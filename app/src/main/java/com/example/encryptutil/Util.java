package com.example.encryptutil;

public class Util {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String encrypt(String plainText);

    public static native String decrypt(String cipherText);

    public static native String base64Encode(String cipherText,boolean doNewLine);

    public static native String base64Decode(String cipherText);

}
