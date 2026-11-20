#include "framework.h"
#include "recursion.h"
#include "sorting.h"
#include "support/allocation_tracker.h"
#include "unity.h"

#include <limits.h>
#include <string.h>

#define BINARY_DIGIT_CAPACITY (sizeof(unsigned int) * CHAR_BIT + 1)

void setUp(void) {
}

void tearDown(void) {
}

/* ------------------------------------------------------------------ */
/* Recursion section: the operations completed in src/recursion.c       */
/* ------------------------------------------------------------------ */

static void test_palindrome_recognizes_normalized_text(void) {
    TEST_ASSERT_EQUAL_INT(PALINDROME_FOUND, recognize_palindrome("Anna"));
    TEST_ASSERT_EQUAL_INT(
        PALINDROME_FOUND,
        recognize_palindrome("A man, a plan, a canal: Panama!"));
    TEST_ASSERT_EQUAL_INT(PALINDROME_FOUND,
                          recognize_palindrome("I topi non avevano nipoti."));
    TEST_ASSERT_EQUAL_INT(
        PALINDROME_NOT_FOUND,
        recognize_palindrome("Recursive functions need a base case."));
}

static void test_palindrome_rejects_text_without_letters(void) {
    TEST_ASSERT_EQUAL_INT(PALINDROME_INVALID_TEXT, recognize_palindrome(""));
    TEST_ASSERT_EQUAL_INT(PALINDROME_INVALID_TEXT,
                          recognize_palindrome(" ... \t!?"));
}

static void test_secret_code_generates_binary_digits(void) {
    char binary_digits[BINARY_DIGIT_CAPACITY] = "";

    generate_secret_code(0, binary_digits);
    TEST_ASSERT_EQUAL_STRING("0", binary_digits);

    generate_secret_code(42, binary_digits);
    TEST_ASSERT_EQUAL_STRING("101010", binary_digits);

    generate_secret_code(UINT_MAX, binary_digits);
    TEST_ASSERT_EQUAL_INT((int) (sizeof(unsigned int) * CHAR_BIT),
                          (int) strlen(binary_digits));
    for (int digit_index = 0; binary_digits[digit_index] != '\0';
         digit_index++) {
        TEST_ASSERT_EQUAL_CHAR('1', binary_digits[digit_index]);
    }
}

static void test_card_search_finds_every_card_within_six_guesses(void) {
    for (int card_value = CARD_VALUE_TWO; card_value <= CARD_VALUE_ACE;
         card_value++) {
        for (int card_suit = CARD_SUIT_SPADES; card_suit <= CARD_SUIT_HEARTS;
             card_suit++) {
            begin_card_challenge((CardValue) card_value,
                                 (CardSuit) card_suit,
                                 0);

            TEST_ASSERT_TRUE(guess_card());
            TEST_ASSERT_TRUE(card_challenge_was_won());
            TEST_ASSERT_GREATER_OR_EQUAL_INT(1, card_guess_count());
            TEST_ASSERT_LESS_OR_EQUAL_INT(CARD_GUESS_LIMIT, card_guess_count());
        }
    }
}

static void test_hanoi_solves_every_supported_size_optimally(void) {
    for (int disk_count = 1; disk_count <= HANOI_MAX_DISK_COUNT; disk_count++) {
        begin_hanoi_challenge(disk_count, 0);

        solve_towers_of_hanoi(disk_count);
        TEST_ASSERT_TRUE(hanoi_challenge_was_won());
        TEST_ASSERT_EQUAL_INT(minimum_hanoi_move_count(disk_count),
                              hanoi_move_count());
    }
}

#define TEST_VALUE_CAPACITY 16
#define QUICK_SORT_ALGORITHM 0
#define MERGE_SORT_ALGORITHM 1
#define MY_SORT_ALGORITHM 2

/* ------------------------------------------------------------------ */
/* Sorting section: the operations completed in src/sorting.c           */
/* ------------------------------------------------------------------ */

/* Calls the selected public sorting operation. */
static int call_sorting_algorithm(int algorithm, int values[], int value_count);
/* Checks one complete sorting result against its expected values. */
static void assert_sort_result(int algorithm,
                               const int input_values[],
                               const int expected_values[],
                               int value_count);
/* Runs the normal and boundary cases shared by the three sorts. */
static void exercise_sorting_algorithm(int algorithm);

static void test_quick_sort_orders_representative_inputs(void) {
    exercise_sorting_algorithm(QUICK_SORT_ALGORITHM);
}

static void test_merge_sort_orders_representative_inputs(void) {
    exercise_sorting_algorithm(MERGE_SORT_ALGORITHM);
}

static void test_my_sort_orders_representative_inputs(void) {
    exercise_sorting_algorithm(MY_SORT_ALGORITHM);
}

static int call_sorting_algorithm(int algorithm,
                                  int values[],
                                  int value_count) {
    if (algorithm == QUICK_SORT_ALGORITHM) {
        return quick_sort(values, value_count);
    }
    if (algorithm == MERGE_SORT_ALGORITHM) {
        return merge_sort(values, value_count);
    }
    return my_sort(values, value_count);
}

static void assert_sort_result(int algorithm,
                               const int input_values[],
                               const int expected_values[],
                               int value_count) {
    int actual_values[TEST_VALUE_CAPACITY];
    for (int value_index = 0; value_index < value_count; value_index++) {
        actual_values[value_index] = input_values[value_index];
    }

    TEST_ASSERT_TRUE(call_sorting_algorithm(algorithm,
                                            actual_values,
                                            value_count));
    if (value_count > 0) {
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_values,
                                    actual_values,
                                    value_count);
    }
}

static void exercise_sorting_algorithm(int algorithm) {
    const int single_value[] = {7};
    const int mixed_values[] = {9, -2, 5, 5, 0, 12, -7};
    const int sorted_mixed_values[] = {-7, -2, 0, 5, 5, 9, 12};
    const int ordered_values[] = {-4, -1, 0, 2, 8, 13};
    const int reverse_values[] = {8, 7, 6, 5, 4, 3, 2, 1};
    const int sorted_reverse_values[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const int duplicate_values[] = {3, 1, 3, 2, 1, 3, 2, 1};
    const int sorted_duplicate_values[] = {1, 1, 1, 2, 2, 3, 3, 3};

    assert_sort_result(algorithm, mixed_values, mixed_values, 0);
    assert_sort_result(algorithm, single_value, single_value, 1);
    assert_sort_result(algorithm, mixed_values, sorted_mixed_values, 7);
    assert_sort_result(algorithm, ordered_values, ordered_values, 6);
    assert_sort_result(algorithm, reverse_values, sorted_reverse_values, 8);
    assert_sort_result(algorithm, duplicate_values, sorted_duplicate_values, 8);
}

/* ------------------------------------------------------------------ */

static void test_every_allocated_block_is_released(void) {
    const int unsorted_values[] = {9, -2, 5, 5, 0, 12, -7};
    int values[TEST_VALUE_CAPACITY];
    int blocks_before = outstanding_allocation_count();

    for (int value_index = 0; value_index < 7; value_index++) {
        values[value_index] = unsorted_values[value_index];
    }
    TEST_ASSERT_TRUE(merge_sort(values, 7));
    recognize_palindrome("Anna");
    recognize_palindrome("A recursive reader.");
    recognize_palindrome(" ... \t!?");

    int leaked_blocks = outstanding_allocation_count() - blocks_before;
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        0,
        leaked_blocks,
        "memory blocks are still allocated: every malloc, calloc and "
        "realloc needs a matching free");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_palindrome_recognizes_normalized_text);
    RUN_TEST(test_palindrome_rejects_text_without_letters);
    RUN_TEST(test_secret_code_generates_binary_digits);
    RUN_TEST(test_card_search_finds_every_card_within_six_guesses);
    RUN_TEST(test_hanoi_solves_every_supported_size_optimally);
    RUN_TEST(test_quick_sort_orders_representative_inputs);
    RUN_TEST(test_merge_sort_orders_representative_inputs);
    RUN_TEST(test_my_sort_orders_representative_inputs);
    RUN_TEST(test_every_allocated_block_is_released);
    return UNITY_END();
}
