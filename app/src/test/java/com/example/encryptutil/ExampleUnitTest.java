package com.example.encryptutil;

import org.junit.Test;

import java.nio.charset.Charset;
import java.util.Base64;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);
    }

    @Test
    public void base64() {
        String s = "1";
        int size = 57;
        final StringBuilder builder = new StringBuilder(10000);
        final int length = 100;
        for (int i = 0; i < length; i++) {
            builder.append(s);
            testBase64(builder.toString());
        }
//        Log.d("base64", "测试完成--" + length);
    }

    private void testBase64(String s) {
//        Log.d("base64","------------------------------------------------");
//        Log.d("base64",s);
        String encodeJ = javaBase64Encode(s);
        String decodeJ = javaBase64Decode(encodeJ);
//        Log.d("base64_java_e",encodeJ);
//        Log.d("base64_java_d",decodeJ);

        String encodeC = Util.base64Encode(s, true);
        String decodeC = Util.base64Decode(encodeC);
//        Log.d("base64_C_e",encodeC);
//        Log.d("base64_C_d",decodeC);

        if (!encodeC.equals(encodeJ) || !decodeC.equals(decodeJ)) {
//            Log.d("base64_original", s);
//            Log.d("base64_e_C", encodeC);
//            Log.d("base64_e_J", encodeJ);
        }else {
//            Log.d("base64_result", "相同");
        }
//        Log.d("base64_Result",String.valueOf(encodeJ.equals(encodeC)));
//        Log.d("base64","===================================================");
    }

    private String javaBase64Encode(String s) {
        return Base64.getEncoder().encodeToString(s.getBytes(Charset.forName("UTF-8")));
    }

    private String javaBase64Decode(String s) {
        return new String(Base64.getDecoder().decode(s));
    }
}