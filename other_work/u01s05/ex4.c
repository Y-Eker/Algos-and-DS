#include <stdio.h>
#include <string.h>

#define MAX_LEN 31

int check_period(char *s);

int main(void) {
    while (1) {
        char s[MAX_LEN];
        scanf(" %s", s);
        if (strcmp(s, "stop") == 0) break;
        int period = check_period(s);
        if (period)
            printf("String %s is periodic with period %d.\n", s, period);
        else
            printf("String %s is not periodic.\n", s);
    }
    return 0;
}

int check_period(char *s) {
    if (strlen(s) < 2) return 0;
    int period = 0;
    for (int i = 1; s[i] != '\0'; i++) {
        if (s[i] == s[0]) {
            period = i - 0;
            break;
        }
    }
    for (int j = 0; j < strlen(s) - period; j++) {
        if (s[j] != s[j + period])
            return 0;
    }
    return period;
}
