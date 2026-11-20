#ifndef SORTING_H
#define SORTING_H

/**
 * @brief Orders an integer array in ascending order using recursive Quick Sort.
 *
 * Every comparison between sortable values must use the supplied helper:
 * @link compare_sorting_values
 * compare_sorting_values(int left_value, int right_value)
 * @endlink
 * The helper is declared in rules.h and already implemented by the framework.
 * Include rules.h in sorting.c and call the helper; do not implement or
 * redefine it. Direct value comparisons cannot be recorded by the magazine
 * and therefore do not count in the competition.
 *
 * @param[in,out] values Values to order.
 * @param[in] value_count Number of elements in values.
 * @return 1 after completing the sort, or 0 when it cannot be completed. An
 *         array of zero elements is already ordered and therefore returns 1.
 */
int quick_sort(int values[], int value_count);

/**
 * @brief Orders an integer array in ascending order using recursive Merge Sort.
 *
 * Every comparison between sortable values must use the supplied helper:
 * @link compare_sorting_values
 * compare_sorting_values(int left_value, int right_value)
 * @endlink
 * The helper is declared in rules.h and already implemented by the framework.
 * Include rules.h in sorting.c and call the helper; do not implement or
 * redefine it. Direct value comparisons cannot be recorded by the magazine
 * and therefore do not count in the competition.
 *
 * @param[in,out] values Values to order.
 * @param[in] value_count Number of elements in values.
 * @return 1 after completing the sort, or 0 when it cannot be completed. An
 *         array of zero elements is already ordered and therefore returns 1.
 */
int merge_sort(int values[], int value_count);

/**
 * @brief Orders an integer array in ascending order using a chosen strategy.
 *
 * Every comparison between sortable values must use the supplied helper:
 * @link compare_sorting_values
 * compare_sorting_values(int left_value, int right_value)
 * @endlink
 * The helper is declared in rules.h and already implemented by the framework.
 * Include rules.h in sorting.c and call the helper; do not implement or
 * redefine it. Direct value comparisons cannot be recorded by the magazine
 * and therefore do not count in the competition.
 *
 * @param[in,out] values Values to order.
 * @param[in] value_count Number of elements in values.
 * @return 1 after completing the sort, or 0 when it cannot be completed. An
 *         array of zero elements is already ordered and therefore returns 1.
 */
int my_sort(int values[], int value_count);

#endif
