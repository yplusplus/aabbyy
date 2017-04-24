#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 55555;
vector<int> vec[N];
int dp[N][2];
int val[N], flip[N];
int n, X, Y;

void dfs(int u, int state) {
    if (flip[u]) state ^= 1;
    if (state) val[u] = -val[u];
    dp[u][0] = val[u], dp[u][1] = -val[u];
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        dfs(v, state);
        dp[u][0] += max(dp[v][0], dp[v][1] - (flip[v] ? Y : X));
        dp[u][1] += max(dp[v][1], dp[v][0] - (flip[v] ? Y : X));
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &X, &Y)) {
        for (int i = 0; i <= n; i++) vec[i].clear();
        for (int i = 1; i <= n; i++) {
            int fa, x;
            scanf("%d%d%d%d", &val[i], &fa, &flip[i], &x);
            vec[fa].push_back(i);
            if (x) val[i] = -val[i];
        }
        dfs(0, 0);
        int ans = dp[0][0];
        if (ans < 0) puts("HAHAHAOMG");
        else printf("%d\n", ans);
    }
    return 0;
}
