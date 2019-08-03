package com.example.encryptutil;

import android.support.test.runner.AndroidJUnit4;
import android.util.Base64;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

/**
 * java加解密和C语言加解密性能测试
 */
@RunWith(AndroidJUnit4.class)
public class EncryptPerformanceTest {
    private static final Map<Integer, Long> table = new LinkedHashMap<>(100);

    @Test
    public void testPerformance() {
        table.clear();
        final String s = "{type:1,name:\"bob;:&#$\\\",function:\"加解密对比\",url:\"https://www.baidu.com/\"}";
        final StringBuilder plainText = new StringBuilder(10000);
        int i;
        for (i = 0; i < 5000; i++) {
            plainText.append(s);
        }
        for (i = 0; i < 50; i++) {
            plainText.append(s);
            final String str = plainText.toString();
            if (!encrypt(str)) {
                Log.d("Encrypt", "失败原文：\n" + str + "---" + str.length());
                break;
            }
        }
        final StringBuilder builder = new StringBuilder(1000);
        Set<Map.Entry<Integer, Long>> entrySet = table.entrySet();
        builder.append("加解密字符串长度以及耗时差（C-J），单位 ms\n");
        for (Map.Entry<Integer, Long> entry : entrySet) {
            builder.append("长度：").append(entry.getKey())
                    .append("    耗时差：").append(entry.getValue())
                    .append("\n");
        }
        Log.d("Encrypt", "       \n\n" + builder.toString());
    }

    private boolean encrypt(String plainText) {
        long startTime;
        long diffJ, diffC;
        final int length = plainText.length();
        final StringBuilder log = new StringBuilder(100);

        String javaE;
        String javaD;
        try {
            //java加解密------------------------------------------------------
            startTime = System.currentTimeMillis();
            javaE = AESEncrypt.encodeReplace(plainText);
            javaD = AESEncrypt.decodeReplace(javaE);
            diffJ = System.currentTimeMillis() - startTime;
            log.append("字符串长度：").append(length).append("      java耗时：").append(diffJ);

            //C加解密------------------------------------------------------
            startTime = System.currentTimeMillis();
            String cE = Util.encrypt(plainText);
            final String cD = Util.decrypt(cE);
            diffC = System.currentTimeMillis() - startTime;
            log.append("      C耗时：").append(diffC);
            table.put(length, diffJ - diffC);
            Log.d("Encrypt", log.toString());
            final boolean success = javaE.equals(cE) && cD.equals(javaD);
            if (!success) {
                Log.d("Encrypt", "\n加解密失败：\n");
                Log.d("Encrypt", "\n明文：\n" + plainText);
                Log.d("Encrypt", "\n密文：\n" + cE);
                Log.d("Encrypt", "\n解密：\n" + cD);
            }
            return success;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return false;
    }

    @Test
    public void base64() {
        final String s = "123456abcdef:\\{\"\"汉字http://.";
        final StringBuilder builder = new StringBuilder(10000);
        final int length = 10000;
        for (int i = 0; i < length; i++) {
            builder.append(s);
            testBase64(builder.toString());
        }
        Log.d("base64", "测试完成--" + length);
    }

    private void testBase64(String s) {
        String encodeJ = javaBase64Encode(s);
        String decodeJ = javaBase64Decode(encodeJ);
//        Log.d("base64_java_e",encodeJ);
//        Log.d("base64_java_d",decodeJ);

        String encodeC = Util.base64Encode(s, true);
        String decodeC = Util.base64Decode(encodeC);
//        Log.d("base64_C_e",encodeC);
//        Log.d("base64_C_d",decodeC);

        if (!encodeC.equals(encodeJ) || !decodeC.equals(decodeJ)) {
            Log.d("base64_result", "以下数据不同");
            Log.d("base64_original", s + "----" + s.length());
            Log.d("base64_e_C", encodeC);
            Log.d("base64_e_J", encodeJ);
        }
//        Log.d("base64_Result_e",String.valueOf(encodeJ.equals(encodeC)));
//        Log.d("base64_Result_d",String.valueOf(decodeC.equals(decodeJ)));
//        Log.d("base64","===================================================");
    }

    private String javaBase64Encode(String s) {
        return Base64.encodeToString(s.getBytes(Charset.forName("UTF-8")), Base64.DEFAULT);
    }

    private String javaBase64Decode(String s) {
        return new String(Base64.decode(s, Base64.DEFAULT));
    }

}
