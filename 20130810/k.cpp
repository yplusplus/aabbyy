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
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
int dir[256];
bool visit[100][100];
bool reach[100][100];

bool check(int x, int y) {
    return x >= 0 && x < 100 && y >= 0 && y < 100;
}

bool bfs(int sx, int sy) {
    //cout << sx << " " << sy << endl;
    queue<int> que;
    que.push(sx);
    que.push(sy);
    int x, y;
    memset(reach, false, sizeof(reach));
    //reach[sx][sy] = true;
    while (!que.empty()) {
        x = que.front(), que.pop();
        y = que.front(), que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!check(nx, ny)) {
                //cout << nx << " " << ny << endl;
                return false;
            }
            if (visit[nx][ny] || reach[nx][ny]) continue;
            reach[nx][ny] = true;
            que.push(nx);
            que.push(ny);
        }
    }
    return true;
}

int ans;
int n;
void dfs(int x, int y, int dep) {
    if (dep >= ans) return;
    if (bfs(x, y)) {
        ans = min(ans, dep);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (visit[nx][ny]) continue;
        visit[nx][ny] = true;
        dfs(nx, ny, dep + 1);
        visit[nx][ny] = false;
    }
}

int main() {
    dir['N'] = 0;
    dir['S'] = 3;
    dir['E'] = 2;
    dir['W'] = 1;
    while (scanf("%d", &n), n) {
        int sx, sy;
        memset(visit, false, sizeof(visit));
        sx = sy = 47;
        visit[sx][sy] = true;
        int a, c;
        for (int i = 0; i < n; i++) {
            char b[5];
            scanf("%d%s", &a, &b);
            //cout << a << " " << b << endl;
            c = dir[b[0]];
            for (int i = 0; i < a; i++) {
                int nx = sx + dx[c], ny = sy + dy[c];
                visit[nx][ny] = true;
                sx = nx, sy = ny;
                //cout << sx << " " << sy << endl;
            }
        }
        if (bfs(sx, sy)) {
            puts("0");
            continue;
        }
        int sum = 0;
        while (1) {
            int t = 0;
            int id = -1;
            for (int i = 0; i < 4; i++) {
                int nx = sx + dx[i], ny = sy + dy[i];
                if (!visit[nx][ny]) t++, id = i;
            }
            if (t == 1) {
                sum++;
                sx += dx[id], sy += dy[id];
                visit[sx][sy] = true;
            } else break;
        }
        ans = 6;
        dfs(sx, sy, 0);
        cout << sum + ans << endl;
    }
    return 0;
}
