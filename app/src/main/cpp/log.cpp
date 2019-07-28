//
// Created by HeQing_2 on 2019/7/21.
//

#include <android/log.h>
#include "log.h"

void log(const char *tag, const char *content) {
    if (!logEnable){
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, tag, "%s", content);
}

void logStr(const char *content) {
    if (!logEnable){
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s", content);
}

void logC(const char c){
    if (!logEnable){
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%c", c);
}

void logInt(const int d){
    if (!logEnable){
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%d", d);
}

void logStrInt(const char *content,const int d){
    if (!logEnable){
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s--%d", content,d);
}


