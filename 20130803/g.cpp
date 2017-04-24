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

const int M = 30;
const int N = 11;
set<pii> edge, e;
int n, m;
int fa[10];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

int dist(const pii &a, const pii &b) {
    return abs(a.fi - b.fi) + abs(a.se - b.se);
}

int getmid(const pii &a, const pii &b) {
    int c = (a.fi + b.fi) >> 1;
    int d = (a.se + b.se) >> 1;
    return c * 3 + d;
}


bool add(const pii &x) {
    if (edge.find(x) == edge.end()) return false;
    e.insert(x);
    return true;
}

bool handle(int u, int v, int mask) {
        if (u > v) swap(u, v);
        pii upos = mp(u / 3, u % 3);
        pii vpos = mp(v / 3, v % 3);
        int d = dist(upos, vpos);
        if (d == 1 || d == 3) {
            if (!add(mp(u, v))) return false;
        } else if (d == 4) {
            if (~mask >> 4 & 1) return false;
            if (!add(mp(min(u, 4), max(u, 4)))) return false;
            if (!add(mp(min(v, 4), max(v, 4)))) return false;
        } else {
            if (upos.fi == vpos.fi || upos.se == vpos.se) {
                int mid = getmid(upos, vpos);
                if (~mask >> mid & 1) return false;
                if (!add(mp(min(u, mid), max(u, mid)))) return false;
                if (!add(mp(min(v, mid), max(v, mid)))) return false;
            } else {
                if (!add(mp(u, v))) return false;
            }
        }
        return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d", &m);
        vector<int> vec, ans;
        edge.clear();
        for (int i = 0; i < 10; i++) fa[i] = i;
        for (int i = 0, a, b; i < m; i++) {
            scanf("%d%d", &a, &b);
            if (a > b) swap(a, b);
            a--, b--;
            edge.insert(mp(a, b));
            vec.pb(a);
            vec.pb(b);
            Union(a, b);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        int sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            int v = vec[i];
            if (fa[v] == v) sum++;
        }
        if (sum > 1) {
            puts("IMPOSSIBLE");
            continue;
        }
        n = vec.size();
        int a[10];
        for (int i = 0; i < n; i++) a[i] = i;
        do {
            int mask = 0;
            e.clear();
            bool found = true;
            for (int i = 0; i < n - 1 && found; i++) {
                int u = vec[a[i]], v = vec[a[i + 1]];
                found = handle(u, v, mask);
                mask |= (1 << u);
                mask |= (1 << v);
            }
            if (!found || edge.size() != e.size()) continue;
            for (int i = 0; i < n; i++) {
                ans.pb(vec[a[i]] + 1);
            }
            break;
        } while (next_permutation(a, a + n));
        if (ans.size() == 0) {
            puts("IMPOSSIBLE");
        } else {
            for (int i = 0; i < n; i++) {
                printf("%d ", ans[i]);
            }
            puts("");
        }
    }
    return 0;
}
