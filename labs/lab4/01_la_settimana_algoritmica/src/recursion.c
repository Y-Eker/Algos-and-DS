#include "recursion.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void normalize_text(char *text, char *result) {
    int result_index = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            result[result_index++] = tolower(text[i]);
        }
    }
    result[result_index] = '\0';
}



PalindromeResult check_palindrome(char *text, int step) {
    if (strlen(text) == 0) return PALINDROME_INVALID_TEXT;
    if (strlen(text) == 1 || text[0] != text[strlen(text) - 1]) return PALINDROME_NOT_FOUND;
    if (strlen(text) / 2 == step) return PALINDROME_FOUND;
    if (text[step] != text[strlen(text) - 1 - step]) return PALINDROME_NOT_FOUND;


    return check_palindrome(text, step+1);
}

PalindromeResult recognize_palindrome(const char text[]) {
    /* normalize the text and perform the recursive check. */
    char *normalized = malloc((strlen(text) + 1) * sizeof(char));
    if (!normalized) return PALINDROME_ERROR;
    normalize_text(text, normalized);

    PalindromeResult Res = check_palindrome(normalized, 0);
    free(normalized);
    return Res;
}

void reverse(char *bits, int step) {
    for (int i = 0; i < step / 2; i++) {
        char t = bits[i];
        bits[i] = bits[step - 1 - i];
        bits[step - 1 - i] = t;
    }
}

void recursive_binary_converter(unsigned int decimal_number, char *binary_digits, int step) {
    if (decimal_number == 0) {
        reverse(binary_digits, step);
        binary_digits[step] = '\0';
        return;
    }
    binary_digits[step] = decimal_number % 2 + '0';
    recursive_binary_converter(decimal_number / 2, binary_digits, step + 1);
}

void generate_secret_code(unsigned int decimal_number, char binary_digits[]) {
    /* generate the binary digits recursively. */
    if (decimal_number == 0) {
        binary_digits[0] = '0';
        binary_digits[1] = '\0';
    }
    else {
        recursive_binary_converter(decimal_number, binary_digits, 0);
    }
}

int guess_card(void) {
    /* TODO: find the card using recursive search. */

    return 0;
}

void solve_towers_of_hanoi(int disk_count) {
    /* TODO: generate the optimal recursive move sequence. */
}
