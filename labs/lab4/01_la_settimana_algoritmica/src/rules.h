/**
 * @file rules.h
 * @brief Shared types and ready-to-use functions supplied by the framework.
 *
 * Include this header to use the shared types and call the framework functions.
 * All functions declared here are already implemented by the supplied framework
 * and included in the project. Call them from your solution; do not implement
 * or redefine them. Leave this header unchanged.
 */
#ifndef MAGAZINE_RULES_H
#define MAGAZINE_RULES_H

/** Result of palindrome recognition after text normalization. */
typedef enum {
    PALINDROME_ERROR = -2,
    PALINDROME_INVALID_TEXT = -1,
    PALINDROME_NOT_FOUND = 0,
    PALINDROME_FOUND = 1
} PalindromeResult;

/** Tower identifiers used by every Hanoi move. */
typedef enum {
    TOWER_WISDOM = 0,
    TOWER_INNER_PEACE = 1,
    TOWER_ENLIGHTENMENT = 2
} Tower;

/** Maximum number of card proposals accepted in one challenge. */
#define CARD_GUESS_LIMIT 6
/** Largest supported Towers of Hanoi puzzle. */
#define HANOI_MAX_DISK_COUNT 8

/** Values of the cards, from two to ace. */
typedef enum {
    CARD_VALUE_TWO = 2,
    CARD_VALUE_THREE = 3,
    CARD_VALUE_FOUR = 4,
    CARD_VALUE_FIVE = 5,
    CARD_VALUE_SIX = 6,
    CARD_VALUE_SEVEN = 7,
    CARD_VALUE_EIGHT = 8,
    CARD_VALUE_NINE = 9,
    CARD_VALUE_TEN = 10,
    CARD_VALUE_JACK = 11,
    CARD_VALUE_QUEEN = 12,
    CARD_VALUE_KING = 13,
    CARD_VALUE_ACE = 14
} CardValue;

/** Suits in increasing order of value for the card challenge. */
typedef enum {
    CARD_SUIT_SPADES = 1,
    CARD_SUIT_CLUBS = 2,
    CARD_SUIT_DIAMONDS = 3,
    CARD_SUIT_HEARTS = 4
} CardSuit;

/** Result of comparing one proposal with the secret card. */
typedef enum {
    CARD_GUESS_INVALID = -2,
    SECRET_CARD_IS_LOWER = -1,
    CARD_GUESS_IS_CORRECT = 0,
    SECRET_CARD_IS_HIGHER = 1
} CardAnswer;

/**
 * @brief Checks one proposed card against the card chosen by the magazine.
 *
 * This function is already implemented by the framework. Call it from your
 * solution; do not implement or redefine it.
 *
 * Every proposal in the card challenge must use this helper. It is the only
 * operation through which the magazine receives, records, and evaluates a
 * proposed card. Card values are ordered from two to ace. For equal values,
 * suits are ordered from spades to hearts. An invalid value or suit
 * immediately invalidates the challenge.
 *
 * @param[in] proposed_value Value of the proposed card.
 * @param[in] proposed_suit Suit of the proposed card.
 * @return The position of the secret card relative to the proposal, or
 *         CARD_GUESS_INVALID when the proposal is invalid, when no more
 *         attempts are available, or when the secret card has already been
 *         found. Every CARD_GUESS_INVALID answer ends the challenge.
 */
CardAnswer check_card_guess(CardValue proposed_value, CardSuit proposed_suit);

/**
 * @brief Moves one disk in the Towers of Hanoi challenge if the move is legal.
 *
 * This function is already implemented by the framework. Call it from your
 * solution; do not implement or redefine it.
 *
 * Every move in the Hanoi challenge must use this helper. It is the only
 * operation through which the magazine can validate the move, update the
 * towers, and count the accepted steps. Legal moves remain accepted beyond
 * the minimum move count. A move that violates the puzzle rules invalidates
 * the challenge, and all later moves are rejected as well. The magazine
 * reports the rejected move and the tower state after the algorithm returns.
 *
 * @param[in] disk_number Disk to move, where 1 is the smallest disk.
 * @param[in] source_tower Tower from which the top disk is moved.
 * @param[in] destination_tower Tower on which the disk is placed.
 * @return 1 when the move is accepted, or 0 when the challenge has failed.
 */
int move_hanoi_disk(int disk_number,
                    Tower source_tower,
                    Tower destination_tower);

/**
 * @brief Compares two sortable values and records the comparison.
 *
 * This function is already implemented by the framework. Call it from your
 * solution; do not implement or redefine it.
 *
 * Every value comparison performed by an algorithm competing in the sorting
 * race must use this helper. Direct comparisons are invisible to the magazine
 * and cannot contribute to the official comparison count.
 *
 * @param[in] left_value First sortable value.
 * @param[in] right_value Second sortable value.
 * @return A negative value when left_value is smaller, zero when the values
 *         are equal, or a positive value when left_value is greater.
 */
int compare_sorting_values(int left_value, int right_value);

#endif
