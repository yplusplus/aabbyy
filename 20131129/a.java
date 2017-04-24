package main;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static final int N = 44;
    static final int[] dx = { -1, -1, -1, 0, 1, 1, 1, 0 };
    static final int[] dy = { -1, 0, 1, 1, 1, 0, -1, -1 };
    static int n;
    static int encode(int x, int y) { return x * n + y; }
    static boolean inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; }
    public static void main(String[] args) {
        BigInteger[][] mat = new BigInteger[N][N];
        Scanner in = new Scanner(System.in);
        int _;
        _ = in.nextInt();
        for (int cas = 0; cas < _; cas++) {
            n = in.nextInt();
            for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) mat[i][j] = new BigInteger("0");
            for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
                int i1 = encode(i, j);
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (inmat(x, y) == false) continue;
                    int i2 = encode(x, y);
                    mat[i1][i1] = mat[i1][i1].add(BigInteger.ONE);
                    mat[i2][i1] = mat[i2][i1].subtract(BigInteger.ONE);
                }
            }
            BigInteger ans = new BigInteger("1");
            int m = n * n;
            /*
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) System.out.print(mat[i][j] + " ");
                System.out.println("");
            }
             */
            for (int p = 1; p < m; p++) {
                for (int i = p + 1; i < m; i++) {
                    while (mat[i][p].compareTo(BigInteger.ZERO) != 0) {
                        BigInteger k = mat[p][p].divide(mat[i][p]);
                        for (int j = p; j < m; j++) {
                            mat[p][j] = mat[p][j].subtract(mat[i][j].multiply(k));
                            BigInteger temp = mat[p][j];
                            mat[p][j] = mat[i][j];
                            mat[i][j] = temp;
                        }
                        ans = BigInteger.ZERO.subtract(ans);
                    }
                }
                ans = ans.multiply(mat[p][p]);
            }
            System.out.println(ans);
        }
    }
}
