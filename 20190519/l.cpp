#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 100000 + 10;
const long long MOD = 998244353;
double dp[N][2];
vector<int> vec[N];
int n, m;
bool visit[N][2];
long long inv[N];

long long mul(long long a, long long b) { return a * b % MOD; } 
long long add(long long a, long long b) { return (a + b) % MOD; }

int dfs(int u, int k) {
    if (visit[u][k]) return dp[u][k];
    visit[u][k] = true;
    int siz = vec[u].size();
    dp[u][k] = 1;
    if (k == 0) {
        siz++;
        long long t = mul((dfs(u, 1)), inv[siz]);
        dp[u][k] = add(dp[u][k], t);
    }
    for (int v: vec[u]) {
        long long t = mul((dfs(v, 0) + 1), inv[siz]);
        dp[u][k] = add(dp[u][k], t);
    }
    return dp[u][k];
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        visit[i][0] = visit[i][1] = false;
        vec[i].clear();
    }
    for (int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        vec[a].push_back(b);
    }
    int ans = dfs(1, 0);
    printf("%d\n", ans);
}

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = mul((MOD - MOD / i), inv[MOD % i]);
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
