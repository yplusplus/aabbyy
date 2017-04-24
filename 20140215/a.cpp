#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int N = 55;
const int offset = 111;
const int inf = 1 << 30;
int d[N];
vector<int> g[N];
int dp[N][N][N * 4], cnt[N][N][N * 4];
int n, m, X, Y;

int dfs(int x, int y, int z) {
    if (cnt[x][y][z + offset] != -1) return dp[x][y][z + offset];
    if (g[x].empty() && g[y].empty()) {
        cnt[x][y][z + offset] = 1;
        return dp[x][y][z + offset] = -z;
    }
    int res = -inf;
    int t = 0;
    for (int i = 0; i < g[x].size(); i++) {
        int nx = g[x][i];
        int ret = -dfs(nx, y, z + d[nx]);
        if (ret > res) {
            res = ret;
            t = 1;
        } else if (ret == res) t++;
    }
    for (int i = 0; i < g[y].size(); i++) {
        int ny = g[y][i];
        int ret = -dfs(x, ny, z - d[ny]);
        if (ret > res) {
            res = ret;
            t = 1;
        } else if (ret == res) t++;
    }
    dp[x][y][z + offset] = res, cnt[x][y][z + offset] = t;
    return res;
}

int main() {
    while (~scanf("%d%d%d%d", &n, &m, &X, &Y)) {
        for (int i = 0; i < n; i++) {
            g[i].clear();
            scanf("%d", &d[i]);
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            g[a].push_back(b);
        }
        memset(cnt, -1, sizeof(cnt));
        dfs(X, Y, 1);
        printf("%d %d\n", dp[X][Y][1 + offset], cnt[X][Y][1 + offset]);
    }
    return 0;
}

