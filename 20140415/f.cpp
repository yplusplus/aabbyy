#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 44;
const int M = N * N;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

char board[N][N];
int n, m;
bool visit[N][N];
vector<int> vec[M];
int blocks;
int id[N][N];
bool g[M][M];
int dep[M];

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(int sx, int sy, int bid) {
    queue<int> que;
    que.push(sx);
    que.push(sy);
    visit[sx][sy] = true;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int y = que.front(); que.pop();
        id[x][y] = bid;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (check(nx, ny) && board[nx][ny] == board[x][y] && !visit[nx][ny]) {
                que.push(nx);
                que.push(ny);
                visit[nx][ny] = true;
            }
        }
    }
}

void init() {
    memset(visit, false, sizeof(visit));
    blocks = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visit[i][j]) {
                bfs(i, j, blocks++);
            }
        }
    }
    memset(g, false, sizeof(g));
    for (int i = 0; i < blocks; i++) vec[i].clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (check(x, y) && board[x][y] != board[i][j]) {
                    int u = id[x][y], v = id[i][j];
                    if (!g[u][v]) {
                        g[u][v] = g[v][u] = true;
                        vec[u].push_back(v);
                        vec[v].push_back(u);
                    }
                }
            }
        }
    }
}


int calc(int s) {
    memset(dep, -1, sizeof(dep));
    queue<int> que;
    dep[s] = 0;
    que.push(s);
    int res = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        res = max(res, dep[u]);
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                que.push(v);
            }
        }
    }
    return res;
}

void solve() {
    init();
    int ans = n * m;
    for (int i = 0; i < blocks; i++) {
        ans = min(ans, calc(i));
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", board[i]);
        solve();
    }
    return 0;
}
