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
const int N = 7;
bool canPut[N][N];
bool put[N][N];
int n, m, q;
int ans;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool inside(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool checkRow(int i) {
    for (int j = 0; j < m; j++) {
        if (put[i][j]) {
            for (int k = 0; k < 2; k++) {
                int x = i + dx[k], y = j + dy[k];
                int cnt = 0;
                while (inside(x, y) && cnt <= 1) {
                    if (cnt == 1 && put[x][y]) return false;
                    cnt += (put[x][y] | !canPut[x][y]);
                    x += dx[k], y += dy[k];
                }
            }
        }
    }
    return true;
}

bool checkCol(int j) {
    for (int i = 0; i < n; i++) {
        if (put[i][j]) {
            for (int k = 2; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                int cnt = 0;
                while (inside(x, y) && cnt <= 1) {
                    if (cnt == 1 && put[x][y]) return false;
                    cnt += (put[x][y] | !canPut[x][y]);
                    x += dx[k], y += dy[k];
                }
            }
        }
    }
    return true;
}

void dfs(int x, int y, int cnt) {
    if (y == m) x++, y = 0;
    if (y == 0) {
        if (x && !checkRow(x - 1)) return;
    }
    if (x == n) {
        for (int j = 0; j < m; j++) {
            if (!checkCol(j)) return;
        }
        ans = max(ans, cnt);
        return;
    }
    dfs(x, y + 1, cnt);
    if (canPut[x][y]) {
        put[x][y] = true;
        dfs(x, y + 1, cnt + 1);
        put[x][y] = false;
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &q)) {
        memset(canPut, true, sizeof(canPut));
        memset(put, false, sizeof(put));
        for (int i = 0; i < q; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            canPut[x][y] = false;
        }
        ans = 0;
        dfs(0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
