package main;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static final int N = 55;
    static final BigInteger _0 = BigInteger.ZERO;
    static final BigInteger _1 = BigInteger.ONE;
    public static void main(String[] args) {
       BigInteger[][] dp = new BigInteger[N][N];
       for (int i = 0; i < N; i++) {
           for (int j = 0; j < N; j++) dp[i][j] = _0;
       }
       dp[1][1] = _1;
       for (int i = 2; i < N; i++) {
           for (int j = 1; j <= i; j++) {
               dp[i][j] = dp[i - 1][j - 1].add(dp[i - 1][j].multiply(BigInteger.valueOf(i - 1)));
           }
       }
       BigInteger[] fac = new BigInteger[N];
       fac[0] = _1;
       for (int i = 1; i < N; i++) fac[i] = fac[i - 1].multiply(BigInteger.valueOf(i));
       BigInteger[][] ans1 = new BigInteger[N][N];
       BigInteger[][] ans2 = new BigInteger[N][N];
       for (int i = 1; i < N; i++) {
           BigInteger sum = _0;
           for (int j = 1; j <= i; j++) {
               if ((j & 1) != 0) sum = sum.add(dp[i][j]);
               BigInteger d = sum.gcd(fac[i]);
               ans1[i][j] = sum.divide(d);
               ans2[i][j] = fac[i].divide(d);
           }
       }
       int a, b;
       Scanner in = new Scanner(System.in);
       while (in.hasNext()) {
           a = in.nextInt();
           b = in.nextInt();
           System.out.println(ans1[a][b] + "/" + ans2[a][b]);
       }
    }
}
