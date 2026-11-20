#include "framework.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_DATASET_VALUE_COUNT 2

int read_integer_dataset(const char filename[],
                         int **values,
                         int *value_count) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        return 0;
    }

    int loaded_value_count;
    if (fscanf(input, "%d", &loaded_value_count) != 1 ||
        loaded_value_count < MINIMUM_DATASET_VALUE_COUNT ||
        loaded_value_count > INT_MAX / (int) sizeof(int)) {
        fclose(input);
        return 0;
    }

    int *loaded_values = malloc(loaded_value_count * sizeof(int));
    if (loaded_values == NULL) {
        fclose(input);
        return 0;
    }

    for (int value_index = 0; value_index < loaded_value_count; value_index++) {
        if (fscanf(input, "%d", &loaded_values[value_index]) != 1) {
            free(loaded_values);
            fclose(input);
            return 0;
        }
    }

    fclose(input);
    *values = loaded_values;
    *value_count = loaded_value_count;
    return 1;
}
