#include "io.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct buffer {
    int fd;
    int offset;
    int num_remaining;
    uint8_t a[BUFFER_SIZE];
};

Buffer *read_open(const char *filename) {
    int rd = -1;
    rd = open(filename, O_RDONLY);
    if (rd < 0) {
        fprintf(stderr, "hi open not working");
        return NULL;
    }

    Buffer *b = calloc(1, sizeof(Buffer));
    b->fd = rd;
    return b;
}

void read_close(Buffer **pbuf) {
    int closed = close((*pbuf)->fd);
    if (closed < 0) {
        printf("Error closing file");
    } else {
        free(*pbuf);
        (*pbuf) = NULL;
    }
}

Buffer *write_open(const char *filename) {
    int wr = creat(filename, 0664);
    if (wr < 0) {
        return NULL;
    }

    Buffer *b = calloc(1, sizeof(Buffer));
    b->fd = wr;
    return b;
}

void write_close(Buffer **pbuf) {
    uint8_t *start = (*pbuf)->a;
    int num_bytes = (*pbuf)->offset;
    do {
        ssize_t rc = write((*pbuf)->fd, start, num_bytes);
        if (rc < 0)
            fprintf(stderr, "couldnt read");
        start += rc; // skip past the bytes that were just written
        num_bytes -= rc; // how many bytes are left?
    } while (num_bytes > 0);
    (*pbuf)->offset = 0;
    int closed = close((*pbuf)->fd);
    if (closed < 0) {
        printf("Error closing file");
    }
    free(*pbuf);
    (*pbuf) = NULL;
}

bool read_uint8(Buffer *buf, uint8_t *x) {
    if (buf == NULL)
        fprintf(stderr, "null pointer buffer");
    if (buf->num_remaining == 0) {
        ssize_t rc = read(buf->fd, buf->a, sizeof(buf->a));
        if (rc < 0)
            fprintf(stderr, "Error reading");
        if (rc == 0)
            return false; // end of file
        buf->num_remaining = rc;
        buf->offset = 0;
    }
    *x = buf->a[buf->offset];
    buf->offset += 1;
    buf->num_remaining -= 1;
    return true;
}

bool read_uint16(Buffer *buf, uint16_t *x) {
    uint8_t first = 0;
    if (!read_uint8(buf, &first)) {
        return false;
    }
    uint8_t second = 0;
    if (!read_uint8(buf, &second)) {
        return false;
    }
    uint16_t copy = second;
    copy = copy << 8;
    copy = copy | first;
    *x = copy;
    return true;
}

bool read_uint32(Buffer *buf, uint32_t *x) {
    uint16_t first = 0;
    if (!read_uint16(buf, &first)) {
        return false;
    }
    uint16_t second = 0;
    if (!read_uint16(buf, &second)) {
        return false;
    }
    uint32_t copy = second;
    copy = copy << 16;
    copy = copy | first;
    *x = copy;
    return true;
}

void write_uint8(Buffer *buf, uint8_t x) {
    if (buf->offset == BUFFER_SIZE) {
        uint8_t *start = buf->a;
        int num_bytes = buf->offset;
        do {
            ssize_t rc = write(buf->fd, start, num_bytes);
            if (rc < 0)
                fprintf(stderr, "couldnt read");
            start += rc; // skip past the bytes that were just written
            num_bytes -= rc; // how many bytes are left?
        } while (num_bytes > 0);
        buf->offset = 0;
    }
    buf->a[buf->offset] = x;
    buf->offset += 1;
}

void write_uint16(Buffer *buf, uint16_t x) {
    write_uint8(buf, x);
    x = x >> 8;
    write_uint8(buf, x);
}

void write_uint32(Buffer *buf, uint32_t x) {
    write_uint16(buf, x);
    x = x >> 16;
    write_uint16(buf, x);
}
