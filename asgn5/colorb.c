#include "bmp.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt = 0;

    char *input = NULL;
    char *output = NULL;

    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
        switch (opt) {
        case 'i': input = (optarg); break;
        case 'o': output = (optarg); break;
        case 'h': printf("Help Page"); return 0;
        default: break;
        }
    }
    if (input == NULL) {
        fprintf(stderr, "No input file");
        exit(1);
    }
    if (output == NULL) {
        fprintf(stderr, "No output file");
        exit(1);
    }
    //fprintf(stderr, "%s", input);
    Buffer *bufrd = read_open(input);
    if (bufrd == NULL)
        fprintf(stderr, "null pointer");
    BMP *bmp = bmp_create(bufrd);
    read_close(&bufrd);
    if (bmp == NULL) {
        fprintf(stderr, "Error creating bmp");
    }
    bmp_reduce_palette(bmp);
    Buffer *bufwr = write_open(output);
    bmp_write(bmp, bufwr);
    bmp_free(&bmp);
    write_close(&bufwr);
}
