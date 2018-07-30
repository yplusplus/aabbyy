#include "bits/stdc++.h"
using namespace std;
typedef long long LL;
const int N = 5101;
const int mod = 1e9 + 7;

int n, k, D;
vector<int> g[N];
int c[N];
bool vis[N];

void dfs_dec(int u, int fa, int d)
{
    if (c[u]) c[u] --;
    if (d == 0) return ;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs_dec(v, u, d - 1);
    }
}

int Cal(int d)
{
    int ret = 1;
    for (int i = 1; i <= n; i++) c[i] = k, vis[i] = false;
    queue<int> que;
    que.push(1);
    vis[1] = true;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        ret = 1LL * ret * c[u] % mod;
        dfs_dec(u, -1, d);
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (vis[v]) continue;
            que.push(v);
            vis[v] = true;
        }
    }
    return ret;
}

int main()
{
    while (cin >> n >> k >> D) {
        for (int i = 1; i <= n; i++) g[i].clear();
        int u, v;
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int ret = (Cal(D - 1) - Cal(D) + mod) % mod;
        cout << ret << endl;
    }
    return 0;
}
