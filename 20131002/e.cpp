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
#include <cassert>
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
const double dinf = 1e31;
const ll linf = 1LL << 55;

const int N = 111111;
int n, m;
struct SegmentTree {
    int sum[N << 2], rev[N << 2];
    void clear() {
        memset(sum, 0, sizeof(sum));
        memset(rev, 0, sizeof(rev));
    }
    void pushup(int p) { sum[p] = sum[p << 1] + sum[p << 1 | 1]; }
    void pushdown(int p, int l, int r) {
        if (rev[p]) {
            int mid = l + r >> 1;
            sum[p << 1] = (mid - l + 1) - sum[p << 1];
            sum[p << 1 | 1] = (r - mid) - sum[p << 1 | 1];
            rev[p << 1] ^= 1;
            rev[p << 1 | 1] ^= 1;
            rev[p] = 0;
        }
    }
    void update(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            sum[p] = (r - l + 1) - sum[p];
            rev[p] ^= 1;
            return;
        }
        pushdown(p, l, r);
        int mid = l + r >> 1;
        if (L <= mid) update(p << 1, l, mid, L, R);
        if (R > mid) update(p << 1 | 1, mid + 1, r, L, R);
        pushup(p);
    }
    int query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return sum[p];
        }
        pushdown(p, l, r);
        int mid = l + r >> 1;
        int res = 0;
        if (L <= mid) res += query(p << 1, l, mid, L, R);
        if (R > mid) res += query(p << 1 | 1, mid + 1, r, L, R);
        return res;
    }
} T[32];

vector<int> g[N];
vector<int> vec[N];
unsigned val[N];
int st[N], ed[N], Dindex, dep[N];
int id[N];
int max_depth;
void dfs(int u, int depth) {
    max_depth = max(max_depth, depth);
    st[u] = ++Dindex;
    dep[u] = depth;
    vec[depth].pb(Dindex);
    for (int i = 0; i < g[u].size(); i++) {
        dfs(g[u][i], depth + 1);
    }
    ed[u] = Dindex;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        assert(n > 0 && n <= 100000);
        for (int i = 0; i <= n; i++) g[i].clear(), vec[i].clear();
        for (int i = 1; i <= n; i++) {
            int father;
            scanf("%d%u", &father, &val[i]);
            assert(father >= 0 && father <= n);
            assert(val[i] > 0 && val[i] < 1000000000);
            g[father].pb(i);
        }
        max_depth = Dindex = 0;
        dfs(0, 0);
        for (int i = 0; i <= 31; i++) T[i].clear();
        Dindex = 0;
        for (int i = 0; i <= max_depth; i++) {
            for (int j = 0; j < vec[i].size(); j++) {
                id[vec[i][j]] = ++Dindex;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= 31; j++) {
                if (val[i] >> j & 1) T[j].update(1, 1, n + 1, id[st[i]], id[st[i]]);
            }
        }

        int a, b, c;
        unsigned v = 0;
        while (m--) {
            scanf("%d%d%d", &a, &b, &c);
            assert(a >= 0 && a <= 1);
            assert(b >= 0 && b <= n);
            assert(c > 0 && c < 1000000000);
            if (!a) scanf("%u", &v);
            assert(v >= 0 && v < 1000000000);
            int d = dep[b] + c;
            if (d > max_depth) {
                if (a) puts("-1");
                continue;
            }
            int L = -1, R = -1, l, r;
            l = 0, r = vec[d].size() - 1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (vec[d][mid] >= st[b]) {
                    L = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
            l = 0, r = vec[d].size() - 1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (vec[d][mid] <= ed[b]) {
                    R = mid;
                    l = mid + 1;
                } else r = mid - 1;
            }
            if (L == -1 || R == -1 || L > R) {
                if (a) puts("-1");
                continue;
            }
            L = id[vec[d][L]];
            R = id[vec[d][R]];
            if (a) {
                ll ans = 0;
                for (int i = 0; i <= 31; i++) {
                    ans += (1LL << i) * T[i].query(1, 1, n + 1, L, R);
                }
                printf("%lld\n", ans);
            } else {
                for (int i = 0; i <= 31; i++) {
                    if (v >> i & 1) T[i].update(1, 1, n + 1, L, R);
                }
            }
        }
    }
    return 0;
}
