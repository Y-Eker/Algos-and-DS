#include "framework.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aads_console/aads_console.h"
#include "story.h"

#define PRESENTATION_CAPACITY 8192
#define EDITORIAL_PAGE_COUNT 3

static int verbose_mode;

static void present(const char *format, va_list arguments, int delay_ms) {
    char text[PRESENTATION_CAPACITY];
    vsnprintf(text, sizeof(text), format, arguments);
    print_text(text, delay_ms);
}

void report(const char *format, ...) {
    va_list arguments;
    va_start(arguments, format);
    present(format, arguments, -1);
    va_end(arguments);
}

int magazine_is_verbose(void) {
    return verbose_mode;
}

void magazine_open(int verbose) {
    verbose_mode = verbose;
    srand((unsigned int) time(NULL));
    print_blocks(MAGAZINE_HEADER, MAGAZINE_HEADER_COUNT, NULL, 0);
}

MagazinePage magazine_choose_page(MagazinePage current_page) {
    if (current_page == RECURSION_PAGE) {
        print_blocks(RECURSION_INDEX, RECURSION_INDEX_COUNT, NULL, 0);
    } else if (current_page == COMPARISON_QUIZ_PAGE_NUMBER) {
        print_blocks(COMPARISON_QUIZ_PAGE, COMPARISON_QUIZ_PAGE_COUNT, NULL, 0);
    } else if (current_page == FACTS_PAGE_NUMBER) {
        print_blocks(FACTS_PAGE, FACTS_PAGE_COUNT, NULL, 0);
    } else if (current_page == SOLUTIONS_PAGE_NUMBER) {
        print_blocks(SOLUTIONS_PAGE, SOLUTIONS_PAGE_COUNT, NULL, 0);
    } else {
        print_blocks(verbose_mode ? INDEX_VERBOSE : INDEX_QUIET,
                     verbose_mode ? INDEX_VERBOSE_COUNT : INDEX_QUIET_COUNT,
                     NULL,
                     0);
    }
    const int pages[] = {MAGAZINE_CLOSED,
                         INDEX_PAGE,
                         RECURSION_PAGE,
                         PALINDROME_PAGE,
                         SECRET_CODE_PAGE,
                         CARD_PAGE,
                         HANOI_PAGE,
                         SORTING_PAGE,
                         COMPARISON_QUIZ_PAGE_NUMBER,
                         FACTS_PAGE_NUMBER,
                         SOLUTIONS_PAGE_NUMBER};
    int page_count = (int) (sizeof(pages) / sizeof(pages[0]));
    int selected =
        ask_choice("\nPage: ",
                   pages,
                   page_count - EDITORIAL_PAGE_COUNT * !verbose_mode);
    return selected < 0 ? MAGAZINE_CLOSED : (MagazinePage) selected;
}

void magazine_close(void) {
    report("\nSee you in the next issue!\n");
}
