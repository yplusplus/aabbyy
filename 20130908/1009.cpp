#pragma comment(linker,"/STACK:1024000000,1024000000");
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define ll int
const int N = 1000010;
const ll inf = 1 << 25;
int eh[N], tot;
ll dp[N][3], f[N][2];
int n;

struct Edge {
    int v, next;
} et[N << 1];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u, int fa) {
    dp[u][0] = dp[u][1] = inf;
    f[u][0] = f[u][1] = inf;
    int cnt = 0;
    ll sum = 0;
    bool leaf = true;
    dp[u][2] = 0;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == fa) continue;
        leaf = false;
        dfs(v, u);
        cnt++;
        sum += min(min(dp[v][1], dp[v][2]), dp[v][0]);
        ll t = dp[v][0] - min(min(dp[v][1], dp[v][2]), dp[v][0]);
        if (t < f[u][0]) f[u][1] = f[u][0], f[u][0] = t;
        else if (t < f[u][1]) f[u][1] = t;
    }
    if (cnt >= 1) {
        dp[u][0] = min(dp[u][0], 2 * (cnt - 1) + sum + f[u][0]);
    }
    if (cnt >= 2) {
        dp[u][1] = min(dp[u][1], 2 * (cnt - 2) + sum + f[u][0] + f[u][1]);
    }
    dp[u][2] = 2 * cnt + sum;
    if (leaf) dp[u][0] = dp[u][1] = dp[u][2] = 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        init();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        dfs(1, 0);
        /*
        for (int i = 1; i <= n; i++) {
            cout << "***********" << endl;
            cout << i << endl;
            cout << dp[i][0] << " " << dp[i][1] << endl;
            cout << f[i][0] << " " << f[i][1] << endl;
        }
        */
        cout << min(min(dp[1][0], dp[1][1]), dp[1][2]) + 1 << endl;
    }
}
