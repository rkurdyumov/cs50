#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum CardType {AMEX, MASTERCARD, VISA, INVALID} CardType;
const char *CardTypeToString[] = {"AMEX", "MASTERCARD", "VISA", "INVALID"};

long get_long() {
    const int BUFFER_SIZE = 80;
    char buffer[BUFFER_SIZE];
    char *ret, *tail;
    long n;
    do {
        printf("Number: ");
        ret = fgets(buffer, BUFFER_SIZE, stdin);
        n = strtol(buffer, &tail, 10);
    } while (n < 0 || ret == NULL || *tail != 0x0a);
    return n;
}

bool is_valid_number(char *n_str) {  // Use Luhn's algorithm.
    int sum = 0;
    for (int i = strlen(n_str) - 2; i >= 0; i-= 2) {
        int product = 2 * (n_str[i] - '0');
        sum += product >= 10 ? 1 + (product % 10) : product;
    }
    for (int i = strlen(n_str) - 1; i >= 0; i-= 2) {
        sum += n_str[i] - '0';
    }
    return sum % 10 == 0;
}

CardType get_card_type(long n) {
    char n_str[21];  // LONG_MAX = 9223372036854775807
    sprintf(n_str, "%ld", n);
    CardType type = INVALID;
    char pre[3];
    strncpy(pre, n_str, 2);
    pre[2] = '\0';
    int len = strlen(n_str);
    if (len == 15 && (!strcmp(pre, "34") || !strcmp(pre, "37"))) {
        type = AMEX;
    } else if (len == 16 && strcmp(pre, "50") > 0 && strcmp(pre, "56") < 0) {
        type = MASTERCARD;
    } else if ((len == 13 || len == 16) && pre[0] == '4') {
        type = VISA;
    }
    type = is_valid_number(n_str) ? type : INVALID;
    return type;
}

int main(void) {
    long n = get_long();
    printf("%s\n", CardTypeToString[get_card_type(n)]);
}
