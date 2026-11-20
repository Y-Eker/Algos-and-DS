#ifndef RECURSION_H
#define RECURSION_H

#include "rules.h"

/**
 * @brief Recognizes a palindrome after ignoring non-letter characters and case.
 *
 * Text normalization is part of the operation. The final comparison between
 * the retained letters must be recursive.
 *
 * @param[in] text Null-terminated text to examine.
 * @return PALINDROME_FOUND, PALINDROME_NOT_FOUND, or PALINDROME_INVALID_TEXT
 *         when no letter remains after normalization. Returns PALINDROME_ERROR
 *         when memory for the normalized text cannot be allocated.
 */
PalindromeResult recognize_palindrome(const char text[]);

/**
 * @brief Generates the minimal binary representation of a decimal number.
 *
 * The supplied destination has enough room for every binary digit and the
 * string terminator. Binary digits must be generated recursively.
 *
 * @param[in] decimal_number Number to encode.
 * @param[out] binary_digits Destination for the null-terminated binary text.
 */
void generate_secret_code(unsigned int decimal_number, char binary_digits[]);

/**
 * @brief Guesses the card selected by the magazine using recursive search.
 *
 * The complete search organization and card representation belong to this
 * operation. Every proposal must use the supplied helper:
 * @link check_card_guess
 * check_card_guess(CardValue proposed_value, CardSuit proposed_suit)
 * @endlink
 * The helper is declared in rules.h and already implemented by the framework.
 * Call it; do not implement or redefine it. It is the only way the magazine
 * can receive and evaluate a proposed card. The 52 possible cards can always
 * be found in at most six proposals.
 *
 * @return 1 after finding the secret card, or 0 when the challenge fails.
 */
int guess_card(void);

/**
 * @brief Solves Towers of Hanoi recursively from the Tower of Wisdom
 *        to the Tower of Enlightenment.
 *
 * The Tower of Inner Peace is the auxiliary tower. The goal is to move the
 * complete stack in the minimum number of moves. Implement the recursive
 * generation of the move sequence.
 *
 * Every move must use the supplied helper:
 * @link move_hanoi_disk
 * move_hanoi_disk(int disk_number, Tower source_tower,
 *                  Tower destination_tower)
 * @endlink
 * The helper is declared in rules.h and already implemented by the framework.
 * Call it to execute each single-disk move; do not implement or redefine it.
 * It updates and validates the tower state and counts accepted moves. Stop
 * the recursive process when it rejects a move. Valid challenge sizes range
 * from 1 through 8 disks.
 *
 * @param[in] disk_count Number of disks in the challenge.
 */
void solve_towers_of_hanoi(int disk_count);

#endif
