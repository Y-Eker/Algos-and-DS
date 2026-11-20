#include "word_index.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *str_lower(char* s) {
    char* result = malloc(strlen(s) + 1 * sizeof(*result));
    for (int i = 0; i < strlen(s); i++) {
        if (isupper(s[i])) result[i] = tolower(s[i]);
        else result[i] = s[i];
    }
    return result;
}

WordEntry *load_word_index(FILE *input, int *word_count) {
    if (fscanf(input, "%d", word_count) != 1 || *word_count <= 0) {
        return NULL;
    }
    WordEntry *entries = malloc((size_t)*word_count * sizeof(*entries));
    if (entries == NULL) {
        return NULL;
    }
    for (int i = 0; i < *word_count; i++) {
        if (fscanf(input, "%30s", entries[i].word) != 1) {
            free(entries);
            return NULL;
        }
        entries[i].occurrences = 0;
    }
    return entries;
}

int find_word(const WordEntry word_entries[],
              int word_count,
              const char *word) {
    /* implement a case-insensitive search. */
    for (int i = 0; i < word_count; i++) {
        if (strcmp(str_lower(word_entries[i].word), str_lower(word)) == 0) {
            return i;
        }
    }
    return -1;
}

int count_words(FILE *input, WordEntry word_entries[], int word_count) {
    /* scan the text and update occurrence counters. */
    char word[31];
    while (fscanf(input, "%30s", word) == 1) {
        int res = find_word(word_entries, word_count, word);
        if (res >= 0) {
            word_entries[res].occurrences++;
        }
    }
    return 1;
}

void destroy_word_index(WordEntry word_entries[]) {
    /* release the array representation. */
    free(word_entries);
}

