#include "station_report.h"

int load_snapshot(FILE *input_file,
                  Station stations[],
                  int *station_count,
                  char query_station_id[STATION_TEXT_CAPACITY]) {
    /* TODO: load and validate the complete station snapshot. */
    return 0;
}

StationTotals compute_totals(const Station stations[], int station_count) {
    /* TODO: compute all aggregate values. */
    StationTotals totals = {0, 0, 0};
    return totals;
}

const Station *find_station_by_id(const Station stations[],
                                  int station_count,
                                  const char *station_id) {
    /* TODO: search for the requested station identifier. */
    return NULL;
}

int find_most_available_station_index(const Station stations[],
                                      int station_count) {
    /* TODO: select the station with the most available bicycles. */
    return -1;
}

int collect_zero_availability_station_indexes(
    const Station stations[],
    int station_count,
    int station_indices[MAX_STATIONS]) {
    /* TODO: collect and order the indices of stations without bicycles. */
    return 0;
}

void build_sorted_indexes_array(const Station stations[],
                                int station_count,
                                int station_indices[MAX_STATIONS]) {
    /* TODO: initialize and sort the complete index view. */
}
