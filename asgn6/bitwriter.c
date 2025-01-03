#include "bitwriter.h"

#include "io.h"

#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    Buffer *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    BitWriter *buf = calloc(1, sizeof(BitWriter));
    Buffer *underlying_stream = write_open(filename);
    buf->underlying_stream = underlying_stream;
    return buf;
}

void bit_write_close(BitWriter **pbuf) {
    if ((*pbuf)->bit_position > 0) {
        write_uint8((*pbuf)->underlying_stream, (*pbuf)->byte);
    }
    write_close(&(*pbuf)->underlying_stream);
    free(*pbuf);
    *pbuf = NULL;
}

void bit_write_bit(BitWriter *buf, uint8_t x) {
    if (buf->bit_position > 7) {
        write_uint8(buf->underlying_stream, buf->byte);
        buf->byte = 0;
        buf->bit_position = 0;
    }
    if (x & 1) {
        buf->byte = buf->byte | ((x & 1) << buf->bit_position);
    }
    ++buf->bit_position;
}

void bit_write_uint8(BitWriter *buf, uint8_t x) {
    for (int i = 0; i < 8; i++) {
        uint8_t temp = x >> i;
        uint8_t bit = temp & 1;
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        uint16_t temp = x >> i;
        uint8_t bit = temp & 1;
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        uint32_t temp = x >> i;
        uint8_t bit = temp & 1;
        bit_write_bit(buf, bit);
    }
}
