#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char words[1000];
    printf("Text: ");
    fgets(words, sizeof(words), stdin);
    int num_letters = 0, num_words = 0, num_sentences = 0;
    for (int i = 0; i < strlen(words); i++) {
        if (words[i] == ' ') {
            num_words++;
        } else if (isalpha(words[i])) {
            num_letters++;
        } else if (words[i] == '.' || words[i] == '?' || words[i] == '!') {
            num_sentences++;
        }
    }
    num_words++;
    float L = (float)num_letters / num_words * 100;
    float S = (float)num_sentences / num_words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1) {
        printf("Before Grade 1\n");
    } else if (index > 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %d\n", index);
    }
}

