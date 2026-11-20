#ifndef AADS_CONSOLE_H
#define AADS_CONSOLE_H

#define AADS_CONSOLE_WIDTH 80

typedef enum {
    NO = 0,
    YES = 1
} YesNoAnswer;

typedef enum {
    CONSOLE_TEXT,
    CONSOLE_NARRATIVE,
    CONSOLE_PAUSE
} ConsoleBlockKind;

typedef struct {
    ConsoleBlockKind kind;
    const char *text;
} ConsoleBlock;

typedef struct {
    const char *name;
    const char *text;
} ConsoleValue;

void print_text(const char *text, int delay_ms);
void print_blocks(const ConsoleBlock blocks[],
                  int block_count,
                  const ConsoleValue values[],
                  int value_count);
void add_pause(void);
void print_separator(void);
int ask_integer(const char *prompt, int *value);
int ask_choice(const char *prompt, const int choices[], int choice_count);
YesNoAnswer ask_yes_no(const char *prompt);

#endif
