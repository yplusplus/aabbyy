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

const int N = 222;
vector<pii> vec;
int n, m;
struct Point {
    ll x, y;
    void read() {
        cin >> x >> y;
    }
} p[N];
inline int sig(ll k) {
    return k < 0 ? -1 : k > 0;
}
inline ll dotdet(ll x1, ll y1, ll x2, ll y2) {
    return x1 * x2 + y1 * y2;
}
inline ll dot(Point a , Point b , Point c ) {
    return dotdet( b .x - a .x, b .y - a .y, c .x - a .x, c .y - a .y);
}
inline ll det(ll x1, ll y1, ll x2, ll y2) {
    return x1 * y2 - x2 * y1;
}
inline ll xmult(Point a , Point b , Point c ) {
    return det(b .x - a .x, b .y - a .y, c .x - a .x, c .y - a .y);
}
inline int between(Point a , Point b , Point c ) {
    return sig(dot( a , b , c ));
}
inline int intersect(Point a, Point b, Point c, Point d) {
    int d1 = sig(xmult(a, b, c));
    int d2 = sig(xmult(a, b, d));
    int d3 = sig(xmult(c, d, a));
    int d4 = sig(xmult(c, d, b));
    if ((d1^d2) == -2 && (d3^d4) == -2) return 1;
    if (d1 == 0 && between(c, a, b) <= 0) return 2;
    if (d2 == 0 && between(d, a, b) <= 0) return 2;
    if (d3 == 0 && between(a, c, d) <= 0) return 2;
    if (d4 == 0 && between(b, c, d) <= 0) return 2;
    return 0;
}

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

int main() {
    while (cin >> n >> m) {
        vec.clear();
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            p[i].read();
        }
        int x = n;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            x -= Union(a, b);
            vec.pb(mp(a, b));
            for (int j = 1; j <= n; j++) {
                if (sig(xmult(p[a], p[b], p[j])) == 0 && between(p[j], p[a], p[b]) <= 0) {
                    x -= Union(j, b);
                }
            }
            for (int j = 0; j < i; j++) {
                int c = vec[j].fi, d = vec[j].se;
                if (intersect(p[a], p[b], p[c], p[d]) > 0) {
                    x -= Union(a, c);
                }
            }
        }
        puts(1 == x ? "YES" : "NO");
    }
    return 0;
}
