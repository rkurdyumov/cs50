#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NUM_LETTERS 26

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != NUM_LETTERS) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    char keys[NUM_LETTERS] = {0};
    bool used[NUM_LETTERS] = {false};
    for (int i = 0; i < strlen(argv[1]); i++) {
        char key = tolower(argv[1][i]);  //
        if (!isalpha(key)) {
            printf("Key must be alphabetic.\n");
            return 1;
        }
        if (used[key - 'a']) {
            printf("Key must contain each letter exactly once.\n");
            return 1;
        }
        keys[i] = key;
        used[key - 'a'] = true;
    }
    char plaintext[1000], ciphertext[1000];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    for (int i = 0; i < strlen(plaintext); i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char new_c = keys[tolower(plaintext[i]) - 'a'];
            ciphertext[i] = isupper(c) ? toupper(new_c) : new_c;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
