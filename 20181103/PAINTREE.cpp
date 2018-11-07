#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int MOD = 998244353;
const int N = 2000 + 10;
vector<int> vec[N];

int fac[N];
int inv[N];
int n;
int son[N];

long long add(long long a, long long b) { return (a + b) % MOD; }
long long mul(long long a, long long b) { return (a * b) % MOD; }

long long quick_pow(long long a, long long b) {
    a %= MOD;
    long long res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int dp[N][N][4];
int tmp[N][3];
void dfs(int u, int fa) {
    son[u] = 1;
    dp[u][0][0] = 1;
    dp[u][1][2] = 1;
    for (int v: vec[u]) {
        if (v == fa) continue;
        dfs(v, u);
        son[u] += son[v];
        for (int i = 0; i <= son[u]; i++) {
            for (int j = min(son[v], i); j >= max(0, i - son[u] + son[v]); j--) {
                tmp[i][0] = add(tmp[i][0], mul(dp[u][i - j][0], dp[v][j][3]));
                tmp[i][1] = add(tmp[i][1], mul(dp[u][i - j][1], dp[v][j][3]));
                tmp[i][2] = add(tmp[i][2], mul(dp[u][i - j][2], dp[v][j][3]));
                long long t = add(dp[v][j + 1][1], dp[v][j + 1][2]);
                tmp[i][0] = add(tmp[i][0], mul(dp[u][i - j][1], t));
                tmp[i][1] = add(tmp[i][1], mul(dp[u][i - j][2], t));
            }
        }
        for (int i = 0; i <= son[u]; i++) {
            for (int j = 0; j < 3; j++) {
                dp[u][i][j] = tmp[i][j];
                tmp[i][j] = 0;
            }
        }
    }
    for (int i = 0; i <= son[u]; i++) {
        dp[u][i][3] = ((long long)dp[u][i][0] + dp[u][i][1] + dp[u][i][2]) % MOD;
    }
}

void solve() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) { fac[i] = mul(fac[i - 1], i); }

    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    dfs(1, 0);

    long long all = (n * (n + 1LL)) / 2LL;
    for (int i = 1, p = all; i <= n; i++, p = mul(p, all)) {
        inv[i] = quick_pow(p, MOD - 2);
    }

    long long sum = 0;
    long long ans = 0;
    for (int i = n; i >= 1; i--) {
        long long t = mul(dp[1][i][3], fac[i]);
        t = mul(t, inv[i]);
        t = add(t, MOD - sum);
        ans = add(ans, mul(t, i));
        sum = add(sum, t);
    }

    printf("%d\n", (int)ans);
}

int main() {
    solve();
    return 0;
}
