#ifndef CHAIN_CODE_DECODER_H
#define CHAIN_CODE_DECODER_H

#include <stdlib.h>
#include "pico/stdlib.h"
#include "consts.h"
#include "varint.h"

// Constants
#define DELIMITER 0xFE
#define WHITE     0xFFFF // RGB-565 representation for white
#define BLACK     0x0000 // RGB-565 representation for black

// Enum for direction
typedef enum {
    N = 0x1,
    E = 0x2,
    S = 0x4,
    W = 0x8
} Direction;

typedef struct {
    unsigned int x;
    unsigned int y;
} Point;

// Function prototypes
void initialize_frame_buffer(uint16_t* frame_buffer, uint16_t color);
uint16_t read_delimiter_value(unsigned char byte);
void process_nibble(unsigned char nibble, unsigned int* x, unsigned int* y);
void set_pixel(uint16_t* frame_buffer, unsigned int x, unsigned int y, uint16_t color);
void decode_chain_coded_frame(const unsigned char* encodedData, unsigned long long length, uint16_t* frame_buffer);

#endif // CHAIN_CODE_DECODER_H