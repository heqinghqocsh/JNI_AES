package com.example.encryptutil;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.util.Log;
import android.widget.TextView;

import java.nio.charset.Charset;

public class MainActivity extends AppCompatActivity {

    private TextView originalText;
    private TextView decryptText;

    private TextView base64Text;
    private TextView encodeText;
    private TextView decodeText;

    final String original = "abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒abcdefg1234567890拉酒店方垃圾死了打飞机1234567$%*8啊啊大所发生的901" +
            "234567890,./最棒dfadfjlasjdflsajdofgaskdgajfla464a53s1df3a1s97r8917403a(&*&*@#$%$^";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        originalText = findViewById(R.id.original_text);
        decryptText = findViewById(R.id.decrypt_text);

        base64Text = findViewById(R.id.base64_text);
        encodeText = findViewById(R.id.encode_text);
        decodeText = findViewById(R.id.decode_text);

        final StringBuilder plainText = new StringBuilder(10000);
        for (int i = 0; i < 200; i++) {
            plainText.append(original);
        }

        originalText.setText("原文长度：\n" + plainText.length());
        final String cipherText = Util.encrypt(plainText.toString());
//        encryptText.setText("密文：\n"+cipherText);
        final String tmp = Util.decrypt(cipherText);
        if (tmp.equals(plainText.toString())) {
            decryptText.setText("加解密成功：\n");
        } else {
            decryptText.setText("加解密失败：\n");
        }

        final String base64 = "http://www漢字12汉字3asdf456中文www漢字12汉字3asdf456中文www漢字12汉字3asdf456中文www漢字12汉字3asdf456中文";

        base64Text.setText(base64);

        /*String CEncodeStr = Util.base64Encode(base64);
        encodeText.setText(CEncodeStr);
        decodeText.setText(Util.base64Decode(CEncodeStr));
        Log.d("Test",CEncodeStr);
        Log.d("Test",Util.base64Decode(CEncodeStr));

        String javaEncodeStr = javaBase64Encode(base64);
        Log.d("Test",javaEncodeStr);
        Log.d("Test",javaBase64Decode(javaEncodeStr));

        Log.d("Test",String.valueOf(CEncodeStr.equals(javaEncodeStr)));
        Log.d("Test",javaBase64Decode(CEncodeStr));
        Log.d("Test",Util.base64Decode(javaEncodeStr));*/
    }

    private String javaBase64Encode(String s) {
        return Base64.encodeToString(s.getBytes(Charset.forName("UTF-8")), Base64.DEFAULT);
    }

    private String javaBase64Decode(String s) {
        return new String(Base64.decode(s, Base64.DEFAULT));
    }


}
