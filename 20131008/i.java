import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static BigInteger _0 = new BigInteger("0");
    static BigInteger _1 = new BigInteger("1");
    static BigInteger gcd(BigInteger a, BigInteger b) {
        if (b.compareTo(_0) == 0) return a;
        return gcd(b, a.mod(b));
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        boolean pnt = false;
        while (in.hasNext()) {
            if (pnt) System.out.println();
            else pnt = true;
            String a, b;
            a = in.next();
            b = in.next();
            System.out.println(gcd(new BigInteger(a), new BigInteger(b)));
        }
    }
}

