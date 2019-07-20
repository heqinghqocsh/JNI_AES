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

extern "C"
jstring encryptDecrypt(JNIEnv *env,
                       jstring text, const int enc) {
//    std::string hello = "Hello from C++";
//    const char *str = "明文：你好 C++";
    const char passwordStr[100] = "123456";
    const unsigned char *password = (unsigned char *) passwordStr;

    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%s", "密码：", passwordStr);

    const char ivStr[50] = "0123456789abcdef";
    unsigned char *iv = (unsigned char *) ivStr;
    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%s", "iv：", ivStr);

    AES_KEY *aes_key = (AES_KEY *) malloc(sizeof(AES_KEY));
    AES_set_encrypt_key(password, (int) size_t(password), aes_key);

    const char *inChars = (env->GetStringUTFChars(text, JNI_FALSE));
    const unsigned char *in = (unsigned char *) inChars;

    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%s", "输入：", in);

    const size_t inputLength = strlen(inChars);
    env->ReleaseStringUTFChars(text, inChars);

    const size_t ivLength = strlen(ivStr);

    __android_log_print(ANDROID_LOG_ERROR, Tag, "%s%d-%d", "长度：", (int) inputLength,
                        (int) ivLength);

    unsigned char *out = (unsigned char *) malloc(
            (inputLength /*+ ivLength + 100*/) * sizeof(unsigned char));

    logChar("开始cfb128加密开始");
    AES_cfb128_encrypt(in, out, inputLength, aes_key, iv, (int *) ivLength - 1, enc);
    logChar("开始cfb128加密完成");

    return env->NewStringUTF((char *) out);
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_MainActivity_encrypt(
        JNIEnv *env,
        jobject /* this */, jstring plainText) {
    log("Native_Test", "这里1");
    return encryptDecrypt(env, plainText, AES_ENCRYPT);
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_MainActivity_decrypt(
        JNIEnv *env,
        jobject /* this */, jstring encryptText) {
/*    std::string hello = "Hello from C++";
    const char *str = "明文：你好 C++";

    const unsigned char *password = (unsigned char *) "123456";
    const char ivStr[50] = "0123456789abcdef";
    unsigned char *iv = (unsigned char *) ivStr;

    unsigned char *out;
    const char *inChars = (env->GetStringUTFChars(encryptText, JNI_FALSE));
    const unsigned char *in = (unsigned char *) inChars;

    AES_KEY *aes_key = (AES_KEY *) malloc(sizeof(AES_KEY));
    AES_set_encrypt_key(password, (int) size_t(password), aes_key);

    AES_cfb128_encrypt(in, out, size_t(in), aes_key, iv, (int *) strlen(ivStr), AES_DECRYPT);
    env->ReleaseStringUTFChars(encryptText, inChars);

    return env->NewStringUTF(str);*/
    log("Native_Test", "这里2");
    return encryptDecrypt(env, encryptText, AES_DECRYPT);
}
