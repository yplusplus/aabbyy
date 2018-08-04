#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 15;
const int INF = 1e9 + 7;

int n;
vector<int> g[1 << N];

int dfs(int l, int r)
{
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    int u = dfs(l, mid);
    int v = dfs(mid + 1, r);

    int mx_u = 0;
    for (int i = 0; i < g[u].size(); i++) {
        mx_u = max(mx_u, g[u][i]);
    }
    int mx_v = 0;
    for (int i = 0; i < g[v].size(); i++) {
        mx_v = max(mx_v, g[v][i]);
    }

    int winner = -1, score = -1;
    if (mx_u > mx_v) {
        winner = u;
        score = mx_v;
    }
    else {
        winner = v;
        score = mx_u;
    }

    int idx = -1;
    for (int i = 0; i < g[winner].size(); i++) {
        if (g[winner][i] > score && (idx == -1 || g[winner][idx] > g[winner][i])) {
            idx = i;
        }
    }
    g[winner][idx] = -1;
    return winner;
}

int main()
{
    int T, cas = 1;
    cin >> T;
    while (T --) {
        scanf("%d", &n);
        int x;
        for (int i = 1; i <= (1 << n); i++) {
            g[i].clear();
            for (int j = 0; j < n; j++) {
                scanf("%d", &x);
                g[i].push_back(x);
            }
        }
        printf("Case #%d: %d\n", cas ++, dfs(1, 1 << n));
    }
    return 0;
}
