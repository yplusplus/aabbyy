#pragma comment(linker,"/STACK:102400000,102400000")
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

const int MOD = 1000003;
const int N = 111111;
int val[N];
int inv[MOD];
int n, k;
vector<int> vec[N];
bool visit[N];
int rec[MOD];

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int power_mod(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        b >>= 1;
        a = mul(a, a);
    }
    return res;
}

int son[N], dp[N];
int que[N], cc;
void dfs_center(int u, int fa) {
    que[cc++] = u;
    son[u] = 1;
    dp[u] = 0;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (visit[v] || fa == v) continue;
        dfs_center(v, u);
        son[u] += son[v];
        dp[u] = max(dp[u], son[v]);
    }
}

int calc_center(int u) {
    cc = 0;
    dfs_center(u, 0);
    int id = -1, record = n + 1;
    for (int i = 0; i < cc; i++) {
        u = que[i];
        dp[u] = max(dp[u], cc - son[u]);
        if (id == -1 || record > dp[u]) id = u, record = dp[u];
    }
    return id;
}

pair<int, int> q[N];
void dfs2(int u, int fa, int w) {
    w = (1LL * w * val[u]) % MOD;
    q[cc++] = make_pair(u, w);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa || visit[v]) continue;
        dfs2(v, u, w);
    }
}

pair<int, int> ans;
void update(int a, int b) {
    if (a > b) swap(a, b);
    ans = min(ans, make_pair(a, b));
}

void dfs(int u) {
    u = calc_center(u);
    visit[u] = true;
    vector<int> vv;
    rec[val[u]] = u;
    vv.push_back(val[u]);
    int x, y;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            cc = 0;
            dfs2(v, u, 1);
            for (int i = 0; i < cc; i++) {
                x = q[i].first, y = q[i].second;
                int z = rec[1LL * inv[y] * k % MOD];
                if (z != -1) update(x, z);
            }
            for (int i = 0; i < cc; i++) {
                x = q[i].first, y = 1LL * q[i].second * val[u] % MOD;
                if (rec[y] == -1 || rec[y] > x) rec[y] = x;
                vv.push_back(y);
            }
        }
    }
    for (int i = 0; i < vv.size(); i++) { rec[vv[i]] = -1; }

    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            dfs(v);
        }
    }
}

int main() {
    for (int i = 1; i < MOD; i++) inv[i] = power_mod(i, MOD - 2);
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            val[i] %= MOD;
            vec[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        memset(visit, false, sizeof(visit));
        memset(rec, -1, sizeof(rec));
        ans = make_pair(n + 1, n + 1);
        if (k) dfs(1);
        if (ans.first == n + 1) puts("No solution");
        else printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}
