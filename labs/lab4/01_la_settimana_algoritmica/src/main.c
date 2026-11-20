#include "framework.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reports whether the optional narrative mode was requested. */
static int parse_verbose(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    int verbose = parse_verbose(argc, argv);
    if (verbose < 0) {
        return EXIT_FAILURE;
    }
    magazine_open(verbose);

    MagazinePage page = INDEX_PAGE;
    while (page != MAGAZINE_CLOSED) {
        switch (page) {
        case PALINDROME_PAGE:
            run_palindrome_challenge();
            page = RECURSION_PAGE;
            break;
        case SECRET_CODE_PAGE:
            run_secret_code_challenge();
            page = RECURSION_PAGE;
            break;
        case CARD_PAGE:
            run_card_challenge();
            page = RECURSION_PAGE;
            break;
        case HANOI_PAGE:
            run_hanoi_challenge();
            page = RECURSION_PAGE;
            break;
        case SORTING_PAGE:
            run_sorting_competition();
            page = INDEX_PAGE;
            break;
        default:
            page = magazine_choose_page(page);
            break;
        }
    }
    magazine_close();
    return EXIT_SUCCESS;
}

static int parse_verbose(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "--verbose") == 0) {
        return 1;
    }
    fprintf(stderr, "Usage: la_settimana_algoritmica [--verbose]\n");
    return -1;
}
