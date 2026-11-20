#include "story.h"

#include <stddef.h>

const ConsoleBlock CARD_INVALID_PROPOSAL[] = {
    {CONSOLE_NARRATIVE, "The magazine cannot accept that guess.\n"}};

const int CARD_INVALID_PROPOSAL_COUNT =
    sizeof(CARD_INVALID_PROPOSAL) / sizeof(CARD_INVALID_PROPOSAL[0]);

const ConsoleBlock MAGAZINE_HEADER[] = {
    {CONSOLE_TEXT,
     " _    __     __  ___ _____ _____ _ __ __  __  __  _  __    \n"
     "| |  /  \\  /' _/| __|_   _|_   _| |  V  |/  \\|  \\| |/  \\   \n"
     "| |_| /\\ | `._`.| _|  | |   | | | | \\_/ | /\\ | | ' | /\\ |  \n"
     "|___|_||_| |___/|___|_|_|__ |_|_|_|_|_|_|_||_|_|\\__|_||_|  \n"
     "             __  _   __  __  ___  _ _____ _   _ _  __  __\n"
     "            /  \\| | / _]/__\\| _ \\| |_   _|  V  | |/ _//  \\  \n"
     "           | /\\ | || [/\\ \\/ | v /| | | | | \\_/ | | \\_| /\\ | \n"
     "           |_||_|___\\__/\\__/|_|_\\|_| |_| |_| |_|_|\\__/_||_|  \n"
     "\n"
     "________________________________________________________________\n"
     "|         IL PIU DIGITALE INTEGRATORE PER LA MENTE             |\n"
     "________________________________________________________________\n"},
};

const int MAGAZINE_HEADER_COUNT =
    sizeof(MAGAZINE_HEADER) / sizeof(MAGAZINE_HEADER[0]);

const ConsoleBlock INDEX_VERBOSE[] = {
    {CONSOLE_TEXT,
     "INDEX                                                     Page 1\n"
     "\n"
     "  Page 10   La Pagina della Ricorsione\n"
     "  Page 20   Che film è?\n"
     "  Page 30   Il confronto\n"
     "  Page 40   Forse non tutti sanno che...\n"
     "  Page 46   Soluzioni\n"
     "\n"
     "  0         Close the magazine\n"},
};

const int INDEX_VERBOSE_COUNT =
    sizeof(INDEX_VERBOSE) / sizeof(INDEX_VERBOSE[0]);

const ConsoleBlock INDEX_QUIET[] = {
    {CONSOLE_TEXT,
     "INDEX                                                     Page 1\n"
     "\n"
     "  Page 10   La Pagina della Ricorsione\n"
     "  Page 20   Che film è?\n"
     "\n"
     "  0         Close the magazine\n"},
};

const int INDEX_QUIET_COUNT = sizeof(INDEX_QUIET) / sizeof(INDEX_QUIET[0]);

const ConsoleBlock RECURSION_INDEX[] = {
    {CONSOLE_TEXT,
     "LA PAGINA DELLA RICORSIONE                              Page 10\n"
     "\n"
     "Choose a challenge:\n"
     "\n"
     "  Page 11   The Palindrome Challenge\n"
     "  Page 12   The Secret Code\n"
     "  Page 13   Guess the Card\n"
     "  Page 14   Towers of Hanoi\n"
     "\n"
     "  Page  1   Index\n"},
};

const int RECURSION_INDEX_COUNT =
    sizeof(RECURSION_INDEX) / sizeof(RECURSION_INDEX[0]);

const ConsoleBlock PALINDROME_TITLE[] = {
    {CONSOLE_TEXT,
     "THE PALINDROME CHALLENGE                                Page 11\n\n"},
};

const int PALINDROME_TITLE_COUNT =
    sizeof(PALINDROME_TITLE) / sizeof(PALINDROME_TITLE[0]);

const ConsoleBlock PALINDROME_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "Five entries have reached the editorial desk.\n"
     "Some are palindromes. Some are not.\n"
     "\n"
     "Ignore case, spaces, and punctuation. Only letters count.\n"
     "Let's see whether your recursive reader can tell them apart.\n"
     "\n"},
};

const int PALINDROME_INTRO_COUNT =
    sizeof(PALINDROME_INTRO) / sizeof(PALINDROME_INTRO[0]);

const ConsoleBlock CARD_TITLE[] = {
    {CONSOLE_TEXT,
     "GUESS THE CARD                                          Page 13\n\n"},
};

const int CARD_TITLE_COUNT = sizeof(CARD_TITLE) / sizeof(CARD_TITLE[0]);

const ConsoleBlock CARD_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "The magazine has chosen one card from the deck.\n"
     "\n"
     "Your recursive algorithm has at most 6 guesses to find it.\n"
     "After every guess, the magazine will tell you whether the secret card is higher or lower.\n"
     "\n"
     "Choose carefully. There are no extra guesses.\n"},
};

const int CARD_INTRO_COUNT = sizeof(CARD_INTRO) / sizeof(CARD_INTRO[0]);

const ConsoleBlock HANOI_TITLE[] = {
    {CONSOLE_TEXT,
     "TOWERS OF HANOI                                        Page 14\n\n"},
};

const int HANOI_TITLE_COUNT = sizeof(HANOI_TITLE) / sizeof(HANOI_TITLE[0]);

const ConsoleBlock HANOI_QUIET_INTRO[] = {
    {CONSOLE_TEXT,
     "Disks: {disk_count}\n"
     "Move the complete stack from the Tower of Wisdom to the Tower of Enlightenment, using the Tower of Inner Peace.\n"
     "Minimum moves: {minimum_moves}\n"},
};

const int HANOI_QUIET_INTRO_COUNT =
    sizeof(HANOI_QUIET_INTRO) / sizeof(HANOI_QUIET_INTRO[0]);

const ConsoleBlock HANOI_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "In a quiet monastery, every monk must face the puzzle of the three towers.\n"
     "\n"
     "Solving it opens the way to inner peace.\n"
     "Solving it in the fewest possible moves brings enlightenment.\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "The disks are stacked on the Tower of Wisdom, from largest at the bottom to smallest at the top.\n"
     "\n"
     "Move the complete stack to the Tower of Enlightenment, using the Tower of Inner Peace when necessary.\n"
     "\n"
     "Only one disk may move at a time.\n"
     "A larger disk may never rest on a smaller one.\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "Today's puzzle has {disk_count} disks.\n"
     "\n"
     "After centuries of practice, the monks have solved this puzzle in {minimum_moves} moves.\n"
     "\n"
     "Can your recursive algorithm match their mastery?\n"},
};

const int HANOI_INTRO_COUNT = sizeof(HANOI_INTRO) / sizeof(HANOI_INTRO[0]);

const ConsoleBlock SORTING_TITLE[] = {
    {CONSOLE_TEXT,
     "CHE FILM È?                                             Page 20\n"},
};

const int SORTING_TITLE_COUNT =
    sizeof(SORTING_TITLE) / sizeof(SORTING_TITLE[0]);

const ConsoleBlock SORTING_INTRO[] = {
    {CONSOLE_TEXT,
     "Soluzione a pagina 46.\n"
     "\n"
     "Read the following plot and guess the movie.\n"
     "\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "Judy Standish is struggling to keep her sanitarium open.\n"
     "\n"
     "Banker J.D. Morgan holds the mortgage and is waiting for the chance to take it over.\n"
     "\n"
     "There may still be one way out. The sanitarium's richest patient, Mrs. Upjohn, agrees to stay only if Dr. Hugo Z. Hackenbush is put in charge.\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "Hackenbush is called in and arrives to take the job.\n"
     "\n"
     "There is one small problem:\n"
     "he is not a doctor at all.\n"
     "\n"
     "He is a horse doctor.\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "Meanwhile, Judy's boyfriend Gil has spent his savings on Hi-Hat, a racehorse bought from Morgan, hoping that a few victories might help save the sanitarium.\n"
     "\n"
     "Hi-Hat is racing today against three unusual competitors:\n"
     "\n"
     "Quick Step\n"
     "Merge Ahead\n"
     "Free Rein\n"
     "\n"
     "Four races are on the card.\n"
     "Four horses to compete.\n"
     "\n"
     "The first race is about to begin.\n"},
};

const int SORTING_INTRO_COUNT =
    sizeof(SORTING_INTRO) / sizeof(SORTING_INTRO[0]);

const ConsoleBlock SORTING_CLOSING[] = {
    {CONSOLE_NARRATIVE,
     "Hi-Hat has finished last in every race.\n"
     "\n"
     "Later, at the stables, Morgan shows up.\n"
     "\n"
     "Hi-Hat panics at the sight and sound of his former owner, bolts away and clears every obstacle in his path.\n"
     "\n"
     "Gil watches him go.\n"
     "\n"
     "Maybe Hi-Hat is not much of a racer...\n"
     "but he could be quite a jumper.\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "Gil enters him in the upcoming Grand Steeplechase, where Morgan's horse is competing too.\n"
     "\n"
     "Near the finish, Hi-Hat and Morgan's horse are fighting for the lead when they both crash into the mud.\n"
     "\n"
     "The jockeys remount, and Morgan's jockey crosses the line first.\n"},
    {CONSOLE_PAUSE, NULL},
    {CONSOLE_NARRATIVE,
     "But in the confusion, they mounted the wrong horses.\n"
     "\n"
     "Morgan's jockey crossed the finish line on Hi-Hat.\n"
     "\n"
     "Hi-Hat wins after all.\n"
     "\n"
     "And this time, the prize money is enough to save Judy's sanitarium.\n"
     "\n"},
    {CONSOLE_TEXT, "What movie is this plot from?\n"},
};

const int SORTING_CLOSING_COUNT =
    sizeof(SORTING_CLOSING) / sizeof(SORTING_CLOSING[0]);

const ConsoleBlock SOLUTIONS_PAGE[] = {
    {CONSOLE_TEXT,
     "SOLUZIONI                                                Page 46\n"
     "\n"
     "Che film è? (pag. 20): A Day at the Races, 1937.\n"
     "\n"
     "Il confronto (pag. 30): Version A prints 40 30 20 10.\n"
     "Version B prints 10 20 30 40. Moving the printf before or after the recursive call reverses the order in which the values are printed.\n"},
};

const int SOLUTIONS_PAGE_COUNT =
    sizeof(SOLUTIONS_PAGE) / sizeof(SOLUTIONS_PAGE[0]);

const ConsoleBlock SECRET_TITLE[] = {
    {CONSOLE_TEXT,
     "THE SECRET CODE                                         Page 12\n\n"},
};

const int SECRET_TITLE_COUNT = sizeof(SECRET_TITLE) / sizeof(SECRET_TITLE[0]);

const ConsoleBlock SECRET_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "A locked door stands between you and the next page.\n"
     "Fortunately, the editor left the access key behind.\n"
     "\n"
     "Today's access key is:\n"
     "\n"},
};

const int SECRET_INTRO_COUNT = sizeof(SECRET_INTRO) / sizeof(SECRET_INTRO[0]);

const ConsoleBlock SECRET_INSTRUCTIONS[] = {
    {CONSOLE_NARRATIVE,
     "Convert it to the secret code.\n"
     "No leading zeroes. No second chances.\n"},
};

const int SECRET_INSTRUCTIONS_COUNT =
    sizeof(SECRET_INSTRUCTIONS) / sizeof(SECRET_INSTRUCTIONS[0]);

const ConsoleBlock SECRET_ACCEPTED[] = {
    {CONSOLE_NARRATIVE,
     "The lock clicks. The door opens.\n"
     "\n"},
};

const int SECRET_ACCEPTED_COUNT =
    sizeof(SECRET_ACCEPTED) / sizeof(SECRET_ACCEPTED[0]);

const ConsoleBlock SECRET_REJECTED[] = {
    {CONSOLE_TEXT,
     "Code rejected.\n"
     "The expected code was:\n"
     "\n"},
};

const int SECRET_REJECTED_COUNT =
    sizeof(SECRET_REJECTED) / sizeof(SECRET_REJECTED[0]);

const ConsoleBlock SECRET_CLOSED[] = {
    {CONSOLE_NARRATIVE,
     "The door remains firmly closed.\n"
     "\n"},
};

const int SECRET_CLOSED_COUNT =
    sizeof(SECRET_CLOSED) / sizeof(SECRET_CLOSED[0]);

const ConsoleBlock RACE_1_TITLE[] = {
    {CONSOLE_TEXT, "FIRST RACE — RANDOM\n"},
};

const int RACE_1_TITLE_COUNT = sizeof(RACE_1_TITLE) / sizeof(RACE_1_TITLE[0]);

const ConsoleBlock RACE_1_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "Nothing on this track seems to be in any particular order.\n"},
};

const int RACE_1_INTRO_COUNT = sizeof(RACE_1_INTRO) / sizeof(RACE_1_INTRO[0]);

const ConsoleBlock RACE_2_TITLE[] = {
    {CONSOLE_TEXT, "SECOND RACE — ALREADY SORTED\n"},
};

const int RACE_2_TITLE_COUNT = sizeof(RACE_2_TITLE) / sizeof(RACE_2_TITLE[0]);

const ConsoleBlock RACE_2_INTRO[] = {
    {CONSOLE_NARRATIVE, "Everything is already in perfect order.\n"},
};

const int RACE_2_INTRO_COUNT = sizeof(RACE_2_INTRO) / sizeof(RACE_2_INTRO[0]);

const ConsoleBlock RACE_3_TITLE[] = {
    {CONSOLE_TEXT, "THIRD RACE — REVERSE SORTED\n"},
};

const int RACE_3_TITLE_COUNT = sizeof(RACE_3_TITLE) / sizeof(RACE_3_TITLE[0]);

const ConsoleBlock RACE_3_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "This time, everything starts in the wrong direction.\n"},
};

const int RACE_3_INTRO_COUNT = sizeof(RACE_3_INTRO) / sizeof(RACE_3_INTRO[0]);

const ConsoleBlock RACE_4_TITLE[] = {
    {CONSOLE_TEXT, "FOURTH RACE — MANY DUPLICATES\n"},
};

const int RACE_4_TITLE_COUNT = sizeof(RACE_4_TITLE) / sizeof(RACE_4_TITLE[0]);

const ConsoleBlock RACE_4_INTRO[] = {
    {CONSOLE_NARRATIVE,
     "The field looks strangely familiar.\n"
     "Several values appear more than once.\n"},
};

const int RACE_4_INTRO_COUNT = sizeof(RACE_4_INTRO) / sizeof(RACE_4_INTRO[0]);

const ConsoleBlock PALINDROME_REACTION_1[] = {
    {CONSOLE_NARRATIVE, "Correct. A gentle start.\n"},
};

const int PALINDROME_REACTION_1_COUNT =
    sizeof(PALINDROME_REACTION_1) / sizeof(PALINDROME_REACTION_1[0]);

const ConsoleBlock PALINDROME_REACTION_2[] = {
    {CONSOLE_NARRATIVE, "Correct. Spaces did not fool it.\n"},
};

const int PALINDROME_REACTION_2_COUNT =
    sizeof(PALINDROME_REACTION_2) / sizeof(PALINDROME_REACTION_2[0]);

const ConsoleBlock PALINDROME_REACTION_3[] = {
    {CONSOLE_NARRATIVE, "Correct. Neither did the punctuation.\n"},
};

const int PALINDROME_REACTION_3_COUNT =
    sizeof(PALINDROME_REACTION_3) / sizeof(PALINDROME_REACTION_3[0]);

const ConsoleBlock PALINDROME_REACTION_4[] = {
    {CONSOLE_NARRATIVE,
     "Correct. Recursion may need a base case.\n"
     "Symmetry is another matter.\n"},
};

const int PALINDROME_REACTION_4_COUNT =
    sizeof(PALINDROME_REACTION_4) / sizeof(PALINDROME_REACTION_4[0]);

const ConsoleBlock PALINDROME_REACTION_5[] = {
    {CONSOLE_NARRATIVE, "Correct. The editor closes the file.\n"},
};

const int PALINDROME_REACTION_5_COUNT =
    sizeof(PALINDROME_REACTION_5) / sizeof(PALINDROME_REACTION_5[0]);

const ConsoleBlock PALINDROME_FOOLED[] = {
    {CONSOLE_NARRATIVE, "That one fooled the recursive reader.\n"},
};

const int PALINDROME_FOOLED_COUNT =
    sizeof(PALINDROME_FOOLED) / sizeof(PALINDROME_FOOLED[0]);

const ConsoleBlock CARD_CLOSER[] = {
    {CONSOLE_NARRATIVE,
     "\n"
     "Getting closer.\n"},
};

const int CARD_CLOSER_COUNT = sizeof(CARD_CLOSER) / sizeof(CARD_CLOSER[0]);

const ConsoleBlock HANOI_OPTIMAL_ENDING[] = {
    {CONSOLE_NARRATIVE,
     "You have found inner peace and reached enlightenment.\n"},
};

const int HANOI_OPTIMAL_ENDING_COUNT =
    sizeof(HANOI_OPTIMAL_ENDING) / sizeof(HANOI_OPTIMAL_ENDING[0]);

const ConsoleBlock HANOI_SOLVED_ENDING[] = {
    {CONSOLE_NARRATIVE,
     "The way to inner peace is open.\n"
     "Your journey towards enlightenment continues.\n"},
};

const int HANOI_SOLVED_ENDING_COUNT =
    sizeof(HANOI_SOLVED_ENDING) / sizeof(HANOI_SOLVED_ENDING[0]);

const ConsoleBlock HANOI_UNSOLVED_ENDING[] = {
    {CONSOLE_NARRATIVE,
     "The puzzle remains unsolved.\n"
     "\n"
     "Take a breath and begin again.\n"
     "The path to enlightenment is still open.\n"},
};

const int HANOI_UNSOLVED_ENDING_COUNT =
    sizeof(HANOI_UNSOLVED_ENDING) / sizeof(HANOI_UNSOLVED_ENDING[0]);

const ConsoleBlock COMPARISON_QUIZ_PAGE[] = {
    {CONSOLE_TEXT,
     "IL CONFRONTO                                          Page 30\n"
     "Soluzione a pagina 46.\n"
     "\n"
     "These two functions differ by just one line.\n"
     "\n"
     "What does each one print?\n"
     "\n"
     "VERSION A                       |  VERSION B\n"
     "                                |\n"
     "void print_values(              |  void print_values(\n"
     "    const int values[],         |     const int values[],\n"
     "    int count) {                |      int count) {\n"
     "                                |\n"
     "    if (count == 0) {           |      if (count == 0) {\n"
     "        return;                 |          return;\n"
     "    }                           |      }\n"
     "                                |\n"
     "    printf(\"%d \",               |       print_values(values,\n"
     "           values[count - 1]);  |                  count - 1);\n"
     "                                |\n"
     "    print_values(values,        |     printf(\"%d \",\n"
     "                 count - 1);    |            values[count - 1]);\n"
     "}                               |     }\n"
     "\n"
     "Given:\n"
     "\n"
     "int values[] = {10, 20, 30, 40};\n"
     "\n"
     "What is printed by Version A?\n"
     "What is printed by Version B?\n"},
};

const int COMPARISON_QUIZ_PAGE_COUNT =
    sizeof(COMPARISON_QUIZ_PAGE) / sizeof(COMPARISON_QUIZ_PAGE[0]);

const ConsoleBlock FACTS_PAGE[] = {
    {CONSOLE_TEXT,
     "FORSE NON TUTTI SANNO CHE...                            Page 40\n"
     "\n"
     "3500044. In C, a function can call itself just like it can call any other function. The language does not have a special \"recursive function\" construct.\n"
     "\n"
     "3500045. A recursive function does not need to call itself directly. Function A may call B, which calls A again. This is known as mutual recursion.\n"
     "\n"
     "3500046. In Merge Sort, splitting the array does not sort anything. The actual sorting happens while the recursive calls return, when already sorted portions are merged back together.\n"
     "\n"
     "3500047. Quick Sort can be very fast on average and still have quadratic worst-case behavior if its partitions are badly unbalanced.\n"
     "\n"
     "3500048. In C, array parameters are adjusted to pointer parameters. These two declarations therefore describe the same parameter type: void f(int values[]); void f(int *values);\n"},
};

const int FACTS_PAGE_COUNT = sizeof(FACTS_PAGE) / sizeof(FACTS_PAGE[0]);
