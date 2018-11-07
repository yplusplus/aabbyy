#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 55;
const int M = N * N;
int MOD;
int K, n, m;
long long dp[N][N][N];
long long nCr[M][M];

long long add(long long a, long long b) { return (a + b) % MOD; }
long long mul(long long a, long long b) { return (a * b) % MOD; }

void init() {
    nCr[0][0] = 1;
    for (int i = 1; i < M; i++) {
        nCr[i][0] = nCr[i][i] = 1;
        for (int j = 1; j < i; j++) {
            nCr[i][j] = add(nCr[i - 1][j - 1], nCr[i - 1][j]);
        }
    }
}

long long ncr(int n, int m) {
    if (n < m) return 0;
    if (n == m) return 1;
    //cout << n << " " << m << endl;
    return nCr[n][m];
}

void solve() {
    init();
    dp[0][0][0] = 1;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= K; j++) {
            for (int k = 0; k <= n; k++) {
                if (dp[i][j][k] == 0) continue;
                for (int l = k + 1; l <= n; l++) {
                    int x = (n - l) * (l - k) + (l - k);
                    int y = (n - l) * (l - k);
                    for (int c = 1; c <= x && c + i <= m; c++) {
                        //cout << i << " " << j << " " << k << " " << l << " " << x << " " << y << " " << c << endl;
                        long long t = mul(dp[i][j][k], ncr(x, c) + MOD - ncr(y, c));
                        dp[i + c][j + 1][l] = add(dp[i + c][j + 1][l], t);
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = add(ans, dp[m][K][i]);
    }
    cout << ans << endl;
}

int main() {
    cin >> n >> m >> K >> MOD;
    solve();
    return 0;
}
