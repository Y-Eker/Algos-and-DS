#include "framework.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aads_console/aads_console.h"
#include "recursion.h"
#include "story.h"

#define BINARY_DIGIT_CAPACITY (sizeof(unsigned int) * CHAR_BIT + 1)
#define PALINDROME_CHALLENGE_COUNT 5
#define PALINDROME_TEXT_CAPACITY 128
#define SECRET_CODE_COUNT 64
#define RANDOM_HANOI_MIN_DISK_COUNT 4
#define INTEGER_TEXT_CAPACITY 16

typedef struct {
    char text[PALINDROME_TEXT_CAPACITY];
    PalindromeResult expected_result;
} PalindromeChallenge;

typedef struct {
    unsigned int decimal_number;
    char binary_code[BINARY_DIGIT_CAPACITY];
} SecretCode;

static int load_palindromes(PalindromeChallenge challenges[]) {
    FILE *input = fopen("data/palindromes.txt", "r");
    if (input == NULL) {
        return 0;
    }
    int input_is_valid = 1;
    for (int challenge_index = 0;
         input_is_valid && challenge_index < PALINDROME_CHALLENGE_COUNT;
         challenge_index++) {
        int expected_result;
        input_is_valid = fscanf(input, "%d ", &expected_result) == 1 &&
                         (expected_result == PALINDROME_FOUND ||
                          expected_result == PALINDROME_NOT_FOUND) &&
                         fgets(challenges[challenge_index].text,
                               PALINDROME_TEXT_CAPACITY,
                               input) != NULL;
        if (input_is_valid) {
            challenges[challenge_index]
                .text[strcspn(challenges[challenge_index].text, "\r\n")] = '\0';
            challenges[challenge_index].expected_result =
                (PalindromeResult) expected_result;
        }
    }
    fclose(input);
    return input_is_valid;
}

static const char *palindrome_verdict(PalindromeResult result) {
    switch (result) {
    case PALINDROME_FOUND:
        return "PALINDROME";
    case PALINDROME_NOT_FOUND:
        return "NOT A PALINDROME";
    case PALINDROME_INVALID_TEXT:
        return "INVALID TEXT";
    case PALINDROME_ERROR:
        return "ALGORITHM ERROR";
    default:
        return "INVALID RESULT";
    }
}

static void report_palindrome_failure(PalindromeResult actual_result,
                                      PalindromeResult expected_result) {
    if (actual_result == PALINDROME_ERROR) {
        report(
            "The algorithm could not allocate memory for text normalization.\n");
    } else if (!magazine_is_verbose()) {
        report("Expected: %s\n", palindrome_verdict(expected_result));
    } else if (actual_result == PALINDROME_INVALID_TEXT) {
        report("Wrong. This is a valid text.\nThe correct verdict was %s.\n",
               palindrome_verdict(expected_result));
    } else if (actual_result != PALINDROME_FOUND &&
               actual_result != PALINDROME_NOT_FOUND) {
        report("Wrong. The algorithm returned an invalid verdict.\n"
               "The correct verdict was %s.\n",
               palindrome_verdict(expected_result));
    } else {
        report("Wrong. The correct verdict was %s.\n",
               palindrome_verdict(expected_result));
        print_blocks(PALINDROME_FOOLED, PALINDROME_FOOLED_COUNT, NULL, 0);
    }
    report("\nChallenge lost.\n");
}

void run_palindrome_challenge(void) {
    print_blocks(PALINDROME_TITLE, PALINDROME_TITLE_COUNT, NULL, 0);
    PalindromeChallenge challenges[PALINDROME_CHALLENGE_COUNT];
    if (!load_palindromes(challenges)) {
        report(
            "Cannot load the prepared palindrome challenges.\nChallenge lost.\n");
        add_pause();
        return;
    }
    if (magazine_is_verbose()) {
        print_blocks(PALINDROME_INTRO, PALINDROME_INTRO_COUNT, NULL, 0);
    }
    const ConsoleBlock *reactions[] = {PALINDROME_REACTION_1,
                                       PALINDROME_REACTION_2,
                                       PALINDROME_REACTION_3,
                                       PALINDROME_REACTION_4,
                                       PALINDROME_REACTION_5};
    const int reaction_counts[] = {PALINDROME_REACTION_1_COUNT,
                                   PALINDROME_REACTION_2_COUNT,
                                   PALINDROME_REACTION_3_COUNT,
                                   PALINDROME_REACTION_4_COUNT,
                                   PALINDROME_REACTION_5_COUNT};
    for (int challenge_index = 0; challenge_index < PALINDROME_CHALLENGE_COUNT;
         challenge_index++) {
        report("CASE %d OF %d\n\n\"%s\"\n",
               challenge_index + 1,
               PALINDROME_CHALLENGE_COUNT,
               challenges[challenge_index].text);
        add_pause();
        print_separator();
        PalindromeResult actual_result =
            recognize_palindrome(challenges[challenge_index].text);
        report("\n");
        print_separator();
        int answer_is_correct =
            actual_result == challenges[challenge_index].expected_result;
        if (magazine_is_verbose()) {
            report("\nYour algorithm says: %s\n\n",
                   palindrome_verdict(actual_result));
        } else {
            report("\n%s - %s\n",
                   palindrome_verdict(actual_result),
                   answer_is_correct ? "CORRECT" : "WRONG");
        }
        if (!answer_is_correct) {
            report_palindrome_failure(
                actual_result,
                challenges[challenge_index].expected_result);
            add_pause();
            return;
        }
        if (magazine_is_verbose()) {
            print_blocks(reactions[challenge_index],
                         reaction_counts[challenge_index],
                         NULL,
                         0);
        }
        if (challenge_index == PALINDROME_CHALLENGE_COUNT - 1) {
            report("\nFINAL RESULT\n\n5 out of 5 correct.\n"
                   "Your algorithm wins the Palindrome Challenge!\n");
        }
        add_pause();
    }
}

static int choose_secret_code(SecretCode *selected_code) {
    static int previous_code_index = -1;
    SecretCode secret_codes[SECRET_CODE_COUNT];
    FILE *input = fopen("data/secret_codes.txt", "r");
    if (input == NULL) {
        return 0;
    }
    int input_is_valid = 1;
    for (int code_index = 0; input_is_valid && code_index < SECRET_CODE_COUNT;
         code_index++) {
        input_is_valid = fscanf(input,
                                "%u %10s",
                                &secret_codes[code_index].decimal_number,
                                secret_codes[code_index].binary_code) == 2;
    }
    fclose(input);
    if (!input_is_valid) {
        return 0;
    }
    int code_index;
    do {
        code_index = rand() % SECRET_CODE_COUNT;
    } while (code_index == previous_code_index);
    previous_code_index = code_index;
    *selected_code = secret_codes[code_index];
    return 1;
}

void run_secret_code_challenge(void) {
    print_blocks(SECRET_TITLE, SECRET_TITLE_COUNT, NULL, 0);
    SecretCode secret_code;
    if (!choose_secret_code(&secret_code)) {
        report("Cannot load the prepared access keys.\nChallenge lost.\n");
        add_pause();
        return;
    }
    if (magazine_is_verbose()) {
        print_blocks(SECRET_INTRO, SECRET_INTRO_COUNT, NULL, 0);
        report("%u\n\n", secret_code.decimal_number);
        print_blocks(SECRET_INSTRUCTIONS, SECRET_INSTRUCTIONS_COUNT, NULL, 0);
    } else {
        report("Access key: %u\n", secret_code.decimal_number);
    }
    add_pause();
    print_separator();
    char generated_code[BINARY_DIGIT_CAPACITY] = "";
    generate_secret_code(secret_code.decimal_number, generated_code);
    report("\n");
    print_separator();
    int code_is_terminated =
        memchr(generated_code, '\0', sizeof(generated_code)) != NULL;
    int code_is_correct = code_is_terminated &&
                          strcmp(generated_code, secret_code.binary_code) == 0;
    report(magazine_is_verbose() ? "\nYour algorithm produced:\n\n%s\n\n"
                                 : "\nGenerated code: %s\n",
           code_is_terminated ? generated_code
                              : "INVALID CODE (missing terminator)");
    if (code_is_correct) {
        report("Code accepted.\n");
        if (magazine_is_verbose()) {
            print_blocks(SECRET_ACCEPTED, SECRET_ACCEPTED_COUNT, NULL, 0);
        }
        report(magazine_is_verbose() ? "Challenge won!\n" : "CORRECT\n");
    } else {
        if (magazine_is_verbose()) {
            print_blocks(SECRET_REJECTED, SECRET_REJECTED_COUNT, NULL, 0);
            report("%s\n\n", secret_code.binary_code);
            print_blocks(SECRET_CLOSED, SECRET_CLOSED_COUNT, NULL, 0);
        } else {
            report("WRONG\nExpected: %s\n\n", secret_code.binary_code);
        }
        report("Challenge lost.\n");
    }
    add_pause();
}

void run_card_challenge(void) {
    print_blocks(CARD_TITLE, CARD_TITLE_COUNT, NULL, 0);
    if (magazine_is_verbose()) {
        print_blocks(CARD_INTRO, CARD_INTRO_COUNT, NULL, 0);
    } else {
        report("Deck: 52 cards\nGuess limit: %d\n", CARD_GUESS_LIMIT);
    }
    CardValue secret_value =
        (CardValue) (CARD_VALUE_TWO +
                     rand() % (CARD_VALUE_ACE - CARD_VALUE_TWO + 1));
    CardSuit secret_suit =
        (CardSuit) (CARD_SUIT_SPADES +
                    rand() % (CARD_SUIT_HEARTS - CARD_SUIT_SPADES + 1));
    begin_card_challenge(secret_value, secret_suit, 1);
    add_pause();
    print_separator();
    int algorithm_reported_success = guess_card();
    report("\n");
    print_separator();
    end_card_challenge();
    report_secret_card();
    if (algorithm_reported_success && card_challenge_was_won()) {
        report(magazine_is_verbose()
                   ? "\nFound in %d guesses.\n\nChallenge won!\n"
                   : "Guesses: %d\nChallenge won.\n",
               card_guess_count());
    } else {
        report("Guesses: %d/%d\n\nChallenge lost.\n",
               card_guess_count(),
               CARD_GUESS_LIMIT);
    }
    add_pause();
}

void run_hanoi_challenge(void) {
    print_blocks(HANOI_TITLE, HANOI_TITLE_COUNT, NULL, 0);
    int disk_count =
        RANDOM_HANOI_MIN_DISK_COUNT +
        rand() % (HANOI_MAX_DISK_COUNT - RANDOM_HANOI_MIN_DISK_COUNT + 1);
    int mark = minimum_hanoi_move_count(disk_count);
    char disk_count_text[INTEGER_TEXT_CAPACITY];
    char minimum_moves_text[INTEGER_TEXT_CAPACITY];
    snprintf(disk_count_text, sizeof(disk_count_text), "%d", disk_count);
    snprintf(minimum_moves_text, sizeof(minimum_moves_text), "%d", mark);
    const ConsoleValue values[] = {{"disk_count", disk_count_text},
                                   {"minimum_moves", minimum_moves_text}};
    print_blocks(magazine_is_verbose() ? HANOI_INTRO : HANOI_QUIET_INTRO,
                 magazine_is_verbose() ? HANOI_INTRO_COUNT
                                       : HANOI_QUIET_INTRO_COUNT,
                 values,
                 2);
    begin_hanoi_challenge(disk_count, 1);
    add_pause();
    print_separator();
    solve_towers_of_hanoi(disk_count);
    report("\n");
    print_separator();
    end_hanoi_challenge();
    if (hanoi_puzzle_was_solved()) {
        report(magazine_is_verbose()
                   ? "\nYou solved the puzzle in %d moves.\n\n"
                   : "\nMoves: %d\n",
               hanoi_move_count());
        if (magazine_is_verbose()) {
            print_blocks(hanoi_challenge_was_won() ? HANOI_OPTIMAL_ENDING
                                                   : HANOI_SOLVED_ENDING,
                         hanoi_challenge_was_won() ? HANOI_OPTIMAL_ENDING_COUNT
                                                   : HANOI_SOLVED_ENDING_COUNT,
                         NULL,
                         0);
        } else {
            report(hanoi_challenge_was_won()
                       ? "Puzzle solved. Optimal solution.\n"
                       : "Puzzle solved. Non-optimal solution.\n");
        }
    } else {
        report("\nMoves: %d\n", hanoi_move_count());
        if (magazine_is_verbose()) {
            print_blocks(HANOI_UNSOLVED_ENDING,
                         HANOI_UNSOLVED_ENDING_COUNT,
                         NULL,
                         0);
        } else {
            report("Puzzle unsolved.\n");
        }
    }
    add_pause();
}
