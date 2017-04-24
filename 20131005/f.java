import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    static final BigInteger _26 = new BigInteger("26");
    static final BigInteger _0 = new BigInteger("0");
    static final BigInteger _1 = new BigInteger("1");
    static BigInteger[] cnt = new BigInteger[55];
    
    static void print(BigInteger a) {
        int l = 1;
        BigInteger t = a;
        while (t.compareTo(cnt[l]) > 0) {
            t = t.subtract(cnt[l]);
            l++;
        }
        String ans = "";
        for (int i = l - 1; i >= 0; i--) {
            ans += (char) ('a' + t.divide(cnt[i]).mod(_26).intValue());
        }
        System.out.print(ans);
    }
    
    public static void main(String[] args) {
        int n;
        String m;
        Scanner in = new Scanner(System.in);
        for (int i = 0; i < 55; i++) {
            cnt[i] = _1;
            for (int j = 0; j < i; j++) {
                cnt[i] = cnt[i].multiply(_26);
            }
        }
        while (in.hasNext()) {
            n = in.nextInt();
            m = in.next();
            BigInteger sum = _0;
            for (int i = 1; i <= n; i++) sum = sum.add(cnt[i]);
            BigInteger p = sum.divide(new BigInteger(m));
            BigInteger r = sum.mod(new BigInteger(m));
            BigInteger cur = _0;
//            System.out.println(sum);
            int im = Integer.parseInt(m);
            int ir = Integer.parseInt(r.toString());
            for (int i = 0; i < im; i++) {
                BigInteger nx = cur.add(p);
                if (i < ir) nx = nx.add(_1);
                print(cur);
                System.out.print('-');
                print(nx.subtract(_1));
                System.out.println();
                cur = nx;
//                System.out.println(cur);
            }
        }
    }
}

