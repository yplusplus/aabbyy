#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

using LL = long long;

const LL MOD = 998244353LL;

const int N = 222222;
vector<int> vec[N];
LL cnt[N];
LL dp[N];
LL f[N], g[N];
int father[N];
int n;

inline LL add(LL a, LL b) { return (a + b) % MOD; }
inline LL mul(LL a, LL b) { return (a * b) % MOD; }
inline LL eval(LL x) { return (x + 1LL) * x >> 1; }

LL quick_mod(LL a, LL n) {
    LL res = 1;
    while (n) {
        if (n & 1) res = mul(res, a);
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

void dfs(int u, int fa) {
    father[u] = fa;
    cnt[u] = 1;
    dp[u] = 1;
    g[u] = 0;
    for (int v: vec[u]) {
        if (v == fa) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
        dp[u] = mul(dp[u], add(dp[v], f[v]));
        g[u] += eval(cnt[v]);
    }
    f[u] = quick_mod(2, eval(cnt[u]));
    f[u] = add(f[u], MOD - quick_mod(2, g[u] % (MOD - 1)));
}

LL calc(int u) {
    int fa = father[u];
    if (fa == 0) return 1LL;

    LL res = quick_mod(2, eval(n - cnt[u]) % (MOD - 1));
    LL x = g[fa];
    x -= eval(cnt[u]);
    x += eval(n - cnt[fa]);
    res = add(res, MOD - quick_mod(2, x % (MOD - 1)));
    return res;
}

void solve() {
    dfs(1, 0);
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        LL t = dp[i];
        //cout << i << " " << t << endl;
        t = mul(t, calc(i));
        //cout << i << " " << t << endl;
        ans = add(ans, t);
    }
    cout << ans << endl;
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            vec[i].clear();
        }

        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            vec[u].push_back(v);
            vec[v].push_back(u);
        }

        solve();
    }
    return 0;
}
