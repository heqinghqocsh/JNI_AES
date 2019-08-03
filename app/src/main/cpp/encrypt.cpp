//
// Created by HeQing_2 on 2019/7/21.
//

#include <jni.h>
#include <string>
#include "aes.h"
#include "modes.h"
#include "log.h"
#include "utils.h"
#include "base64.h"

unsigned char *padding_buf(const char *buf, size_t size, size_t *final_size) {
    unsigned char *ret = NULL;
    size_t padding_size = AES_BLOCK_SIZE - (size % AES_BLOCK_SIZE);
    size_t i;
    *final_size = size + padding_size;
    ret = (unsigned char *) malloc(*final_size + 1);
    memcpy(ret, buf, size);
    const unsigned char paddingChar = (unsigned char) padding_size;
    for (i = size; i < *final_size; i++) {
        // zero padding算法：
        // ret[i] = 0;
        // or PKCS7Padding算法
        ret[i] = paddingChar;
    }
    ret[*final_size] = '\0';
    return ret;
}

unsigned const char password[] = "yn!d!c@p$abw0rdacbttye$15649!@$@";
const int pwdBitsLength = 256;
unsigned char iv[] = "-o&g@n,%o!dl^abc";

unsigned char *getIv() {
    size_t len = strlen((char *) iv);
    unsigned char *ivCopy = (unsigned char *) malloc(len);;
    memcpy(ivCopy, iv, len);
    return ivCopy;
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_Util_encrypt(
        JNIEnv *env,
        jclass /* this */, jstring plainText) {
    AES_KEY *aes_key = (AES_KEY *) malloc(sizeof(AES_KEY));
    AES_set_encrypt_key(password, pwdBitsLength, aes_key);
    const char *inChars = (env->GetStringUTFChars(plainText, JNI_FALSE));
    const size_t originalLength = strlen(inChars);
    size_t paddedLength = 0;
    unsigned char *in = padding_buf(inChars, originalLength, &paddedLength);
    env->ReleaseStringUTFChars(plainText, inChars);
    unsigned char *out = (unsigned char *) malloc((paddedLength) * sizeof(unsigned char));
    int num = 0;
    AES_cfb128_encrypt(in, out, paddedLength, aes_key, getIv(), &num, AES_ENCRYPT);
    free(in);
    free(aes_key);
    /*
     * //十六进制字符串转换
     * char *result = (char *) malloc((paddedLength * 2 + 1) * sizeof(char));
    convert_hex(out, paddedLength, result);
     */
    char *result = b64_encode(out,paddedLength, true);
    free(out);
    jstring tmp = env->NewStringUTF(result);
    free(result);
    return tmp;
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_Util_decrypt(
        JNIEnv *env,
        jclass /* this */, jstring encryptText) {
    AES_KEY *aes_key = (AES_KEY *) malloc(sizeof(AES_KEY));
    AES_set_encrypt_key(password, pwdBitsLength, aes_key);
    const char *inChars = (env->GetStringUTFChars(encryptText, JNI_FALSE));
    size_t originalLength = 0;
    unsigned char *in = b64_decode((const unsigned char *)inChars,strlen(inChars),&originalLength);
    env->ReleaseStringUTFChars(encryptText, inChars);
    const size_t outPaddedLength = originalLength;
    /*
     * //十六进制字符串转换
     * unsigned char *in = (unsigned char *) malloc(
            (outPaddedLength + 1) * sizeof(unsigned char));
    hexConvertToUnsignedChar((unsigned char *) inChars, outPaddedLength, in);
     */
    unsigned char *out = (unsigned char *) malloc((outPaddedLength) * sizeof(unsigned char));
    int num = 0;
    AES_cfb128_encrypt(in, out, outPaddedLength, aes_key, getIv(), &num, AES_DECRYPT);
    free(in);
    free(aes_key);
    const int pad = (int)out[outPaddedLength - 1];
    out[outPaddedLength - pad] = '\0';
    jstring tmp = env->NewStringUTF((char *) out);
    free(out);
    return tmp;
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_Util_base64Encode(
        JNIEnv *env,
        jclass /* this */, jstring plainText,jboolean doNewLine) {
    const char *inChars = (env->GetStringUTFChars(plainText, JNI_FALSE));
    char *out = b64_encode((const unsigned char *)inChars,strlen(inChars),doNewLine);
    env->ReleaseStringUTFChars(plainText, inChars);
    jstring tmp = env->NewStringUTF(out);
    free(out);
    return tmp;
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_encryptutil_Util_base64Decode(
        JNIEnv *env,
        jclass /* this */, jstring encodedText) {
    const char *inChars = (env->GetStringUTFChars(encodedText, JNI_FALSE));
    size_t originalLength = 0;
    unsigned char *out = b64_decode((const unsigned char *)inChars,strlen(inChars),&originalLength);
    env->ReleaseStringUTFChars(encodedText, inChars);
    jstring tmp = env->NewStringUTF((char *)out);
    free(out);
    return tmp;
}
