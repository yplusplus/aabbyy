#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

using LL = long long;
const LL MOD = 1000000007LL;

LL add(LL a, LL b) { return (a + b) % MOD; }
LL mul(LL a, LL b) { return (a * b) % MOD; }

const int N = 5555;
LL C[N][N];

int n;
int A[N];
int ans[N];
vector<int> vec[N], son[N];

void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
        }
        C[i][0] = C[i][i] = 1;
    }
}

int pow_mod(int x, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = mul(res, x);
        x = mul(x, x);
        n >>= 1;
    }
    return res;
}

int inv(int x) {
    return pow_mod(x, MOD - 2);
}

int dfs(int u, int fa) {
    son[u].clear();
    int t = 1;
    for (int v: vec[u]) {
        if (v == fa) continue;
        int ret = dfs(v, u);
        son[u].push_back(ret);
        t += ret;
    }
    if (n - t > 0) son[u].push_back(n - t);
    if (son[u].size() <= 2) {
        for (int j = 1; j <= n; j++) {
            ans[j] = add(ans[j], C[n - 1][j - 1]);
        }
    }
    //cout << "nodes of " << u << " is " << t << endl;
    return t;
}

void solve() {
    for (int i = 0; i <= n; i++) {
        A[i] = 0;
        ans[i] = 0;
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        if (son[i].size() <= 2) continue;
        for (int j = 0; j < son[i].size(); j++) {
            for (int k = j + 1; k < son[i].size(); k++) {
                A[son[i][j] + son[i][k]]--;
            }
            A[son[i][j]] += son[i].size() - 2;
        }
        for (int j = 1; j <= n; j++) {
            ans[j] = add(ans[j], C[n][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ans[i] = add(ans[i], mul(add(A[j], MOD), C[j][i]));
        }
    }

    for (int i = 1; i <= n; i++) {
        ans[i] = mul(ans[i], inv(C[n][i]));
        printf("%d\n", ans[i]);
    }
}

int main() {
    init();
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        solve();
    }
    return 0;
}
