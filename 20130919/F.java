import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    static int N = 222;
    static final BigInteger ZERO = new BigInteger("0");
    static final BigInteger ONE = new BigInteger("1");
    static final BigInteger TEN = new BigInteger("10");

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BigInteger[] exp10 = new BigInteger[N];
        exp10[0] = ONE;
        for (int i = 1; i < N; i++) {
            exp10[i] = exp10[i - 1].multiply(TEN);
        }
        int T = in.nextInt();
        for (int cas = 1; cas <= T; cas++) {
            String a = in.next();
            String b = in.next();
            BigInteger A = new BigInteger(a);
            BigInteger B = new BigInteger(b);
            System.out.printf("Case #%d: ", cas);
            if (B.compareTo(ZERO) == 0 && b.length() == 1) {
                boolean ok = false;
                for (int i = 0; i < a.length(); i++) {
                    if (a.charAt(i) == '0') {
                        ok = true;
                    }
                }
                if (!ok) {
                    int i = 0;
                    while (A.mod(exp10[1]).compareTo(ZERO) != 0) {
                        A = A.add(ONE);
                        i++;
                    }
                    System.out.println(i);
                } else {
                    System.out.println(0);
                }
                continue;
            }
            int i = -1, l = b.length();
            BigInteger ans = exp10[N - 1];
            do {
                i++;
                BigInteger C = A.divide(exp10[i]).mod(exp10[l]);
                int cmp = C.compareTo(B);
                if (cmp == 0) {
                    ans = ZERO;
                    //System.out.println("yes");
                    break;
                } else if (cmp < 0) {
                    BigInteger D = A.divide(exp10[i + l]).multiply(exp10[l]).add(B).multiply(exp10[i]);
                    BigInteger tmp = D.subtract(A);
                    if (tmp.compareTo(ans) < 0) {
                        ans = tmp;
                    }
                    //System.out.println("~~" + tmp);
                } else {
                    BigInteger D = A.divide(exp10[i + l]).add(ONE).multiply(exp10[l]).add(B).multiply(exp10[i]);
                    BigInteger tmp = D.subtract(A);
                    if (tmp.compareTo(ans) < 0) {
                        ans = tmp;
                    }
                    //System.out.println("!!" + tmp);
                }
                //System.out.println(i + " " + l + " " + A + " " + exp10[i + l]);
            } while (A.divide(exp10[i + l - 1]).compareTo(ZERO) != 0);
            System.out.println(ans);
            //System.out.println(ans.add(A));
        }
    }
}