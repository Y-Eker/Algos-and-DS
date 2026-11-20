#include "framework.h"

#include <stdlib.h>

#include "aads_console/aads_console.h"
#include "story.h"

static CardValue selected_card_value;
static CardSuit selected_card_suit;
static int recorded_guess_count;
static int challenge_is_active;
static int challenge_is_valid;
static int secret_card_was_found;
static int card_output_is_enabled;
static int previous_guess_distance;

static const char *card_value_name(CardValue card_value);
static const char *card_suit_name(CardSuit card_suit);
static int card_is_valid(CardValue card_value, CardSuit card_suit);
static int compare_cards(CardValue left_value,
                         CardSuit left_suit,
                         CardValue right_value,
                         CardSuit right_suit);

void begin_card_challenge(CardValue secret_value,
                          CardSuit secret_suit,
                          int output_is_enabled) {
    selected_card_value = secret_value;
    selected_card_suit = secret_suit;
    recorded_guess_count = 0;
    previous_guess_distance = -1;
    challenge_is_active = 1;
    challenge_is_valid = card_is_valid(secret_value, secret_suit);
    secret_card_was_found = 0;
    card_output_is_enabled = output_is_enabled;
}

CardAnswer check_card_guess(CardValue proposed_value, CardSuit proposed_suit) {
    if (!challenge_is_active || !challenge_is_valid) {
        return CARD_GUESS_INVALID;
    }
    if (secret_card_was_found || recorded_guess_count >= CARD_GUESS_LIMIT) {
        challenge_is_valid = 0;
        if (card_output_is_enabled) {
            report("Invalid card proposal: the challenge is over.\n");
        }
        return CARD_GUESS_INVALID;
    }
    if (!card_is_valid(proposed_value, proposed_suit)) {
        challenge_is_valid = 0;
        if (card_output_is_enabled) {
            report("\nGuess %d/%d\n\n",
                   recorded_guess_count + 1,
                   CARD_GUESS_LIMIT);
            report(magazine_is_verbose()
                       ? "Your algorithm proposes an invalid card.\n\n"
                       : "INVALID CARD\n");
            if (magazine_is_verbose()) {
                print_blocks(CARD_INVALID_PROPOSAL,
                             CARD_INVALID_PROPOSAL_COUNT,
                             NULL,
                             0);
            }
        }
        return CARD_GUESS_INVALID;
    }

    recorded_guess_count++;
    int card_order = compare_cards(selected_card_value,
                                   selected_card_suit,
                                   proposed_value,
                                   proposed_suit);
    if (card_output_is_enabled) {
        report("\nGuess %d/%d\n\n", recorded_guess_count, CARD_GUESS_LIMIT);
        if (magazine_is_verbose()) {
            report("Your algorithm proposes:\n\n");
        }
        report("%s of %s\n\n",
               card_value_name(proposed_value),
               card_suit_name(proposed_suit));
        if (card_order < 0) {
            report(magazine_is_verbose() ? "The secret card is lower.\n"
                                         : "LOWER\n");
        } else if (card_order > 0) {
            report(magazine_is_verbose() ? "The secret card is higher.\n"
                                         : "HIGHER\n");
        } else {
            report(magazine_is_verbose() ? "That's the card!\n" : "CORRECT\n");
        }
    }

    int proposed_card_index = (proposed_value - CARD_VALUE_TWO) *
                                  (CARD_SUIT_HEARTS - CARD_SUIT_SPADES + 1) +
                              proposed_suit - CARD_SUIT_SPADES;
    int secret_card_index = (selected_card_value - CARD_VALUE_TWO) *
                                (CARD_SUIT_HEARTS - CARD_SUIT_SPADES + 1) +
                            selected_card_suit - CARD_SUIT_SPADES;
    int distance = abs(proposed_card_index - secret_card_index);
    if (card_order == 0) {
        secret_card_was_found = 1;
        return CARD_GUESS_IS_CORRECT;
    }
    if (card_output_is_enabled && previous_guess_distance >= 0 &&
        distance < previous_guess_distance) {
        if (magazine_is_verbose()) {
            print_blocks(CARD_CLOSER, CARD_CLOSER_COUNT, NULL, 0);
        }
    }
    previous_guess_distance = distance;
    if (recorded_guess_count == CARD_GUESS_LIMIT) {
        challenge_is_valid = 0;
        if (card_output_is_enabled) {
            report("\nNo guesses left.\n");
        }
    } else if (card_output_is_enabled) {
        add_pause();
    }
    return card_order < 0 ? SECRET_CARD_IS_LOWER : SECRET_CARD_IS_HIGHER;
}

void report_secret_card(void) {
    report(magazine_is_verbose() ? "\nThe secret card was:\n\n%s of %s\n"
                                 : "\nSecret card: %s of %s\n",
           card_value_name(selected_card_value),
           card_suit_name(selected_card_suit));
}

void end_card_challenge(void) {
    challenge_is_active = 0;
}

int card_challenge_was_won(void) {
    return challenge_is_valid && secret_card_was_found &&
           recorded_guess_count <= CARD_GUESS_LIMIT;
}

int card_guess_count(void) {
    return recorded_guess_count;
}

static const char *card_value_name(CardValue card_value) {
    static const char *CARD_VALUE_NAMES[] = {"2",
                                             "3",
                                             "4",
                                             "5",
                                             "6",
                                             "7",
                                             "8",
                                             "9",
                                             "10",
                                             "Jack",
                                             "Queen",
                                             "King",
                                             "Ace"};

    return CARD_VALUE_NAMES[card_value - CARD_VALUE_TWO];
}

static const char *card_suit_name(CardSuit card_suit) {
    static const char *CARD_SUIT_NAMES[] = {"Spades",
                                            "Clubs",
                                            "Diamonds",
                                            "Hearts"};

    return CARD_SUIT_NAMES[card_suit - CARD_SUIT_SPADES];
}

static int card_is_valid(CardValue card_value, CardSuit card_suit) {
    return card_value >= CARD_VALUE_TWO && card_value <= CARD_VALUE_ACE &&
           card_suit >= CARD_SUIT_SPADES && card_suit <= CARD_SUIT_HEARTS;
}

static int compare_cards(CardValue left_value,
                         CardSuit left_suit,
                         CardValue right_value,
                         CardSuit right_suit) {
    if (left_value != right_value) {
        return left_value - right_value;
    }
    return left_suit - right_suit;
}
