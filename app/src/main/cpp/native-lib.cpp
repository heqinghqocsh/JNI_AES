#include <jni.h>
#include <string>
#include "aes.h"
#include "modes.h"
#include <android/log.h>
#include "utils.h"

const char *Log_Tag = "Native_Test";

char *padding_buf(const char *buf, size_t size, size_t *final_size) {
    char *ret = NULL;
    size_t padding_size = AES_BLOCK_SIZE - (size % AES_BLOCK_SIZE);
    size_t i;
    *final_size = size + padding_size;
    ret = (char *) malloc(*final_size);
    memcpy(ret, buf, size);
    if (padding_size != 0) {
        for (i = size; i < (size + padding_size); i++) {
            // zero padding算法：
//            ret[i] = 0;
//            or PKCS5Padding算法
            ret[i] = (char)padding_size;
        }
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
    const char * paddedChar = padding_buf(inChars,originalLength,&paddedLength);
    env->ReleaseStringUTFChars(text, inChars);
    const unsigned char *in = (unsigned char *) paddedChar;

    __android_log_print(ANDROID_LOG_ERROR, Log_Tag, "%s%s", "输入：", in);
    __android_log_print(ANDROID_LOG_ERROR, Log_Tag, "%s%d", "长度：", (int) paddedLength);

    unsigned char *out = (unsigned char *) malloc(
            (paddedLength) * sizeof(unsigned char));
    logChar("开始cfb128加密开始");
    int num = 0;
    AES_cfb128_encrypt(in, out, paddedLength, aes_key, iv, &num, enc);
    logChar("开始cfb128加密完成");
    char *result = (char *)malloc((paddedLength  / 2)* sizeof(char));
    convertUnCharToStr(result,out,paddedLength);
//    free(&out);
    return env->NewStringUTF(result);
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
