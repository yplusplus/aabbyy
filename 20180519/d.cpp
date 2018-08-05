#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MOD = 1000000007;
const int N = 5005;

int f[N][N];
int g[N];
int inv[N];

int add(long long a, long long b) { return (a + b) % MOD; }
int mul(long long a, long long b) { return (a * b) % MOD; }

void init() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = mul((MOD - MOD / i), inv[MOD % i]);
    }

    memset(f, 0, sizeof(f));
    f[0][0] = 1;
   for (int i = 1; i < N; i++) {
        g[0] = f[i - 1][0];
        for (int j = 1; j < N; j++) g[j] = add(g[j - 1], f[i - 1][j]);
        for (int j = i; j < N; j++) {
            f[i][j] = add(f[i][j - 1], g[j - 1]);
        }
    }
}

int main() {
    init();
    int n, m;
    while (cin >> n >> m) {
        int ans = 0;
        for (int i = 1; i <= min(n, m); i++) {
            long long t = mul(mul(f[i][n], f[i][m]), inv[i]);
            ans = add(ans, t);
        }
        ans = mul(n + m, ans);
        cout << ans << endl;
    }
    return 0;
}
