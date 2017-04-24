#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 5;
double dp[N][N][N][N];
int A, B, C, D;

int main() {
    freopen("school.in", "r", stdin);
    freopen("school.out", "w", stdout);
    scanf("%d%d%d%d", &A, &B, &C, &D);
    dp[A][B][C][D] = 0;
    for (int times = 0; times < 1000; times++) {
        for (int a = 0; a <= A; a++) {
            for (int b = 0; b <= B; b++) {
                for (int c = 0; c <= C; c++) {
                    for (int d = 0; d <= D; d++) {
                        if (a == A && b == B && c == C && d == D) continue;
                        int na, nb, nc, nd;
                        double record[N] = {0};
                        int cnt[N] = {0};
                        for (int da = -1; da <= 1; da++) {
                            if (a + da < 0 || a + da > A) continue;
                            na = a + da;
                            for (int db = -1; db <= 1; db++) {
                                if (b + db < 0 || b + db > B) continue;
                                nb = b + db;
                                for (int dc = -1; dc <= 1; dc++) {
                                    if (c + dc < 0 || c + dc > C) continue;
                                    nc = c + dc;
                                    for (int dd = -1; dd <= 1; dd++) {
                                        if (d + dd < 0 || d + dd > D) continue;
                                        nd = d + dd;
                                        if (da == 1) record[1] += dp[na][nb][nc][nd], cnt[1]++;
                                        if (db == 1) record[2] += dp[na][nb][nc][nd], cnt[2]++;
                                        if (dc == 1) record[3] += dp[na][nb][nc][nd], cnt[3]++;
                                        if (dd == 1) record[4] += dp[na][nb][nc][nd], cnt[4]++;
                                    }
                                }
                            }
                        }
                        double t = 1e300;
                        for (int i = 1; i <= 4; i++) {
                            t = min(t, record[i] * 1.0 / cnt[i]);
                        }
                        dp[a][b][c][d] = t + 1.0;
                    }
                }
            }
        }
    }
    printf("%.15f\n", dp[0][0][0][0]);
    return 0;
}
