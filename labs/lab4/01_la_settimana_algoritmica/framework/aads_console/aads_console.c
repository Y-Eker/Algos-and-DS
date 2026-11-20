#include "aads_console.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aads_console_platform.h"

#define INPUT_CAPACITY 256
#define NARRATIVE_DELAY_MS 3

static int pending_blank_line;
static int input_initialized;
static int current_column;
static int trailing_newlines;

static void begin_section(void) {
    if (!input_initialized) {
        setvbuf(stdin, NULL, _IONBF, 0);
        aads_console_platform_prepare();
        input_initialized = 1;
    }
    if (pending_blank_line) {
        while (trailing_newlines < 2) {
            putchar('\n');
            trailing_newlines++;
        }
        current_column = 0;
        pending_blank_line = 0;
    }
}

static int is_character_start(unsigned char character) {
    return (character & 0xc0) != 0x80;
}

static int word_width(const char *text) {
    int width = 0;
    while (*text != '\0' && !isspace((unsigned char) *text)) {
        width += is_character_start((unsigned char) *text++);
    }
    return width;
}

static void emit_character(int character, int delay_ms, int *skip) {
    putchar(character);
    if (character == '\n') {
        current_column = 0;
        trailing_newlines++;
    } else {
        current_column += is_character_start((unsigned char) character);
        trailing_newlines = 0;
    }
    if (delay_ms > 0 && !*skip &&
        is_character_start((unsigned char) character)) {
        fflush(stdout);
        aads_console_platform_sleep_milliseconds(delay_ms);
        if (aads_console_platform_enter_pressed()) {
            *skip = 1;
        }
    }
}

void print_text(const char *text, int delay_ms) {
    int progressive = delay_ms > 0 && aads_console_platform_is_interactive();
    int skip = !progressive;
    int after_pause = pending_blank_line;
    begin_section();
    if (after_pause) {
        while (*text == '\n') {
            text++;
        }
    }
    if (progressive) {
        aads_console_platform_begin_polling();
    }
    while (*text != '\0') {
        if (*text == ' ' && current_column > 0) {
            const char *next_word = text;
            int spaces = 0;
            while (*next_word == ' ') {
                spaces++;
                next_word++;
            }
            if (*next_word != '\n' && *next_word != '\0' &&
                current_column + spaces + word_width(next_word) >
                    AADS_CONSOLE_WIDTH) {
                emit_character('\n', delay_ms, &skip);
                text = next_word;
                continue;
            }
        }
        unsigned char character = (unsigned char) *text++;
        if (character != '\n' && is_character_start(character) &&
            current_column == AADS_CONSOLE_WIDTH) {
            emit_character('\n', delay_ms, &skip);
        }
        if (character >= 0x80) {
            emit_character(character, 0, &skip);
            while (((unsigned char) *text & 0xc0) == 0x80) {
                emit_character((unsigned char) *text++, 0, &skip);
            }
            if (progressive && !skip) {
                fflush(stdout);
                aads_console_platform_sleep_milliseconds(delay_ms);
                if (aads_console_platform_enter_pressed()) {
                    skip = 1;
                }
            }
        } else {
            emit_character(character, delay_ms, &skip);
        }
    }
    if (progressive) {
        aads_console_platform_end_polling();
    }
    fflush(stdout);
}

static size_t expand_text(const char *text,
                          char *expanded_text,
                          const ConsoleValue values[],
                          int value_count) {
    size_t length = 0;
    while (*text != '\0') {
        const char *replacement = NULL;
        const char *closing_brace = *text == '{' ? strchr(text, '}') : NULL;
        if (closing_brace != NULL) {
            size_t name_length = (size_t) (closing_brace - text - 1);
            for (int value_index = 0; value_index < value_count;
                 value_index++) {
                if (strlen(values[value_index].name) == name_length &&
                    strncmp(text + 1, values[value_index].name, name_length) ==
                        0) {
                    replacement = values[value_index].text;
                    break;
                }
            }
        }
        if (replacement != NULL) {
            size_t replacement_length = strlen(replacement);
            if (expanded_text != NULL) {
                memcpy(expanded_text + length, replacement, replacement_length);
            }
            length += replacement_length;
            text = closing_brace + 1;
        } else {
            if (expanded_text != NULL) {
                expanded_text[length] = *text;
            }
            length++;
            text++;
        }
    }
    if (expanded_text != NULL) {
        expanded_text[length] = '\0';
    }
    return length;
}

void print_blocks(const ConsoleBlock blocks[],
                  int block_count,
                  const ConsoleValue values[],
                  int value_count) {
    for (int block_index = 0; block_index < block_count; block_index++) {
        if (blocks[block_index].kind == CONSOLE_PAUSE) {
            add_pause();
            continue;
        }
        int delay_ms = blocks[block_index].kind == CONSOLE_NARRATIVE
                           ? NARRATIVE_DELAY_MS
                           : -1;
        if (value_count == 0) {
            print_text(blocks[block_index].text, delay_ms);
            continue;
        }
        size_t length =
            expand_text(blocks[block_index].text, NULL, values, value_count);
        char *expanded_text = malloc(length + 1);
        if (expanded_text == NULL) {
            print_text("Cannot allocate the console text.\n", -1);
            return;
        }
        expand_text(blocks[block_index].text,
                    expanded_text,
                    values,
                    value_count);
        print_text(expanded_text, delay_ms);
        free(expanded_text);
    }
}

void add_pause(void) {
    fflush(stdout);
    if (aads_console_platform_is_interactive()) {
        aads_console_platform_wait_enter();
    }
    pending_blank_line = 1;
}

void print_separator(void) {
    char separator[AADS_CONSOLE_WIDTH + 2];
    memset(separator, '*', AADS_CONSOLE_WIDTH);
    separator[AADS_CONSOLE_WIDTH] = '\n';
    separator[AADS_CONSOLE_WIDTH + 1] = '\0';
    print_text(separator, -1);
}

static int read_answer(const char *prompt, char answer[]) {
    print_text(prompt, -1);
    int count = 0;
    int too_long = 0;
    int character;
    while ((character = getchar()) != '\n' && character != EOF) {
        if (count < INPUT_CAPACITY - 1) {
            answer[count++] = (char) character;
        } else {
            too_long = 1;
        }
    }
    answer[count] = '\0';
    if (!aads_console_platform_is_interactive()) {
        print_text("\n", -1);
    } else if (character == '\n') {
        current_column = 0;
        trailing_newlines = 1;
    }
    if (character == EOF && count == 0 && !too_long) {
        return 0;
    }
    return too_long ? -1 : 1;
}

int ask_integer(const char *prompt, int *value) {
    char answer[INPUT_CAPACITY];
    for (;;) {
        int result = read_answer(prompt, answer);
        if (result == 0) {
            return 0;
        }
        char *end;
        errno = 0;
        long parsed = strtol(answer, &end, 10);
        int has_number = end != answer;
        while (isspace((unsigned char) *end)) {
            end++;
        }
        if (result > 0 && has_number && errno == 0 && *end == '\0' &&
            parsed >= INT_MIN && parsed <= INT_MAX) {
            *value = (int) parsed;
            return 1;
        }
        print_text("Invalid input: enter an integer.\n", -1);
    }
}

int ask_choice(const char *prompt, const int choices[], int choice_count) {
    int value;
    while (ask_integer(prompt, &value)) {
        for (int index = 0; index < choice_count; index++) {
            if (value == choices[index]) {
                return value;
            }
        }
        print_text("Invalid choice.\n", -1);
    }
    return -1;
}

YesNoAnswer ask_yes_no(const char *prompt) {
    char answer[INPUT_CAPACITY];
    for (;;) {
        print_text(prompt, -1);
        int result = read_answer(" [Y/n]: ", answer);
        if (result == 0) {
            return NO;
        }
        char *cursor = answer;
        while (isspace((unsigned char) *cursor)) {
            cursor++;
        }
        if (*cursor == '\0') {
            if (result > 0) {
                return YES;
            }
            print_text("Invalid input: enter y or n.\n", -1);
            continue;
        }
        int first = tolower((unsigned char) *cursor++);
        while (isspace((unsigned char) *cursor)) {
            cursor++;
        }
        if (result > 0 && *cursor == '\0' && (first == 'y' || first == 'n')) {
            return first == 'y' ? YES : NO;
        }
        print_text("Invalid input: enter y or n.\n", -1);
    }
}
