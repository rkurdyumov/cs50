#include <stdio.h>
#include <stdlib.h>

int get_positive_int() {
    char buffer[80];
    char *ret, *tail;
    long n;
    do {
        printf("Height: ");
        ret = fgets(buffer, 80, stdin);
        n = strtol(buffer, &tail, 10);
    } while (n < 1 || n > 8 || ret == NULL || *tail != 0x0a);
    return n;
}

int main(void) {
    int height = get_positive_int();
    for (int row = 1; row <= height; row++) {
        for (int i = 0; i < height - row; i++) {
            printf(" ");
        }
        for (int i = 0; i < row; i++) {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < row; i++) {
            printf("#");
        }
        printf("\n");
    }
}
