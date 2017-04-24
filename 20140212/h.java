package main;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    static final BigInteger _0 = BigInteger.ZERO;
    static final BigInteger _1 = BigInteger.ONE;

    static private void exgcd(BigInteger a, BigInteger b, BigInteger[] x) {
        if (b.compareTo(_0) == 0) {
            x[0] = _1;
            x[1] = _0;
        } else {
            exgcd(b, a.mod(b), x);
            BigInteger temp = x[0];
            x[0] = x[1];
            x[1] = temp;
            x[1] = x[1].subtract(a.divide(b).multiply(x[0]));
        }
    }
    static final int N = 1000;
    static final int NN = 180;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BigInteger[] prm = new BigInteger[NN];
        int[] prm_i = new int[NN];
        int pn = 0;
        boolean[] np = new boolean[N];
        np[0] = np[1] = true;
        for (int i = 0; i < N; i++) {
            if (!np[i]) {
                for (int j = i << 1; j < N; j += i) {
                    np[j] = true;
                }
            }
        }
        for (int i = 0; i < N; i++) {
            if (!np[i]) {
                prm[pn] = BigInteger.valueOf(i);
                prm_i[pn++] = i;
            }
        }
        //for (int i = 0; i < pn; i++) System.out.println(i + " " + prm[i]);
        BigInteger[] M = new BigInteger[NN];
        BigInteger[] Mp = new BigInteger[NN];
        BigInteger product_M = _1;
        for (int i = 0; i < pn; i++) {
            product_M = product_M.multiply(prm[i]);
        }
        //System.out.println(product_M);
        for (int i = 0; i < pn; i++) {
            M[i] = product_M.divide(prm[i]);
        }
        for (int i = 0; i < pn; i++) {
            /*
            BigInteger[] x = new BigInteger[2];
            exgcd(M[i].mod(prm[i]), prm[i], x);
            Mp[i] = x[0];
            if (Mp[i].compareTo(_0) < 0) {
                Mp[i] = Mp[i].add(prm[i]);
            }
            */
            Mp[i] = M[i].modInverse(prm[i]);
            //System.out.println(i + " " + prm[i] + " " + Mp[i]);
            M[i] = M[i].multiply(Mp[i]).mod(product_M);
        }
        BigInteger[] A = new BigInteger[2];
        String s;
        while (in.hasNext()) {
            for (int i = 0; i < 2; i++) {
                s = in.next();
                A[i] = new BigInteger(s);
            }
            int len = in.nextInt();
            s = in.next();
            int[][] val = new int[3][NN];
            for (int i = 0; i < pn; i++) {
                for (int j = 0; j < 2; j++) {
                    val[j][i] = A[j].mod(prm[i]).intValue();
                }
            }
            for (int i = 0; i < len; i++) {
                if (s.charAt(i) == '*') {
                    for (int j = 0; j < pn; j++) {
                        val[2][j] = val[0][j] * val[1][j] % prm_i[j];
                    }
                } else if (s.charAt(i) == '+') {
                    for (int j = 0; j < pn; j++) {
                        val[2][j] = (val[0][j] + val[1][j]) % prm_i[j];
                    }
                } else {
                    for (int j = 0; j < pn; j++) {
                        val[2][j] = (val[0][j] - val[1][j] + prm_i[j]) % prm_i[j];
                    }
                }
                for (int j = 0; j < 2; j++) {
                    System.arraycopy(val[j + 1], 0, val[j], 0, pn);
                }
            }
            BigInteger ans = _0;
            for (int i = 0; i < pn; i++) {
                ans = ans.add(M[i].multiply(BigInteger.valueOf(val[2][i])));
            }
            ans = ans.mod(product_M);
            if (ans.compareTo(_0) < 0) {
                ans = ans.add(product_M);
            }
            System.out.println(ans);
        }
    }
}
