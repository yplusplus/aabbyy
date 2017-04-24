#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 12;
long long dp[1 << N][1222];
int bits[1 << N];
int p[N][N];
int n, m;
long long fac[N + 1];

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    bits[0] = 0;
    for (int i = 1; i < 1 << N; i++) bits[i] = bits[i >> 1] + (i & 1);
    int T;
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> p[i][j];
            }
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int mask = 0; mask < 1 << n; mask++) {
            for (int j = 0; j < 1222; j++) {
                if (dp[mask][j] == 0) continue;
                for (int k = 0; k < n; k++) {
                    if (~mask >> k & 1) {
                        dp[mask | (1 << k)][j + p[k][bits[mask]]] += dp[mask][j];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = m; i < 1222; i++) {
            ans += dp[(1 << n) - 1][i];
        }
        if (ans == 0) {
            cout << "No solution" << endl;
        } else {
            long long d = __gcd(ans, fac[n]);
            cout << fac[n] / d << "/" << ans / d << endl;
        }
    }
    return 0;
}
