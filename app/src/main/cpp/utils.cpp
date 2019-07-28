//
// Created by HeQing_2 on 2019/7/21.
//

#include <iostream>
#include <string>
#include <android/log.h>
#include "utils.h"

const char *Tag = "Native_Test";

void log(const char *tag, const char *content) {
    __android_log_print(ANDROID_LOG_ERROR, tag, "%s", content);
}

void logChar(const char *content) {
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s", content);
}

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
    for (int i = 0; i < hex_chars_length; ++i) {
        if (hex_chars[i] == c) {
            return i;
        }
    }
    return -1;
}

void hexConvertToUnsignedChar(unsigned char *in, size_t len, unsigned char *out) {
    int i = 0;
    for (i = 0; i < len; i++) {
        out[i] = (hexIndex(in[i * 2]) << 4 & 0xf0) |
                 (hexIndex(in[i * 2 + 1]) & 0x0f);
    }
    out[i] = '\0';
}


