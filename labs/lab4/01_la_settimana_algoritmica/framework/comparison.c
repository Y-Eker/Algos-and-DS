#include "framework.h"

static int comparison_count;

int compare_sorting_values(int left_value, int right_value) {
    comparison_count++;

    if (left_value < right_value) {
        return -1;
    }
    if (left_value > right_value) {
        return 1;
    }
    return 0;
}

void reset_comparison_count(void) {
    comparison_count = 0;
}

int current_comparison_count(void) {
    return comparison_count;
}
