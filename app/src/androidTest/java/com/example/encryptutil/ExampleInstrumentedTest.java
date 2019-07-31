package com.example.encryptutil;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Base64;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.nio.charset.Charset;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {
    @Test
    public void useAppContext() {
        Context appContext = InstrumentationRegistry.getTargetContext();
        assertEquals("com.example.encryptutil", appContext.getPackageName());
    }

    @Test
    public void testEncrypt(){
        final String s = "1234按实际冷风机cdef:\\{\"\"汉字http://.";
        final StringBuilder plainText = new StringBuilder(10000);
        int i;
        /*for (i = 0; i < 1000; i++) {
            plainText.append(s);
        }*/
        for (i = 0; i < 5000; i++) {
            plainText.append(s);
            String str = plainText.toString();
            if (!encrypt(str)){
                Log.d("Encrypt","失败原文：\n" + str+"---"+str.length());
                break;
            }
        }
        Log.d("Encrypt","测试成功数据：\n" + i);
        /*final String s = plainText.toString();
        if (!encrypt(s)){
            Log.d("Encrypt","失败原文：\n" + s+"---"+s.length());
        }*/
    }

    private boolean encrypt(String plainText){
//        Log.d("Encrypt","原文：\n" + plainText);

        String cipherText = Util.encrypt(plainText);

//        cipherText = cipherText.replace('=', '*');
//        cipherText = cipherText.replace('+', '$');
//        Log.d("Encrypt","\n密文：\n"+cipherText);
//        cipherText = cipherText.replace('*', '=');
//        cipherText = cipherText.replace('$', '+');

        final String tmp = Util.decrypt(cipherText);

//        Log.d("Encrypt","\n解密：\n"+tmp);

        final boolean success = tmp.equals(plainText);

        if (success) {
//            Log.d("Encrypt","\n加解密成功："+plainText);
        } else {
            Log.d("Encrypt","\n加解密失败：\n");
            Log.d("Encrypt","\n明文：\n"+plainText);
            Log.d("Encrypt","\n密文：\n"+cipherText);
            Log.d("Encrypt","\n解密：\n"+tmp);
        }
        return success;
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
            Log.d("base64_original", s+"----"+s.length());
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
