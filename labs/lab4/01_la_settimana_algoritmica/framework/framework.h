#ifndef MAGAZINE_FRAMEWORK_H
#define MAGAZINE_FRAMEWORK_H

#include "rules.h"

typedef enum {
    MAGAZINE_CLOSED = 0,
    INDEX_PAGE = 1,
    RECURSION_PAGE = 10,
    PALINDROME_PAGE = 11,
    SECRET_CODE_PAGE = 12,
    CARD_PAGE = 13,
    HANOI_PAGE = 14,
    SORTING_PAGE = 20,
    COMPARISON_QUIZ_PAGE_NUMBER = 30,
    FACTS_PAGE_NUMBER = 40,
    SOLUTIONS_PAGE_NUMBER = 46
} MagazinePage;

void magazine_open(int verbose);
MagazinePage magazine_choose_page(MagazinePage current_page);
void magazine_close(void);
int magazine_is_verbose(void);
void report(const char *format, ...);

void run_palindrome_challenge(void);
void run_secret_code_challenge(void);
void run_card_challenge(void);
void run_hanoi_challenge(void);
void run_sorting_competition(void);

void reset_comparison_count(void);
int current_comparison_count(void);
int read_integer_dataset(const char filename[], int **values, int *value_count);
int sorting_result_is_valid(const int input[], const int output[], int count);

void begin_card_challenge(CardValue value, CardSuit suit, int output_enabled);
void end_card_challenge(void);
int card_challenge_was_won(void);
int card_guess_count(void);
void report_secret_card(void);

void begin_hanoi_challenge(int disk_count, int output_enabled);
void end_hanoi_challenge(void);
int hanoi_puzzle_was_solved(void);
int hanoi_challenge_was_won(void);
int hanoi_move_count(void);
int minimum_hanoi_move_count(int disk_count);

#endif
