import javax.crypto.spec.SecretKeySpec;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.Cipher;

public class AES {
    public static byte[] aes_cbc_pkcs5padding(byte[] content, String key, byte[] iv) {
        try {
            SecretKeySpec secretKeySpec = new SecretKeySpec(key.getBytes("ASCII"), "AES");
            IvParameterSpec ivParameterSpec = new IvParameterSpec(iv);
            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec, ivParameterSpec);
            return cipher.doFinal(content);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String bytesToHex(byte[] bytes) {
        StringBuilder buf = new StringBuilder(bytes.length << 2);
        for(byte b : bytes) { // 使用String的format方法进行转换
            buf.append(String.format("%02X", new Integer(b & 0xff)));
        }
        return buf.toString();
    }

    public static void main(String[] args) throws Exception {
        String content = args[0];
        String key = "abcdefghjklqwert";
        byte[] iv = new byte[16];
        for (int i = 0; i < 16; i++) {
            iv[i] = 0;
        }
        String hex = bytesToHex(aes_cbc_pkcs5padding(content.getBytes("ASCII"), key, iv));
        System.out.printf("aes_cbc_pkcs5padding(content=%s,key=%s)=%s\n", content, key, hex);
    }
}
