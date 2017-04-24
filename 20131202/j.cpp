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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 44444;
ll a[N], b[N];
vector<int> g[2][N];
int down[2][N][2], up[2][N];
int rec[2][N][2];
int n, m;

void dfs_down(int u, int fa, int id) {
    memset(down[id][u], 0, sizeof(down[id][u]));
    memset(rec[id][u], 0, sizeof(rec[id][u]));
    for (int i = 0; i < g[id][u].size(); i++) {
        int v = g[id][u][i];
        if (v == fa) continue;
        dfs_down(v, u, id);
        int t = down[id][v][0] + 1;
        if (t >= down[id][u][0]) {
            down[id][u][1] = down[id][u][0];
            rec[id][u][1] = rec[id][u][0];
            down[id][u][0] = t;
            rec[id][u][0] = v;
        } else if (t > down[id][u][1]) {
            down[id][u][1] = t;
            rec[id][u][1] = v;
        }
    }
}

void dfs_up(int u, int fa, int id) {
    for (int i = 0; i < g[id][u].size(); i++) {
        int v = g[id][u][i];
        if (v == fa) continue;
        int t = up[id][u];
        if (rec[id][u][0] == v) t = max(t, down[id][u][1]);
        else t = max(t, down[id][u][0]);
        up[id][v] = t + 1;
        dfs_up(v, u, id);
    }
}

void solve() {
    dfs_down(1, 0, 0);
    dfs_down(1, 0, 1);
    up[0][1] = 0;
    dfs_up(1, 0, 0);
    up[1][1] = 0;
    dfs_up(1, 0, 1);
    int x = 0;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++) {
        x = max(x, down[0][i][0] + max(up[0][i], down[0][i][1]));
        a[max(down[0][i][0], up[0][i])]++;
    }
    for (int i = 1; i <= m; i++) {
        x = max(x, down[1][i][0] + max(up[1][i], down[1][i][1]));
        b[max(down[1][i][0], up[1][i])]++;
    }
    int pos = m;
    ll ans = 0;
    ll sum = 0;
    ll cnt = 0;
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        while (pos && pos + i > x) {
            pos--;
            sum += b[pos] * pos;
            cnt += b[pos];
        }
        tot += a[i] * cnt;
        ans += sum * a[i];
        ans += a[i] * cnt * (i + 1);
    }
    ans += x * (1LL * n * m - tot);
    printf("%.3f\n", ans * 1.0 / n / m);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) g[0][i].clear();
        for (int i = 1; i <= m; i++) g[1][i].clear();
        for (int i = 1; i < n; i++) { int a, b; scanf("%d%d", &a, &b); g[0][a].push_back(b); g[0][b].push_back(a); }
        for (int i = 1; i < m; i++) { int a, b; scanf("%d%d", &a, &b); g[1][a].push_back(b); g[1][b].push_back(a); }
        solve();
    }
    return 0;
}
