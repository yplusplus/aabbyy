#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
const int M = 15;
const int N = 111111;
int a[N];
int dp[N][M];
int n, m, k;
int nx[N][M];

int main() {
    while (~scanf("%d%d%d", &n, &m, &k)) {
        a[0] = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= k; j++) {
                nx[i][j] = 0;
            }
            for (int j = 0; j <= m; j++) {
                dp[i][j] = 0;
            }
        }

        nx[n][0] = n + 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= k; j++) {
                if (a[i + 1] == j) nx[i][j] = i + 1;
                else nx[i][j] = nx[i + 1][j];
            }
        }

        dp[0][0] = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (dp[i][j] == 0) continue;
                for (int c = 0; c <= k; c++) {
                    if (nx[i][c] == -1) continue;
                    int nexti = nx[i][c];
                    int nextj = j + nexti - i - 1;
                    if (nextj <= m) {
                        dp[nexti][nextj] += dp[i][j];
                        dp[nexti][nextj] %= MOD;
                    }
                }
            }
        }

        printf("%d\n", dp[n+1][m]);
    }

    return 0;
}
