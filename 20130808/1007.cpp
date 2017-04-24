#pragma comment(linker, "/STACK:10006777216")
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

const int N = 1111111;
const ll MOD = 1000000007LL;
ll fac[N], inv_fac[N];
ll dp[N];
int eh[N], tot;
struct Edge {
    int v, next;
} et[N << 1];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll power_mod(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        b >>= 1;
        a = mul(a, a);
    }
    return res;
}

ll com(int a, int b) {
    if (b == 0) return 1;
    return mul(fac[a], mul(inv_fac[b], inv_fac[a - b]));
}

ll inv_com(int a, int b) {
    if (b == 0) return 1;
    return mul(inv_fac[a], mul(fac[b], fac[a - b]));
}

int cnt[N];
int n;
ll ans;
void dfs_down(int u, int pre) {
    cnt[u] = 0;
    dp[u] = 1;
    for (int i = eh[u]; ~i; i = et[i].next) {
        int v = et[i].v;
        if (v == pre) continue;
        dfs_down(v, u);
        cnt[u] += cnt[v];
        dp[u] = mul(dp[u], mul(com(cnt[u], cnt[v]), dp[v]));
    }
    cnt[u]++;
}

void dfs_up(int u, int pre, ll t) {
    ll w = mul(t, com(n - 1, n - cnt[u]));
    ans = (ans + mul(w, w)) % MOD;
    for (int i = eh[u]; ~i; i = et[i].next) {
        int v = et[i].v;
        if (v == pre) continue;
        dfs_up(v, u, mul(w, inv_com(n - 1, cnt[v])));
    }
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = mul(fac[i - 1], i);
    }
    for (int i = 0; i < N; i++) {
        inv_fac[i] = power_mod(fac[i], MOD - 2);
    }
    int T;
    cin >> T;
    while (T--) {
        scanf("%d", &n);
        init();
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        ans = 0;
        dfs_down(1, 0);
        dfs_up(1, 0, dp[1]);
        printf("%I64d\n", ans);
    }
    return 0;
}
