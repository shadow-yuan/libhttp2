/*
 * nghttp2 - HTTP/2 C Library
 *
 * Copyright (c) 2013 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <stdint.h>

typedef enum {
    /* FSA accepts this state as the end of huffman encoding
       sequence. */
    HTTP2_HUFF_ACCEPTED = 1 << 14,
    /* This state emits symbol */
    HTTP2_HUFF_SYM = 1 << 15,
} http2_huff_decode_flag;

typedef struct {
    /* fstate is the current huffman decoding state, which is actually
       the node ID of internal huffman tree with
       http2_huff_decode_flag OR-ed.  We have 257 leaf nodes, but they
       are identical to root node other than emitting a symbol, so we
       have 256 internal nodes [1..255], inclusive.  The node ID 256 is
       a special node and it is a terminal state that means decoding
       failed. */
    uint16_t fstate;
    /* symbol if HTTP2_HUFF_SYM flag set */
    uint8_t sym;
} http2_huff_decode;

typedef struct {
    /* fstate is the current huffman decoding state. */
    uint16_t fstate;
} http2_hd_huff_decode_context;

typedef struct {
    /* The number of bits in this code */
    uint32_t nbits;
    /* Huffman code aligned to LSB */
    uint32_t code;
} http2_huff_sym;

extern const http2_huff_sym huff_sym_table[];
extern const http2_huff_decode huff_decode_table[][16];

/* Huffman encoding/decoding functions */

/*
 * Counts the required bytes to encode |src| with length |len|.
 *
 * This function returns the number of required bytes to encode given
 * data, including padding of prefix of terminal symbol code. This
 * function always succeeds.
 */
size_t http2_head_huffman_encode_count(const uint8_t *src, size_t len);

/*
 * Encodes the given data |src| with length |srclen| to the |bufs|.
 * This function expands extra buffers in |bufs| if necessary.
 *
 * This function returns the number of bytes that would have been
 * filled in dst.
 */
int http2_head_huffman_encode(uint8_t *dst, size_t dstlen, const uint8_t *src, size_t srclen);

void http2_head_huffman_decode_context_init(http2_hd_huff_decode_context *ctx);

/*
 * Decodes the given data |src| with length |srclen|.  The |ctx| must
 * be initialized by nghttp2_hd_huff_decode_context_init(). The result
 * will be written to |buf|.  This function assumes that |buf| has the
 * enough room to store the decoded byte string.
 *
 * The caller must set the |fin| to nonzero if the given input is the
 * final block.
 *
 * This function returns the number of read bytes from the |in|.
 *
 * If this function fails, it returns -1.
 */
int32_t http2_head_huffman_decode(http2_hd_huff_decode_context *ctx, uint8_t *buf, const uint8_t *src, size_t srclen,
                                  int fin);

/*
 * http2_hd_huff_decode_failure_state returns nonzero if |ctx|
 * indicates that huffman decoding context is in failure state.
 */
int http2_head_huffman_decode_failure_state(http2_hd_huff_decode_context *ctx);
