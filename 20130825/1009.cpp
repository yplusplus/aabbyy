#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

int star_number, rally_number;
int n, m;
const int N = 55;
const int M = 11111;
bool visit[M];
int match[M];
vector<int> vec[N];
char maz[111][111];
pii star[M];
int dist[2][111][111];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool dfs(int u) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            visit[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match() {
    memset(match, -1, sizeof(match));
    int cnt = 0;
    for (int i = 0; i < rally_number - 1; i++) {
        memset(visit, false, sizeof(visit));
        cnt += dfs(i);
    }
    return cnt;
}

struct Rally {
    int x, y;
    Rally() {}
    Rally(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Rally &a) const {
        return maz[x][y] < maz[a.x][a.y];
    }
} rally[N];

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maz[x][y] != '#';
}

void bfs(int sx, int sy, int id) {
    queue<int> que;
    que.push(sx);
    que.push(sy);
    memset(dist[id], -1, sizeof(dist[id]));
    dist[id][sx][sy] = 0;
    while (!que.empty()) {
        sx = que.front(), que.pop();
        sy = que.front(), que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = sx + dx[i], ny = sy + dy[i];
            if (check(nx, ny) && dist[id][nx][ny] == -1) {
                dist[id][nx][ny] = dist[id][sx][sy] + 1;
                que.push(nx);
                que.push(ny);
            }
        }
    }
    return ;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        star_number = rally_number = 0;
        for (int i = 0; i < N; i++) vec[i].clear();
        for (int i = 0; i < n; i++) {
            scanf("%s", &maz[i]);
            for (int j = 0; j < m; j++) {
                if (isalpha(maz[i][j])) {
                    rally[rally_number++] = Rally(i, j);
                } else if (maz[i][j] == '*') {
                    star[star_number++] = mp(i, j);
                }
            }
        }
        sort(rally, rally + rally_number);
        if (rally_number > 0) bfs(rally[0].x, rally[0].y, 0);
        bool found = false;
        for (int i = 1; i < rally_number; i++) {
            bfs(rally[i].x, rally[i].y, i & 1);
            int path = dist[i & 1][rally[i - 1].x][rally[i - 1].y];
            if (path == -1) {
                found = true;
                break;
            }
            for (int j = 0; j < star_number; j++) {
                if (dist[0][star[j].fi][star[j].se] + dist[1][star[j].fi][star[j].se] == path) vec[i - 1].pb(j);
            }
        }
        if (found) puts("-1");
        else {
            printf("%d\n", Match());
        }
    }
    return 0;
}
