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
    private TextView encryptText;
    private TextView decryptText;

    final String original = "1234567890abcdef";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        originalText = findViewById(R.id.original_text);
        encryptText = findViewById(R.id.encrypt_text);
        decryptText = findViewById(R.id.decrypt_text);

        originalText.setText("原文：\n"+original);
        final String cipherText = encrypt(original);
        encryptText.setText("密文：\n"+cipherText);
        decryptText.setText("解密：\n"+decrypt(cipherText));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String encrypt(String plainText);

    public native String decrypt(String cipherText);
}
