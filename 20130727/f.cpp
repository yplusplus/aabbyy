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

const int N = 666;
int fa[N * N];
char maz[N][N];
bool dir[N][N][4];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void init() {
    for (int i = 0; i < N * N; i++) fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

int n;
int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i < 2 * n; i++) {
            scanf("%s", &maz[i][1]);
        }
        init();
        memset(dir, true, sizeof(dir));
        int m = 2 * n + 1;
        int cnt = 2 * n * m;
        for (int i = 1; i < 2 * n; i++) {
            for (int j = 1; j <= n; j++) {
                int x = i, y = 2 * j - (i & 1), nx, ny;
                if (maz[i][j] == 'H') {
                    nx = x + 1, ny = y;
                    dir[x][y][1] = dir[nx][ny][0] = false;
                    dir[x][y + 1][1] = dir[nx][ny + 1][0] = false;
                } else {
                    nx = x, ny = y + 1;
                    dir[x][y][3] = dir[nx][ny][2] = false;
                    dir[x + 1][y][3] = dir[nx + 1][ny][2] = false;
                }
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j <= m; j++) {
                if (i + 1 < m && dir[i][j][1]) cnt -= Union((i - 1) * m + j, i * m + j);
                if (j + 1 <= m && dir[i][j][3]) cnt -= Union((i - 1) * m + j, (i - 1) * m + j + 1);
            }
        }
        cout << cnt - 1 << endl;
    }
    return 0;
}
