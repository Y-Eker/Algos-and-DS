#include "framework.h"

#include "sorting.h"

#include <stdlib.h>

#include "aads_console/aads_console.h"
#include "story.h"

#define SORTING_COMPETITOR_COUNT 3
#define NO_POSITION 0

typedef struct {
    const char *name;
    int comparison_count;
    int total_points;
    int valid_round_count;
    int is_valid;
    const char *disqualification_reason;
} SortingCompetitor;

static int *copy_integer_values(const int values[], int value_count);
static int call_sorting_algorithm(int competitor_index,
                                  int values[],
                                  int value_count);
static void run_competitor(SortingCompetitor *competitor,
                           int competitor_index,
                           const int original_values[],
                           int value_count);
static int determine_round_position(const SortingCompetitor competitors[],
                                    int competitor_index);
static void award_round_points(SortingCompetitor competitors[]);
static int run_sorting_round(const ConsoleBlock round_name[],
                             int round_name_count,
                             const ConsoleBlock introduction[],
                             int introduction_count,
                             const char filename[],
                             SortingCompetitor competitors[]);
static int determine_final_position(const SortingCompetitor competitors[],
                                    int competitor_index);
static void print_standings(const SortingCompetitor competitors[], int final);

void run_sorting_competition(void) {
    SortingCompetitor competitors[SORTING_COMPETITOR_COUNT] = {
        {"Quick Step", 0, 0, 0, 0, NULL},
        {"Merge Ahead", 0, 0, 0, 0, NULL},
        {"Free Rein", 0, 0, 0, 0, NULL}};

    print_blocks(SORTING_TITLE, SORTING_TITLE_COUNT, NULL, 0);
    if (magazine_is_verbose()) {
        print_blocks(SORTING_INTRO, SORTING_INTRO_COUNT, NULL, 0);
        add_pause();
    }
    if (!run_sorting_round(RACE_1_TITLE,
                           RACE_1_TITLE_COUNT,
                           RACE_1_INTRO,
                           RACE_1_INTRO_COUNT,
                           "data/random.txt",
                           competitors) ||
        !run_sorting_round(RACE_2_TITLE,
                           RACE_2_TITLE_COUNT,
                           RACE_2_INTRO,
                           RACE_2_INTRO_COUNT,
                           "data/sorted.txt",
                           competitors) ||
        !run_sorting_round(RACE_3_TITLE,
                           RACE_3_TITLE_COUNT,
                           RACE_3_INTRO,
                           RACE_3_INTRO_COUNT,
                           "data/reverse.txt",
                           competitors) ||
        !run_sorting_round(RACE_4_TITLE,
                           RACE_4_TITLE_COUNT,
                           RACE_4_INTRO,
                           RACE_4_INTRO_COUNT,
                           "data/duplicates.txt",
                           competitors)) {
        return;
    }
    print_standings(competitors, 1);
    if (magazine_is_verbose()) {
        report("\n");
        print_blocks(SORTING_CLOSING, SORTING_CLOSING_COUNT, NULL, 0);
    }
    add_pause();
}

static int *copy_integer_values(const int values[], int value_count) {
    int *values_copy = malloc(value_count * sizeof(int));
    if (values_copy == NULL) {
        return NULL;
    }

    for (int value_index = 0; value_index < value_count; value_index++) {
        values_copy[value_index] = values[value_index];
    }
    return values_copy;
}

int sorting_result_is_valid(const int input_values[],
                            const int output_values[],
                            int value_count) {
    for (int value_index = 0; value_index < value_count; value_index++) {
        if (value_index > 0 &&
            output_values[value_index - 1] > output_values[value_index]) {
            return 0;
        }
        int input_occurrences = 0;
        int output_occurrences = 0;
        for (int other_value_index = 0; other_value_index < value_count;
             other_value_index++) {
            input_occurrences +=
                input_values[other_value_index] == output_values[value_index];
            output_occurrences +=
                output_values[other_value_index] == output_values[value_index];
        }
        if (input_occurrences != output_occurrences) {
            return 0;
        }
    }
    return 1;
}

static int call_sorting_algorithm(int competitor_index,
                                  int values[],
                                  int value_count) {
    if (competitor_index == 0) {
        return quick_sort(values, value_count);
    }
    if (competitor_index == 1) {
        return merge_sort(values, value_count);
    }
    return my_sort(values, value_count);
}

static void run_competitor(SortingCompetitor *competitor,
                           int competitor_index,
                           const int original_values[],
                           int value_count) {
    int *values_copy = copy_integer_values(original_values, value_count);
    competitor->comparison_count = 0;
    competitor->is_valid = 0;
    competitor->disqualification_reason = NULL;
    if (values_copy == NULL) {
        competitor->disqualification_reason = "cannot allocate the input copy";
        return;
    }

    reset_comparison_count();
    int sorting_completed =
        call_sorting_algorithm(competitor_index, values_copy, value_count);
    competitor->comparison_count = current_comparison_count();
    if (!sorting_completed) {
        competitor->disqualification_reason = "the algorithm reported failure";
    } else if (!sorting_result_is_valid(original_values,
                                        values_copy,
                                        value_count)) {
        competitor->disqualification_reason =
            "the result is not an ordered copy of the input values";
    } else if (competitor->comparison_count == 0) {
        competitor->disqualification_reason =
            "no value comparisons were recorded through compare_sorting_values";
    } else {
        competitor->is_valid = 1;
    }
    free(values_copy);
}

static int determine_round_position(const SortingCompetitor competitors[],
                                    int competitor_index) {
    int round_position = 1;

    for (int other_competitor_index = 0;
         other_competitor_index < SORTING_COMPETITOR_COUNT;
         other_competitor_index++) {
        if (competitors[other_competitor_index].is_valid &&
            competitors[other_competitor_index].comparison_count <
                competitors[competitor_index].comparison_count) {
            round_position++;
        }
    }
    return round_position;
}

static void award_round_points(SortingCompetitor competitors[]) {
    int round_positions[SORTING_COMPETITOR_COUNT];

    for (int competitor_index = 0; competitor_index < SORTING_COMPETITOR_COUNT;
         competitor_index++) {
        round_positions[competitor_index] = NO_POSITION;
        if (!competitors[competitor_index].is_valid) {
            continue;
        }

        round_positions[competitor_index] =
            determine_round_position(competitors, competitor_index);
        competitors[competitor_index].total_points +=
            SORTING_COMPETITOR_COUNT + 1 - round_positions[competitor_index];
        competitors[competitor_index].valid_round_count++;
    }

    report("\nRACE RESULTS\n\n");
    for (int position = 1; position <= SORTING_COMPETITOR_COUNT; position++) {
        int awarded_points = SORTING_COMPETITOR_COUNT + 1 - position;
        for (int competitor_index = 0;
             competitor_index < SORTING_COMPETITOR_COUNT;
             competitor_index++) {
            if (round_positions[competitor_index] == position) {
                report("%d. %-15s %d comparisons   %d point%s\n",
                       position,
                       competitors[competitor_index].name,
                       competitors[competitor_index].comparison_count,
                       awarded_points,
                       awarded_points == 1 ? "" : "s");
            }
        }
    }
    for (int competitor_index = 0; competitor_index < SORTING_COMPETITOR_COUNT;
         competitor_index++) {
        if (!competitors[competitor_index].is_valid) {
            report("-  %-15s DISQUALIFIED\n   Reason: %s.\n",
                   competitors[competitor_index].name,
                   competitors[competitor_index].disqualification_reason);
        }
    }
    if (magazine_is_verbose()) {
        report("4. Hi-Hat\n");
    }
}

static int run_sorting_round(const ConsoleBlock round_name[],
                             int round_name_count,
                             const ConsoleBlock introduction[],
                             int introduction_count,
                             const char filename[],
                             SortingCompetitor competitors[]) {
    int *original_values;
    int value_count;
    if (!read_integer_dataset(filename, &original_values, &value_count)) {
        report("\nCannot load the prepared dataset: %s\n"
               "The sorting competition ends here.\n",
               filename);
        add_pause();
        return 0;
    }
    report("\n");
    print_blocks(round_name, round_name_count, NULL, 0);
    report("\n");
    if (magazine_is_verbose()) {
        print_blocks(introduction, introduction_count, NULL, 0);
    }
    report("Input: %d values\n", value_count);
    for (int value_index = 0; value_index < value_count; value_index++) {
        report("%d%s",
               original_values[value_index],
               value_index == value_count - 1 ? "\n" : " ");
    }
    add_pause();
    print_separator();
    int valid_competitor_count = 0;
    for (int competitor_index = 0; competitor_index < SORTING_COMPETITOR_COUNT;
         competitor_index++) {
        run_competitor(&competitors[competitor_index],
                       competitor_index,
                       original_values,
                       value_count);
        valid_competitor_count += competitors[competitor_index].is_valid;
    }
    report("\n");
    print_separator();
    free(original_values);
    if (valid_competitor_count == 0) {
        report("\nRACE RESULTS\n\n");
        for (int competitor_index = 0;
             competitor_index < SORTING_COMPETITOR_COUNT;
             competitor_index++) {
            report("%-15s DISQUALIFIED\n", competitors[competitor_index].name);
        }
        if (magazine_is_verbose()) {
            report("4. Hi-Hat\n");
        }
        report("\nNo valid competitor completed the race.\n\n");
        for (int competitor_index = 0;
             competitor_index < SORTING_COMPETITOR_COUNT;
             competitor_index++) {
            report("%s: %s.\n",
                   competitors[competitor_index].name,
                   competitors[competitor_index].disqualification_reason);
        }
        report(magazine_is_verbose() ? "\nThe sorting competition ends here.\n"
                                     : "\nChallenge lost.\n");
        add_pause();
        return 0;
    }
    award_round_points(competitors);
    print_standings(competitors, 0);
    add_pause();
    return 1;
}

static int determine_final_position(const SortingCompetitor competitors[],
                                    int competitor_index) {
    int final_position = 1;

    for (int other_competitor_index = 0;
         other_competitor_index < SORTING_COMPETITOR_COUNT;
         other_competitor_index++) {
        if (competitors[other_competitor_index].valid_round_count > 0 &&
            competitors[other_competitor_index].total_points >
                competitors[competitor_index].total_points) {
            final_position++;
        }
    }
    return final_position;
}

static void print_standings(const SortingCompetitor competitors[], int final) {
    int final_positions[SORTING_COMPETITOR_COUNT];

    for (int competitor_index = 0; competitor_index < SORTING_COMPETITOR_COUNT;
         competitor_index++) {
        final_positions[competitor_index] = NO_POSITION;
        if (competitors[competitor_index].valid_round_count == 0) {
            continue;
        }

        final_positions[competitor_index] =
            determine_final_position(competitors, competitor_index);
    }

    report(final ? "\nFINAL STANDINGS\n\n" : "\nSTANDINGS\n\n");
    for (int position = 1; position <= SORTING_COMPETITOR_COUNT; position++) {
        for (int competitor_index = 0;
             competitor_index < SORTING_COMPETITOR_COUNT;
             competitor_index++) {
            if (final_positions[competitor_index] == position) {
                report("%d. %-15s %d point%s\n",
                       position,
                       competitors[competitor_index].name,
                       competitors[competitor_index].total_points,
                       competitors[competitor_index].total_points == 1 ? ""
                                                                       : "s");
            }
        }
    }

    for (int competitor_index = 0; competitor_index < SORTING_COMPETITOR_COUNT;
         competitor_index++) {
        if (final_positions[competitor_index] == NO_POSITION) {
            report("- %s   DISQUALIFIED\n", competitors[competitor_index].name);
        }
    }
    if (magazine_is_verbose()) {
        report("4. Hi-Hat\n");
    }
}
