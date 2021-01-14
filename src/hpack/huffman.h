#pragma once
#include <stdint.h>

typedef enum {
    HUFF_ACCEPTED = 1,    // FSA accepts this state as the end of huffman encoding sequence
    HUFF_SYM = (1 << 1),  // This state emits symbol
    HUFF_FAIL = (1 << 2)  // If state machine reaches this state, decoding fails
} http2_huff_decode_flag;

typedef struct {
    uint8_t state;
    uint8_t flags;  // bitwise OR of zero or more of the HuffDecodeFlag
    uint8_t sym;    // symbol if HUFF_SYM flag set
} http2_huff_decode;

typedef struct {
    uint32_t nbits;  // The number of bits in this code
    uint32_t code;   // Huffman code aligned to LSB
} http2_huff_sym;

extern const http2_huff_sym huff_sym_table[];
extern const http2_huff_decode huff_decode_table[][16];
