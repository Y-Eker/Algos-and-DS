#ifndef AADS_CONSOLE_PLATFORM_H
#define AADS_CONSOLE_PLATFORM_H

void aads_console_platform_prepare(void);
int aads_console_platform_is_interactive(void);
void aads_console_platform_begin_polling(void);
int aads_console_platform_enter_pressed(void);
void aads_console_platform_end_polling(void);
void aads_console_platform_wait_enter(void);
void aads_console_platform_sleep_milliseconds(int milliseconds);

#endif
