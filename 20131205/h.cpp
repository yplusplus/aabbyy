#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <functional>
using namespace std;

const int N = 333;
const int M = 480;
const int offset = 160;
const long long MOD = 1000000007LL;

int eh[N], tot;
long long dp[N][3][M], tmp[3][M];
int cnt[N];
int n;

struct Edge {
    int v, next;
} et[N << 1];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u, int fa) {
    cnt[u] = 1;
    dp[u][0][offset] = 2;
    dp[u][1][offset] = 1;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == fa) continue;
        dfs(v, u);
        memset(tmp, 0, sizeof(tmp));
        for (int x = -(cnt[u] + 1) / 2; x <= cnt[u]; x++) {
            for (int y = -(cnt[v] + 1) / 2; y <= cnt[v]; y++) {
                int xx = x + offset, yy = y + offset, zz = x + y + offset;
                if (zz < 0 || zz >= M) continue;
                tmp[0][zz] += dp[u][0][xx] * dp[v][0][yy] + dp[u][0][xx] * dp[v][1][yy - 1] + dp[u][0][xx] * dp[v][2][yy + 1];
                tmp[1][zz] += dp[u][1][xx] * dp[v][0][yy] + dp[u][1][xx] * dp[v][2][yy] + dp[u][2][xx] * dp[v][1][yy];
                tmp[2][zz] += dp[u][2][xx] * dp[v][0][yy] + dp[u][1][xx] * dp[v][1][yy] + dp[u][2][xx] * dp[v][2][yy];
                tmp[0][zz] %= MOD; tmp[1][zz] %= MOD; tmp[2][zz] %= MOD;
            }
        }
        memcpy(dp[u], tmp, sizeof(tmp));
        cnt[u] += cnt[v];
    }
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        memset(dp, 0, sizeof(dp));
        dfs(1, -1);
        long long ans = 0;
        for (int i = 0; i < M; i++) {
            ans += dp[1][0][i] * max(0, (i - offset)) % MOD;
            ans += dp[1][1][i] * max(0, (i + 1 - offset)) % MOD;
            ans += dp[1][2][i] * max(0, (i - 1 - offset)) % MOD;
            ans %= MOD;
        }
        ans = (ans * 3) % MOD;
        printf("%I64d\n", ans);
    }
    return 0;
}
