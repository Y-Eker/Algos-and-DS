#include "word_index.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *str_lower(char* s) {
    char* result = malloc(strlen(s + 1) * sizeof(*result));
    for (int i = 0; i < strlen(s); i++) {
        if (isupper(s[i])) result[i] = tolower(s[i]);
        else result[i] = s[i];
    }
    return result;
}

WordEntry *load_word_index(FILE *input, int *word_count) {
    /* allocate and load the array representation. */
    fscanf(input, "%d", word_count);
    WordEntry *entries = malloc(*word_count * sizeof(*entries));
    for (int i = 0; i < *word_count; i++) {
        char *word;
        fscanf(input, "%s", word);
        strcpy(entries[i].word, word);
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
    /* TODO: scan the text and update occurrence counters. */
    for (int i = 0; i < word_count; i++) {
        char* word;
        fscanf(input, "%s", word);
        if (find_word(word_entries, word_count, word)) {};
    }

    return 0;
}

void destroy_word_index(WordEntry word_entries[]) {
    /* TODO: release the array representation. */
}

