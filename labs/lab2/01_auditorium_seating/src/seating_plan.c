#include "seating_plan.h"

#include <stdlib.h>

typedef struct {
    int start_index;
    int len_from_center;
} Empty_Block;

int load_seating_plan(FILE *input_file, SeatingPlan *seating_plan) {
    /* validate, allocate, and load all physical rows. */
    fscanf(input_file, " %d ", &seating_plan->row_count);
    seating_plan->rows = malloc(seating_plan->row_count * sizeof(SeatRow));
    seating_plan->seat_states = malloc(seating_plan->row_count * sizeof(SeatState*));
    for (int i = 0; i < seating_plan->row_count; i++) {
        SeatRow Row;
        fscanf(input_file, " %c ", &Row.label);
        fscanf(input_file, " %d ", &Row.seat_count);
        seating_plan->rows[i] = Row;
        seating_plan->seat_states[i] = malloc(Row.seat_count * sizeof(SeatState));
        for (int j = 0; j < Row.seat_count; j++) {
            int curr_seat;
            fscanf(input_file, " %d ", &curr_seat);
            switch (curr_seat) {
                case 1:
                {
                    seating_plan->seat_states[i][j] = SEAT_OCCUPIED;
                    break;
                }
                case 0:
                {
                    seating_plan->seat_states[i][j] = SEAT_AVAILABLE;
                    break;
                }
                default:
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int reserve_group_seats(SeatingPlan *seating_plan,
                        int group_size,
                        int *selected_row_index,
                        int *first_seat_index) {
    /* TODO: find, select, and occupy the required consecutive block. */
    Empty_Block empty_blocks[26];
    int empty_counter = 0;
    for (int i = 0; i < seating_plan->row_count; i++) {
        if (seating_plan->rows[i].seat_count < group_size) continue;
        int consecutive_empties = 0;
        for (int j = 0; j < seating_plan->rows[i].seat_count; j++) {
            if (seating_plan->seat_states[i][j] == SEAT_AVAILABLE) consecutive_empties++;
            else consecutive_empties = 0;
            if (consecutive_empties == group_size) {
                empty_blocks[empty_counter].start_index = j - group_size + 1;
                empty_blocks[empty_counter++].len_from_center = (j - group_size/2) - seating_plan->rows[i].seat_count / 2;
            }
        }
        if (empty_counter == 0) continue;
        int index_of_closest_empty_block_to_center = 0;
        for (int j = 0; j < empty_counter; j++) {
            if (empty_blocks[j].len_from_center < empty_blocks[index_of_closest_empty_block_to_center].len_from_center) index_of_closest_empty_block_to_center = j;
        }
        for (int j = empty_blocks[index_of_closest_empty_block_to_center].start_index; j < empty_blocks[index_of_closest_empty_block_to_center].start_index + group_size; j++) {
            seating_plan->seat_states[i][j] = SEAT_OCCUPIED;
        }
        *selected_row_index = i;
        *first_seat_index = empty_blocks[index_of_closest_empty_block_to_center].start_index;
        return 1;
    }
    *selected_row_index = NO_SELECTION;
    *first_seat_index = NO_SELECTION;
    return 0;
}

SeatState **build_centered_seating_map(const SeatingPlan *seating_plan,
                                       int *map_column_count) {
    /* TODO: build the padded map without changing physical seat numbering. */
    return NULL;
}

void destroy_seating_plan(SeatingPlan *seating_plan) {
    /* TODO: release all seat rows and row descriptions. */
}

void destroy_seating_map(SeatState *seating_map[], int map_row_count) {
    /* TODO: release every seating-map row and then its row-pointer array. */
}
