#include "bitwriter.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
struct BitWriter {
          Buffer *underlying_stream;
          uint8_t byte;
          uint8_t bit_position;
};
*/

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint64_t fill_histogram(Buffer *inbuf, double *histogram) {
    uint64_t filesize = 0;
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    ++histogram[0x00];
    ++histogram[0xff];
    uint8_t byte;
    while (read_uint8(inbuf, &byte)) {
        ++histogram[byte];
        ++filesize;
    }
    return filesize;
}

Node *create_tree(double *histogram, uint16_t *num_leaves) {
    PriorityQueue *q = pq_create();
    for (int i = 0; i < 256; i++) {
        if (histogram[i] != 0) {
            Node *n = node_create(i, histogram[i]);
            enqueue(q, n);
            (*num_leaves)++;
        }
    }
    while (!pq_size_is_1(q) && !pq_is_empty(q)) {
        Node *left, *right;
        dequeue(q, &left);
        dequeue(q, &right);
        Node *new = node_create('n', left->weight + right->weight);
        new->left = left;
        new->right = right;
        enqueue(q, new);
    }
    Node *ret;
    dequeue(q, &ret);
    pq_free(&q);
    return ret;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code = code | 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left != NULL) {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    } else {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    }
}

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);
    uint8_t b;
    while (read_uint8(inbuf, &b)) {
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}
void delete_tree(Node *n) {
    if (n == NULL)
        return;
    delete_tree(n->left);
    delete_tree(n->right);
    free(n);
}
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
    Buffer *one = read_open(input);
    double histogram[256];
    uint64_t filesize = fill_histogram(one, histogram);
    uint16_t num_leaves = 0;
    Node *code_tree = create_tree(histogram, &num_leaves);

    Code code_table[256];

    fill_code_table(code_table, code_tree, 0, 0);
    read_close(&one);
    Buffer *two = read_open(input);
    BitWriter *three = bit_write_open(output);
    huff_compress_file(three, two, filesize, num_leaves, code_tree, code_table);

    delete_tree(code_tree);
    memset(code_table, 0, sizeof(Code));
    bit_write_close(&three);
    read_close(&two);
}
