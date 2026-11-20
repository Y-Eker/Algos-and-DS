#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#endif

#include "aads_console_platform.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

static UINT original_output_code_page;

static void restore_output_code_page(void) {
    SetConsoleOutputCP(original_output_code_page);
}

void aads_console_platform_prepare(void) {
    DWORD console_mode;
    if (GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &console_mode)) {
        original_output_code_page = GetConsoleOutputCP();
        if (SetConsoleOutputCP(CP_UTF8)) {
            atexit(restore_output_code_page);
        }
    }
}

int aads_console_platform_is_interactive(void) {
    DWORD console_mode;
    HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);
    return input_handle != NULL && input_handle != INVALID_HANDLE_VALUE &&
           GetConsoleMode(input_handle, &console_mode) != 0;
}

void aads_console_platform_begin_polling(void) {
}

int aads_console_platform_enter_pressed(void) {
    while (_kbhit()) {
        int character = _getch();
        if (character == 0 || character == 224) {
            (void) _getch();
        } else if (character == '\r' || character == '\n') {
            return 1;
        }
    }
    return 0;
}

void aads_console_platform_end_polling(void) {
}

void aads_console_platform_wait_enter(void) {
    int character;
    do {
        character = _getch();
        if (character == 0 || character == 224) {
            (void) _getch();
        }
    } while (character != '\r' && character != '\n');
}

void aads_console_platform_sleep_milliseconds(int milliseconds) {
    Sleep((DWORD) milliseconds);
}

#else

#include <sys/select.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

static struct termios previous_terminal_state;
static int terminal_state_was_changed;

void aads_console_platform_prepare(void) {
}

int aads_console_platform_is_interactive(void) {
    return isatty(STDIN_FILENO);
}

void aads_console_platform_begin_polling(void) {
    struct termios polling_state;

    terminal_state_was_changed = 0;
    if (tcgetattr(STDIN_FILENO, &previous_terminal_state) != 0) {
        return;
    }

    polling_state = previous_terminal_state;
    polling_state.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
    polling_state.c_cc[VMIN] = 0;
    polling_state.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &polling_state) == 0) {
        terminal_state_was_changed = 1;
    }
}

int aads_console_platform_enter_pressed(void) {
    unsigned char character;
    if (!terminal_state_was_changed) {
        return 0;
    }
    while (read(STDIN_FILENO, &character, 1) == 1) {
        if (character == '\r' || character == '\n') {
            return 1;
        }
    }
    return 0;
}

void aads_console_platform_end_polling(void) {
    if (terminal_state_was_changed) {
        (void) tcsetattr(STDIN_FILENO, TCSANOW, &previous_terminal_state);
        terminal_state_was_changed = 0;
    }
}

void aads_console_platform_wait_enter(void) {
    fd_set input_set;

    aads_console_platform_begin_polling();
    if (!terminal_state_was_changed) {
        int character;
        while ((character = getchar()) != '\n' && character != EOF) {
        }
        return;
    }
    for (;;) {
        FD_ZERO(&input_set);
        FD_SET(STDIN_FILENO, &input_set);
        if (select(STDIN_FILENO + 1, &input_set, NULL, NULL, NULL) > 0 &&
            aads_console_platform_enter_pressed()) {
            break;
        }
    }
    aads_console_platform_end_polling();
}

void aads_console_platform_sleep_milliseconds(int milliseconds) {
    struct timespec delay;
    delay.tv_sec = milliseconds / 1000;
    delay.tv_nsec = (long) (milliseconds % 1000) * 1000000L;
    (void) nanosleep(&delay, NULL);
}

#endif
