//
// Created by HeQing_2 on 2019/7/25.
//

#include "base64.h"

void deal_encode(unsigned char tmp[], unsigned char buf[]) {
    buf[0] = (tmp[0] & 0xfc) >> 2;
    buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
    buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
    buf[3] = tmp[2] & 0x3f;
}

char *b64_encode(const unsigned char *src, size_t len, bool do_newline) {
    int i = 0;
    int j = 0;
    char *enc = NULL;
    size_t size = 0;
    unsigned char buf[4];
    unsigned char tmp[3];
    int lineGroup = do_newline ? LINE_GROUPS : -1;
    // alloc
    enc = (char *) malloc(0);
    if (NULL == enc) { return NULL; }
    // parse until end of source
    while (len--) {
        // read up to 3 bytes at a time into `tmp'
        tmp[i++] = *(src++);
        // if 3 bytes read then encode into `buf'
        if (3 == i) {
            deal_encode(tmp, buf);
            // allocate 4 new byts for `enc` and
            // then translate each encoded buffer
            // part by index from the base 64 index table
            // into `enc' unsigned char array
            enc = (char *) realloc(enc, size + 4);
            for (i = 0; i < 4; ++i) {
                enc[size++] = b64_table[buf[i]];
            }
            // reset index
            i = 0;
            if (do_newline && --lineGroup == 0) {
                enc = (char *) realloc(enc, size + 1);
                enc[size++] = CRLF_LF;
                lineGroup = LINE_GROUPS;
            }
        }
    }

    // remainder
    if (i > 0) {
        // fill `tmp' with `\0' at most 3 times
        for (j = i; j < 3; ++j) {
            tmp[j] = '\0';
        }
        // perform same codec as above
        deal_encode(tmp, buf);
        // perform same write to `enc` with new allocation
        for (j = 0; (j < i + 1); ++j) {
            enc = (char *) realloc(enc, size + 1);
            enc[size++] = b64_table[buf[j]];
        }
        // while there is still a remainder
        // append `=' to `enc'
        while ((i++ < 3)) {
            enc = (char *) realloc(enc, size + 1);
            enc[size++] = '=';
        }
    }
//    free(&tmp);
//    free(&buf);
    if (do_newline && enc[size - 1] != CRLF_LF) {
        enc = (char *) realloc(enc, size + 1);
        enc[size++] = CRLF_LF;
    }
    // Make sure we have enough space to add '\0' character at end.
    enc = (char *) realloc(enc, size + 1);
    enc[size] = '\0';
    return enc;
}

unsigned char *b64_decode(const unsigned char *src, size_t len) {
    return b64_decode_ex(src, len, NULL);
}

void deal_decode(unsigned char tmp[], unsigned char buf[]) {
    buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];
}

int b64_table_index(unsigned char c) {
    switch (c) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return c - 'A';
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return c - 'a' + 26;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return c - '0' + 52;
        case '+':
            return 62;
        case '/':
            return 63;
        default:
            return 0;
    }
}

unsigned char *b64_decode_ex(const unsigned char *src, size_t len, size_t *decsize) {
    int i = 0;
    int j = 0;
    size_t size = 0;
    unsigned char *dec = NULL;
    unsigned char buf[3];
    unsigned char tmp[4];
    // alloc
    dec = (unsigned char *) malloc(0);
    if (NULL == dec) { return NULL; }
    // parse until end of source
    while (len--) {
        // break if char is `=' or not base64 char
        if ('=' == src[j]) {
            break;
        }
        if (CRLF_LF == src[j]) {
            j++;
            continue;
        }
        if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) {
            break;
        }
        // read up to 4 bytes at a time into `tmp'
        tmp[i++] = src[j++];
        // if 4 bytes read then decode into `buf'
        if (4 == i) {
            // translate values in `tmp' from table
            for (i = 0; i < 4; ++i) {
                // find translation char in `b64_table'
                tmp[i] = b64_table_index(tmp[i]);
            }
            // decode
            deal_decode(tmp, buf);
            // write decoded buffer to `dec'
            dec = (unsigned char *) realloc(dec, size + 3);
            for (i = 0; i < 3; ++i) {
                dec[size++] = buf[i];
            }
            // reset
            i = 0;
        }
    }
    // remainder
    if (i > 0) {
        // fill `tmp' with `\0' at most 4 times
        for (j = i; j < 4; ++j) {
            tmp[j] = '\0';
        }
        // translate remainder
        for (j = 0; j < 4; ++j) {
            // find translation char in `b64_table'
            tmp[j] = b64_table_index(tmp[j]);
        }
        // decode remainder
        deal_decode(tmp, buf);
        // write remainer decoded buffer to `dec'
        dec = (unsigned char *) realloc(dec, size + (i - 1));
        for (j = 0; (j < i - 1); ++j) {
            dec[size++] = buf[j];
        }
    }
//    free(&tmp);
//    free(&buf);
    // Make sure we have enough space to add '\0' character at end.
    dec = (unsigned char *) realloc(dec, size + 1);
    dec[size] = '\0';
    // Return back the size of decoded string if demanded.
    if (decsize != NULL) {
        *decsize = size;
    }
    return dec;
}

