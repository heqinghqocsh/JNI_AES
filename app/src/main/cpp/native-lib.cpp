#include <jni.h>
#include <string>
#include "aes.h"
#include "modes.h"
#include <android/log.h>

const char *Tag = "Native_Test";

extern "C"
void log(const char *tag, const char *content) {
    __android_log_print(ANDROID_LOG_ERROR, tag, "%s", content);
}

extern "C"
void logChar(const char *content) {
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s", content);
}

/*extern "C"
void logFmt(const char *tag, const char *fmt, ...) {
    va_list arg_ptr;
    char *s = NULL;
    va_start(arg_ptr, fmt);
    s = va_arg(arg_ptr, char*);
    va_end(arg_ptr);
    __android_log_print(ANDROID_LOG_ERROR, tag, fmt, s);
}*/

char *padding_buf(const char *buf, int size, size_t *final_size) {
    char *ret = NULL;
    int padding_size = AES_BLOCK_SIZE - (size % AES_BLOCK_SIZE);
    int i;
    *final_size = size + padding_size;
    ret = (char *) malloc(size + padding_size);
    memcpy(ret, buf, size);
    if (padding_size != 0) {
        for (i = size; i < (size + padding_size); i++) {
            // zero padding算法：
            ret[i] = 0;
            //or PKCS5Padding算法
//            ret[i] = pidding_size;
        }
    }
    return ret;
}

unsigned char *str2hex(const char *str) {
    unsigned char *ret = NULL;
    int str_len = strlen(str);
    int i = 0;
    assert((str_len % 2) == 0);
    ret = (unsigned char *) malloc(str_len / 2);
    for (i = 0; i < str_len; i = i + 2) {
        sscanf(str + i, "%2hhx", &ret[i / 2]);
    }
    return ret;
}

extern "C"
jstring encryptDecrypt(JNIEnv *env,
                       jstring text, const int enc) {
//    std::string hello = "Hello from C++";
//    const char *str = "明文：你好 C++";
    const char passwordStr[] = "aaaaaaaaaaaaaaaa";
    const unsigned char *password = (unsigned char *) passwordStr;
    const char ivStr[] = "0123456789abcdef";
    unsigned char *iv = (unsigned char *) ivStr;

    AES_KEY *aes_key = (AES_KEY *) malloc(sizeof(AES_KEY));
    AES_set_encrypt_key(password, 128, aes_key);

    const char *inChars = (env->GetStringUTFChars(text, JNI_FALSE));
    const size_t originalLength = strlen(inChars);
    size_t paddedLength = 0;
    const char * paddedChar = padding_buf(inChars,(int)originalLength,&paddedLength);
    env->ReleaseStringUTFChars(text, inChars);
    const unsigned char *in = (unsigned char *) paddedChar;

    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%s", "输入：", in);

    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%d", "长度：", (int) paddedLength);

    unsigned char *out = (unsigned char *) malloc(
            (paddedLength) * sizeof(unsigned char));
    logChar("开始cfb128加密开始");
    int num = 0;
    AES_cfb128_encrypt(in, out, paddedLength, aes_key, iv, &num, enc);
    logChar("开始cfb128加密完成");
    return env->NewStringUTF((char *) out);
}

void printf_buff(const char *buff, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
//        __android_log_print(ANDROID_LOG_ERROR, Tag, "%02X ", (unsigned char) buff[i]);
        /*if ((i + 1) % 8 == 0) {
            logChar("\n");
        }*/
    }
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s", buff);
    logChar("\n\n");
}

void encrpyt_buf(const char *raw_buf, char *encrpy_buf, int len, const int enc) {
    AES_KEY aes;
    const char *keyStr = "8cc72b05705d5c46f412af8cbed55aad";
    unsigned char *key = str2hex(keyStr);
    const char *ivStr = "667b02a85c61c786def4521b060265e8";
    unsigned char *iv = str2hex(ivStr);
    int result = AES_set_encrypt_key(key, 128, &aes);
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%d", "结果：", result);
    int num = 0;
    AES_cfb128_encrypt((unsigned char *) raw_buf, (unsigned char *) encrpy_buf, len, &aes, iv,
                       &num, enc);
//    logChar(*encrpy_buf);
//    free(key);
//    free(iv);
}

extern "C"
jstring encryptOrDecrypt(JNIEnv *env,
                         jstring text, const int enc) {
    const char *raw_buf = NULL;
    char *after_padding_buf = NULL;
    int padding_size = 0;
    char *encrypt_buf = NULL;
    // 1
    raw_buf = env->GetStringUTFChars(text, JNI_FALSE);
    logChar("------------------raw_buf\n");
    printf_buff(raw_buf, strlen(raw_buf));
    // 2
//    after_padding_buf = padding_buf(raw_buf, strlen(raw_buf), &padding_size);
//    free(&raw_buf);
    logChar("------------------after_padding_buf\n");
    printf_buff(after_padding_buf, padding_size);
    // 3
    encrypt_buf = (char *) malloc(padding_size);
    encrpyt_buf(after_padding_buf, encrypt_buf, padding_size, enc);
    logChar("------------------encrypt_buf\n");
//    printf_buff(encrypt_buf, padding_size);
}


extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_MainActivity_encrypt(
        JNIEnv *env,
        jobject /* this */, jstring plainText) {
    log("Native_Test", "加密");
    const char *str = "明文：你好 C++";
//    encryptOrDecrypt(env, plainText, AES_ENCRYPT);
    return encryptDecrypt(env, plainText, AES_ENCRYPT);
//    return env->NewStringUTF(str);
//    return encryptDecrypt(env, plainText, AES_ENCRYPT);
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_MainActivity_decrypt(
        JNIEnv *env,
        jobject /* this */, jstring encryptText) {
    log("Native_Test", "解密");
    return encryptDecrypt(env, encryptText, AES_DECRYPT);
}
