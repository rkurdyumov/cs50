#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TEMP_FILENAME "###.jpg"
typedef uint8_t  BYTE;
const int NUM_BLOCK_BYTES = 512;

bool is_jpeg_header(BYTE *block) {
    return (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open image file %s\n", argv[1]);
        return 1;
    }
    BYTE block[NUM_BLOCK_BYTES];
    char filename[] = TEMP_FILENAME;
    FILE *img = fopen(filename, "w");
    int i = 0;
    while (fread(block, NUM_BLOCK_BYTES, 1, file) == 1) {
        if (is_jpeg_header(block)) {
            fclose(img);
            sprintf(filename, "%03i.jpg", i++);
            img = fopen(filename, "w");
        }
        fwrite(block, NUM_BLOCK_BYTES, 1, img);
    }
    fclose(img);
    fclose(file);
    remove(TEMP_FILENAME);
}
