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

void convert_hex(unsigned char *in, size_t len, char *out) {
    unsigned int c = 0;
    for (int i = 0; i < len; i++) {
        out += hex_chars[(in[i] >> 4) & 0x0f];
        out += hex_chars[in[i] & 0x0f];
    }
}
