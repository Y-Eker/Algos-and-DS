#include "station_report.h"
#include <string.h>

#define D 2
#define K 10

int check_duplicate_ids(char *curr_id, Station stations[], int station_count);
void sort_indexes_by_id(Station stations[], int* station_indices, int n);
int is_entry_valid(Station station) {
    if (strlen(station.id) < 1 || strlen(station.id) > 31 || strlen(station.name) < 1 ||
            strlen(station.name) > 31) return 0;
    if (station.docks <= 0) return 0;
    if (station.available_bikes < 0 || station.available_bikes > station.docks) return 0;
    if (station.daily_rentals < 0) return 0;
    return 1;
}

int load_snapshot(FILE *input_file,
                  Station stations[],
                  int *station_count,
                  char query_station_id[STATION_TEXT_CAPACITY]) {
    /* load and validate the complete station snapshot. */
    fscanf(input_file, "%d", station_count);
    if (*station_count < 1 || *station_count > 100) return 0;
    int curr_station_num = 0;
    for (int i = 0; i < *station_count; i++) {
        int n_data = fscanf(input_file, " %s %s %d %d %d ", stations[i].id, stations[i].name, &stations[i].docks,
            &stations[i].available_bikes, &stations[i].daily_rentals);
        if (n_data != 5) return 0;
        curr_station_num++;
        if (check_duplicate_ids(stations[i].id, stations, curr_station_num)) return 0;
        if (is_entry_valid(stations[i]) == 0) return 0;
    }
    fscanf(input_file, " %s ", query_station_id);
    return 1;
}
int check_duplicate_ids(char *curr_id, Station stations[], int station_count) {
    for (int i = 0; i < station_count - 1; i++) {
        if (strcmp(curr_id, stations[i].id) == 0) return 1;
    }
    return 0;
}

StationTotals compute_totals(const Station stations[], int station_count) {
    /* compute all aggregate values. */
    StationTotals totals = {0, 0, 0};
    for (int i = 0; i < station_count; i++) {
        totals.total_docks += stations[i].docks;
        totals.total_available += stations[i].available_bikes;
        totals.total_rentals += stations[i].daily_rentals;
    }
    return totals;
}

const Station *find_station_by_id(const Station stations[],
                                  int station_count,
                                  const char *station_id) {
    /* search for the requested station identifier. */
    for (int i = 0; i < station_count; i++) {
        if (strcmp(stations[i].id, station_id) == 0) return &stations[i];
    }
    return NULL;
}

int find_most_available_station_index(const Station stations[],
                                      int station_count) {
    /* select the station with the most available bicycles. */
    int max_available_index = 0;
    for (int i = 0; i < station_count; i++) {
        if (stations[i].available_bikes == stations[max_available_index].available_bikes &&
            strcmp(stations[i].id, stations[max_available_index].id) < 0) max_available_index = i;
        if (stations[i].available_bikes > stations[max_available_index].available_bikes) max_available_index = i;
    }
    return max_available_index;
}

int collect_zero_availability_station_indexes(
    const Station stations[],
    int station_count,
    int station_indices[MAX_STATIONS]) {
    /* collect and order the indices of stations without bicycles. */
    int zero_available_num = 0;
    for (int i = 0; i < station_count; i++) {
        if (stations[i].available_bikes == 0) {
            station_indices[zero_available_num++] = i;
        }
    }
    sort_indexes_by_id(stations, station_indices, zero_available_num);
    return zero_available_num;
}

void build_sorted_indexes_array(const Station stations[],
                                int station_count,
                                int station_indices[MAX_STATIONS]) {
    /* TODO: initialize and sort the complete index view. */
    for (int i = 0; i < station_count; i++) station_indices[i] = i;
    for (int i = 0; i < station_count; i++) {
        int max_index = i;
        for (int j = i + 1; j < station_count; j++) {
            if (stations[station_indices[j]].daily_rentals > stations[station_indices[max_index]].daily_rentals) max_index = j;
        }
        int t = station_indices[i];
        station_indices[i] = station_indices[max_index];
        station_indices[max_index] = t;
    }

    for (int i = 0; i < station_count; i++) {
        int min_index = i;
        for (int j = i + 1; j < station_count; j++) {
            int id_i, id_j;
            sscanf(stations[station_indices[min_index]].id, "S%d", &id_i);
            sscanf(stations[station_indices[j]].id, "S%d", &id_j);
            if (id_j < id_i && stations[station_indices[min_index]].daily_rentals == stations[station_indices[j]].daily_rentals) min_index = j;
        }
        int t = station_indices[i];
        station_indices[i] = station_indices[min_index];
        station_indices[min_index] = t;
    }
}

void sort_indexes_by_id(Station stations[], int* station_indices, int n) {
    for (int i = 0; i < n; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            /* A peculiar bug
            int id_i, id_j;
            sscanf(stations[station_indices[min_index]].id, "S%d", &id_i);
            sscanf(stations[station_indices[j]].id, "S%d", &id_j);
            if (id_j < id_i) min_index = j;
            */
            if (strcmp(stations[station_indices[j]].id, stations[station_indices[min_index]].id) < 0) min_index = j;
        }
        int t = station_indices[i];
        station_indices[i] = station_indices[min_index];
        station_indices[min_index] = t;
    }


    /* Radix sort someday...
    for (int i = 0; i < D; i++) {
        int single_occ_list[K] = {0};
        int mult_occ_list[K] = {0};
        for (int j = 0; j < n; j++) {
            int id;
            sscanf(stations[station_indices[i]].id, "S%d", &id);

        }
    }
    */
}