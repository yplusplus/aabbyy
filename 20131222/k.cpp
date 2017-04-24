#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 15;
const int inf = 1 << 25;
char maz[N][N];
int id[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, m;
bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(int x, int y, int _id) {
    queue<int> que;
    que.push(x);
    que.push(y);
    id[x][y] = _id;
    while (!que.empty()) {
        x = que.front(); que.pop();
        y = que.front(); que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (check(nx, ny) && maz[nx][ny] == '#' && id[nx][ny] == -1) {
                id[nx][ny] = _id;
                que.push(nx); que.push(ny);
            }
        }
    }
}

int ti[N][N][N][N];
int bfs2(int sx, int sy) {
    queue<int> que;
    ti[sx][sy][sx][sy] = 0;
    que.push(sx); que.push(sy);
    int res = 0;
    int x, y;
    while (!que.empty()) {
        x = que.front(); que.pop();
        y = que.front(); que.pop();
        res = max(res, ti[sx][sy][x][y]);
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (check(nx, ny) && maz[nx][ny] == '#' && ti[sx][sy][nx][ny] == -1) {
                ti[sx][sy][nx][ny] = ti[sx][sy][x][y] + 1;
                que.push(nx); que.push(ny);
            }
        }
    }
    return res;
}

int solve() {
    memset(id, -1, sizeof(id));
    memset(ti, -1, sizeof(ti));
    int cc_cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (id[i][j] == -1 && maz[i][j] == '#') bfs(i, j, cc_cnt++);
        }
    }
    if (cc_cnt == 0) return 0;
    if (cc_cnt > 2) return -1;
    int record[2] = {inf, inf};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maz[i][j] == '#') {
                record[id[i][j]] = min(record[id[i][j]], bfs2(i, j));
            }
        }
    }
    if (cc_cnt == 2) return *max_element(record, record + cc_cnt);
    int ret = inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maz[i][j] != '#') continue;
            for (int ii = 0; ii < n; ii++) {
                for (int jj = 0; jj < m; jj++) {
                    if (maz[ii][jj] != '#') continue;
                    int tmp = 0;
                    for (int x = 0; x < n; x++) {
                        for (int y = 0; y < m; y++) {
                            if (maz[x][y] == '#') tmp = max(min(ti[i][j][x][y], ti[ii][jj][x][y]), tmp);
                        }
                    }
                    ret = min(ret, tmp);
                }
            }
        }
    }
    return ret;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", maz[i]);
        }
        int ans = solve();
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}

