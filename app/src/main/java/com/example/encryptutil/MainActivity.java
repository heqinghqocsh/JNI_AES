package com.example.encryptutil;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

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
        for (int i = 0;i<200;i++){
            plainText.append(original);
        }

        originalText.setText("原文长度：\n"+plainText.length());
        final String cipherText = encrypt(plainText.toString());
//        encryptText.setText("密文：\n"+cipherText);
        final String tmp = decrypt(cipherText);
        if (tmp.equals(plainText.toString())){
            decryptText.setText("加解密成功：\n");
        }else {
            decryptText.setText("加解密失败：\n");
        }

        final String base64 = "http://www漢字12汉字3asdf456中文";

        base64Text.setText(base64);
        final String encodeStr = base64Encode(base64);
        encodeText.setText(encodeStr);
        decodeText.setText(base64Decode(encodeStr));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String encrypt(String plainText);

    public native String decrypt(String cipherText);

    public native String base64Encode(String cipherText);

    public native String base64Decode(String cipherText);
}
