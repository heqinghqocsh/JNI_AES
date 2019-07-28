//
// Created by HeQing_2 on 2019/7/25.
//

#ifndef ENCRYPTUTIL_BASE64_H
#define ENCRYPTUTIL_BASE64_H

#endif //ENCRYPTUTIL_BASE64_H

# include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Base64 index table.
 */
static const char b64_table[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
};

static const int b64_length = 64;

static const int LINE_GROUPS = 19;

static const char CRLF_CR = '\r';
static const char CRLF_LF = '\n';

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encode `unsigned char *' source with `size_t' size.
 * Returns a `char *' base64 encoded string.
 */
char *b64_encode(const unsigned char *, size_t, bool);

/**
 * Dencode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string.
 */
unsigned char *b64_decode(const unsigned char *, size_t,size_t *);

/**
 * Dencode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string + size of decoded string.
 */
unsigned char *b64_decode_ex(const unsigned char *, size_t, size_t *);

#ifdef __cplusplus
}
#endif
