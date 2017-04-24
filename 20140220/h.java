import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static final BigInteger _0 = BigInteger.ZERO;
    static final BigInteger _1 = BigInteger.ONE;
    static final int N = 111;
    public static void main(String[] args) {
        BigInteger[][] C = new BigInteger[N][N];
        for (int i = 0; i < N; i++) {
            C[i][0] = C[i][i] = _1;
            for (int j = 1; j < i; j++) C[i][j] = C[i - 1][j - 1].add(C[i - 1][j]);
        }
        BigInteger[][] dp = new BigInteger[N][N];
        int n, m, l;
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) {
            m = in.nextInt();
            n = in.nextInt();
            l = in.nextInt();
            if (m < l) {
                System.out.println("mukyu~");
                continue;
            }
            for (int i = 0; i <= m; i++) for (int j = 0; j <= n; j++) dp[i][j] = _0;
            dp[0][0] = _1;
            for (int j = 0; j < n; j++) {
                for (int i = 0; i <= m; i++) {
                    if (dp[i][j].compareTo(_0) == 0) continue;
                    for (int k = 0; k < l; k++) {
                        if (i + k <= m) dp[i + k][j + 1] = dp[i + k][j + 1].add(dp[i][j].multiply(C[m - i][k]));
                    }
                }
            }
            BigInteger sum = _1;
            for (int i = 0; i < m; i++) {
                sum = sum.multiply(BigInteger.valueOf(n));
            }
            BigInteger ans = sum.subtract(dp[m][n]), d = ans.gcd(sum);
            System.out.println(ans.divide(d) + "/" + sum.divide(d));
        }
    }
}
