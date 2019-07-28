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
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();

        assertEquals("com.example.encryptutil", appContext.getPackageName());
    }

    @Test
    public void base64() {
        String s = "123456abcdef:\\{\"\"汉字http://.";
        int size = 57;
        final StringBuilder builder = new StringBuilder(10000);
        final int length = 1000;
        for (int i = 0; i < length; i++) {
            builder.append(s);
            testBase64(builder.toString());
        }
//        testBase64(s);

        Log.d("base64", "测试完成--" + length);
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
