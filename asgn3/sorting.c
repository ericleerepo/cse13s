#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void array(uint32_t *arr, int seed, int size) {
    srandom(seed);
    for (int i = 0; i < size; i++) {
        int temp = random();
        temp = temp & 1073741823;
        arr[i] = temp;
    }
}

int main(int argc, char *argv[]) {
    extern char *optarg;

    Stats stats;
    Set options = set_empty();
    int opt = 0;
    int seed = 13371453;
    int size = 100;
    int elements = 100;
    while ((opt = getopt(argc, argv, "aishqbr:n:p:H")) != -1) {
        switch (opt) {
        case 'a': options = set_universal(); break;
        case 'i': options = set_insert(options, 1); break;
        case 's': options = set_insert(options, 2); break;
        case 'h': options = set_insert(options, 3); break;
        case 'q': options = set_insert(options, 4); break;
        case 'b': options = set_insert(options, 5); break;
        case 'r': seed = atoi(optarg); break;
        case 'n': size = atoi(optarg); break;
        case 'p': elements = atoi(optarg); break;
        case 'H':
            printf("-a: runs all the algorithms\n-i: runs Insertion Sort\n-s: runs Shell Sort\n-h: "
                   "runs Heap Sort\n-q: runs Quick Sort\n-b: runs Batcher Sort\n-r seed: sets the "
                   "random seed which the user enters. The default seed is 13371453.\n-n size: "
                   "sets the size of the array which the user enters. The default size is 100.\n-p "
                   "elements: sets the amount of elements printed which the user enters. The "
                   "default size is 100 and a size of 0 will print nothing.");
            break;
        default: break;
        }
    }
    uint32_t *arr = calloc(size, sizeof(int));
    if (set_member(options, 1)) {
        reset(&stats);
        array(arr, seed, size);
        insertion_sort(&stats, arr, size);
        char name[] = "Insertion Sort";
        print_stats(&stats, name, size);
        int i = 0;
        int count = 0;
        if (elements > 0 && size > 0) {
            while (i < elements && i < size) {
                printf("%13" PRIu32, arr[i]);
                i++;
                count++;
                if (count == 5) {
                    printf("\n");
                    count = 0;
                }
            }
            printf("\n");
        }
    }
    if (set_member(options, 2)) {
        reset(&stats);
        array(arr, seed, size);
        shell_sort(&stats, arr, size);
        char names[] = "Shell Sort";
        print_stats(&stats, names, size);
        int i = 0;
        int count = 0;
        if (elements > 0 && size > 0) {
            while (i < elements && i < size) {
                printf("%13" PRIu32, arr[i]);
                i++;
                count++;
                if (count == 5) {
                    printf("\n");
                    count = 0;
                }
            }
            printf("\n");
        }
    }
    if (set_member(options, 3)) {
        reset(&stats);
        array(arr, seed, size);
        heap_sort(&stats, arr, size);
        char nameh[] = "Heap Sort";
        print_stats(&stats, nameh, size);
        int i = 0;
        int count = 0;
        if (elements > 0 && size > 0) {
            while (i < elements && i < size) {
                printf("%13" PRIu32, arr[i]);
                i++;
                count++;
                if (count == 5) {
                    printf("\n");
                    count = 0;
                }
            }
            printf("\n");
        }
    }
    if (set_member(options, 4)) {
        reset(&stats);
        array(arr, seed, size);
        quick_sort(&stats, arr, size);
        char nameq[] = "Quick Sort";
        print_stats(&stats, nameq, size);
        int i = 0;
        int count = 0;
        if (elements > 0 && size > 0) {
            while (i < elements && i < size) {
                printf("%13" PRIu32, arr[i]);
                i++;
                count++;
                if (count == 5) {
                    printf("\n");
                    count = 0;
                }
            }
            printf("\n");
        }
    }
    if (set_member(options, 5)) {
        reset(&stats);
        array(arr, seed, size);
        batcher_sort(&stats, arr, size);
        char nameb[] = "Batcher Sort";
        print_stats(&stats, nameb, size);
        int i = 0;
        int count = 0;
        if (elements > 0 && size > 0) {
            while (i < elements && i < size) {
                printf("%13" PRIu32, arr[i]);
                i++;
                count++;
                if (count == 5) {
                    printf("\n");
                    count = 0;
                }
            }
            printf("\n");
        }
    }
    free(arr);

    return 0;
}
