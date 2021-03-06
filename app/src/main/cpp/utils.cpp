//
// Created by HeQing_2 on 2019/7/21.
//

#include <iostream>
#include <string>
#include "utils.h"

void convertUnCharToStr(char *out, unsigned char *UnChar, size_t ucLen) {
    size_t i = 0;
    for (i = 0; i < ucLen; i++) {
        //格式化输str,每unsigned char 转换字符占两位置%x写输%X写输
        sprintf(out + i * 2, "%02x", UnChar[i]);
    }
}

static const char hex_chars[] = "0123456789abcdef";
static const int hex_chars_length = 16;

void convert_hex(unsigned char *in, size_t len, char *out) {
    int i = 0;
    for (i = 0; i < len; i++) {
        out[i * 2] = hex_chars[(in[i] >> 4) & 0x0f];
        out[i * 2 + 1] = hex_chars[in[i] & 0x0f];
    }
    out[i * 2] = '\0';
}

int hexIndex(char c) {
    switch (c){
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
            return c - '0';
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return c - 'a' + 10;
        default:
            return -1;
    }
}

void hexConvertToUnsignedChar(unsigned char *in, size_t len, unsigned char *out) {
    int i = 0;
    for (i = 0; i < len; i++) {
        out[i] = (hexIndex(in[i * 2]) << 4 & 0xf0) |
                 (hexIndex(in[i * 2 + 1]) & 0x0f);
    }
    out[i] = '\0';
}


