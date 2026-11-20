#include "framework.h"

#include <stddef.h>
#include <string.h>

#define HANOI_TOWER_COUNT 3

static const char *const tower_names[HANOI_TOWER_COUNT] = {
    "Tower of Wisdom",
    "Tower of Inner Peace",
    "Tower of Enlightenment"};

static int tower_disks[HANOI_TOWER_COUNT][HANOI_MAX_DISK_COUNT];
static int tower_heights[HANOI_TOWER_COUNT];
static int challenge_disk_count;
static int recorded_move_count;
static int challenge_is_active;
static int challenge_is_valid;
static int hanoi_output_is_enabled;
static int rejected_disk_number;
static Tower rejected_source_tower;
static Tower rejected_destination_tower;
static const char *rejection_reason;
static int show_attempted_state;

static int tower_index_from_name(Tower tower_name);
static const char *printable_tower_name(Tower tower_name);
static void print_repeated_character(char character, int repetition_count);
static void print_tower_cell(int disk_number, int cell_width);
static void render_hanoi_towers(int displayed_towers[][HANOI_MAX_DISK_COUNT],
                                const int displayed_heights[]);
static void render_forbidden_hanoi_state(int disk_number,
                                         int source_tower_index,
                                         int destination_tower_index,
                                         int show_attempted_result);
static int reject_hanoi_move(int disk_number,
                             Tower source_tower,
                             Tower destination_tower,
                             const char message[],
                             int show_attempted_result);

void begin_hanoi_challenge(int disk_count, int output_is_enabled) {
    for (int tower_index = 0; tower_index < HANOI_TOWER_COUNT; tower_index++) {
        tower_heights[tower_index] = 0;
        for (int disk_index = 0; disk_index < HANOI_MAX_DISK_COUNT;
             disk_index++) {
            tower_disks[tower_index][disk_index] = 0;
        }
    }

    challenge_disk_count = disk_count;
    recorded_move_count = 0;
    challenge_is_active = 1;
    challenge_is_valid = disk_count >= 1 && disk_count <= HANOI_MAX_DISK_COUNT;
    hanoi_output_is_enabled = output_is_enabled;
    rejection_reason = NULL;
    show_attempted_state = 0;

    if (!challenge_is_valid) {
        return;
    }

    tower_heights[TOWER_WISDOM] = disk_count;
    for (int disk_index = 0; disk_index < disk_count; disk_index++) {
        tower_disks[TOWER_WISDOM][disk_index] = disk_count - disk_index;
    }
}

int move_hanoi_disk(int disk_number,
                    Tower source_tower,
                    Tower destination_tower) {
    if (!challenge_is_active || !challenge_is_valid) {
        return 0;
    }

    int source_tower_index = tower_index_from_name(source_tower);
    int destination_tower_index = tower_index_from_name(destination_tower);
    if (source_tower_index < 0 || destination_tower_index < 0) {
        return reject_hanoi_move(disk_number,
                                 source_tower,
                                 destination_tower,
                                 "unknown tower",
                                 0);
    }
    if (source_tower_index == destination_tower_index) {
        return reject_hanoi_move(
            disk_number,
            source_tower,
            destination_tower,
            "source and destination tower cannot be the same",
            0);
    }
    if (disk_number < 1 || disk_number > challenge_disk_count) {
        return reject_hanoi_move(disk_number,
                                 source_tower,
                                 destination_tower,
                                 "unknown disk",
                                 0);
    }
    if (tower_heights[source_tower_index] == 0 ||
        tower_disks[source_tower_index]
                   [tower_heights[source_tower_index] - 1] != disk_number) {
        return reject_hanoi_move(disk_number,
                                 source_tower,
                                 destination_tower,
                                 "the selected disk is not available",
                                 0);
    }
    if (tower_heights[destination_tower_index] > 0 &&
        tower_disks[destination_tower_index]
                   [tower_heights[destination_tower_index] - 1] < disk_number) {
        return reject_hanoi_move(disk_number,
                                 source_tower,
                                 destination_tower,
                                 "a larger disk cannot cover a smaller disk",
                                 1);
    }
    tower_heights[source_tower_index]--;
    tower_disks[destination_tower_index]
               [tower_heights[destination_tower_index]] = disk_number;
    tower_heights[destination_tower_index]++;
    recorded_move_count++;

    return 1;
}

void end_hanoi_challenge(void) {
    if (!challenge_is_active) {
        return;
    }
    challenge_is_active = 0;
    if (!hanoi_output_is_enabled || hanoi_puzzle_was_solved()) {
        return;
    }
    if (rejection_reason != NULL) {
        report("\nStep %d FORBIDDEN\n\n"
               "Move: disk %d from %s to %s\n"
               "Reason: %s.\n\n",
               recorded_move_count + 1,
               rejected_disk_number,
               printable_tower_name(rejected_source_tower),
               printable_tower_name(rejected_destination_tower),
               rejection_reason);
    } else {
        report("\nThe complete stack did not reach the "
               "Tower of Enlightenment.\n\n");
    }
    report("CURRENT STATE\n\n");
    render_hanoi_towers(tower_disks, tower_heights);
    if (show_attempted_state) {
        report("\nThat move would produce:\n\n");
        render_forbidden_hanoi_state(
            rejected_disk_number,
            tower_index_from_name(rejected_source_tower),
            tower_index_from_name(rejected_destination_tower),
            1);
        report("\nDisk %d would rest on a smaller disk.\n",
               rejected_disk_number);
    }
}

int hanoi_puzzle_was_solved(void) {
    return challenge_is_valid && tower_heights[TOWER_WISDOM] == 0 &&
           tower_heights[TOWER_INNER_PEACE] == 0 &&
           tower_heights[TOWER_ENLIGHTENMENT] == challenge_disk_count;
}

int hanoi_challenge_was_won(void) {
    return hanoi_puzzle_was_solved() &&
           recorded_move_count ==
               minimum_hanoi_move_count(challenge_disk_count);
}

int hanoi_move_count(void) {
    return recorded_move_count;
}

int minimum_hanoi_move_count(int disk_count) {
    return (1 << disk_count) - 1;
}

static int tower_index_from_name(Tower tower_name) {
    if (tower_name < TOWER_WISDOM || tower_name > TOWER_ENLIGHTENMENT) {
        return -1;
    }
    return (int) tower_name;
}

static const char *printable_tower_name(Tower tower_name) {
    if (tower_index_from_name(tower_name) < 0) {
        return "unknown tower";
    }
    return tower_names[tower_name];
}

static int reject_hanoi_move(int disk_number,
                             Tower source_tower,
                             Tower destination_tower,
                             const char message[],
                             int show_attempted_result) {
    challenge_is_valid = 0;
    rejected_disk_number = disk_number;
    rejected_source_tower = source_tower;
    rejected_destination_tower = destination_tower;
    rejection_reason = message;
    show_attempted_state = show_attempted_result;
    return 0;
}

static void render_forbidden_hanoi_state(int disk_number,
                                         int source_tower_index,
                                         int destination_tower_index,
                                         int show_attempted_result) {
    int displayed_towers[HANOI_TOWER_COUNT][HANOI_MAX_DISK_COUNT];
    int displayed_heights[HANOI_TOWER_COUNT];

    for (int tower_index = 0; tower_index < HANOI_TOWER_COUNT; tower_index++) {
        displayed_heights[tower_index] = tower_heights[tower_index];
        for (int disk_index = 0; disk_index < HANOI_MAX_DISK_COUNT;
             disk_index++) {
            displayed_towers[tower_index][disk_index] =
                tower_disks[tower_index][disk_index];
        }
    }

    if (show_attempted_result) {
        displayed_heights[source_tower_index]--;
        displayed_towers[destination_tower_index]
                        [displayed_heights[destination_tower_index]] =
                            disk_number;
        displayed_heights[destination_tower_index]++;
    }

    render_hanoi_towers(displayed_towers, displayed_heights);
}

static void print_repeated_character(char character, int repetition_count) {
    for (int repetition_index = 0; repetition_index < repetition_count;
         repetition_index++) {
        report("%c", character);
    }
}

static void print_tower_cell(int disk_number, int cell_width) {
    int disk_width = disk_number == 0 ? 1 : 2 * disk_number + 1;
    int left_padding = (cell_width - disk_width) / 2;
    int right_padding = cell_width - disk_width - left_padding;

    print_repeated_character(' ', left_padding);
    if (disk_number == 0) {
        report("|");
    } else {
        print_repeated_character('=', disk_number);
        report("|");
        print_repeated_character('=', disk_number);
    }
    print_repeated_character(' ', right_padding);
}

static void render_hanoi_towers(int displayed_towers[][HANOI_MAX_DISK_COUNT],
                                const int displayed_heights[]) {
    int cell_width = 2 * challenge_disk_count + 3;
    for (int tower_index = 0; tower_index < HANOI_TOWER_COUNT; tower_index++) {
        int name_width = (int) strlen(tower_names[tower_index]);
        if (cell_width < name_width) {
            cell_width = name_width;
        }
    }

    for (int tower_level = challenge_disk_count; tower_level > 0;
         tower_level--) {
        for (int tower_index = 0; tower_index < HANOI_TOWER_COUNT;
             tower_index++) {
            int disk_number = 0;
            if (tower_level <= displayed_heights[tower_index]) {
                disk_number = displayed_towers[tower_index][tower_level - 1];
            }
            print_tower_cell(disk_number, cell_width);
            if (tower_index < HANOI_TOWER_COUNT - 1) {
                report("   ");
            }
        }
        report("\n");
    }

    for (int tower_index = 0; tower_index < HANOI_TOWER_COUNT; tower_index++) {
        print_repeated_character('-', cell_width);
        if (tower_index < HANOI_TOWER_COUNT - 1) {
            report("   ");
        }
    }
    report("\n");

    for (int tower_index = 0; tower_index < HANOI_TOWER_COUNT; tower_index++) {
        int name_width = (int) strlen(tower_names[tower_index]);
        int left_padding = (cell_width - name_width) / 2;
        print_repeated_character(' ', left_padding);
        report("%s", tower_names[tower_index]);
        print_repeated_character(' ', cell_width - left_padding - name_width);
        if (tower_index < HANOI_TOWER_COUNT - 1) {
            report("   ");
        }
    }
    report("\n\n");
}
