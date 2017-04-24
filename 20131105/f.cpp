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

const int N = 66666;
struct Point {
    int x, y, z;
    void read() {
        scanf("%d%d%d", &x, &y, &z);
    }
    bool operator < (const Point &a) const {
        return y < a.y;
    }
} point[N];

struct SegTree {
    int a[N << 2];
    void pushup(int p) { a[p] = max(a[p << 1], a[p << 1 | 1]); }
    void update(int p, int l, int r, int x, int v) {
        if (l == r) {
            a[p] = v;
            return;
        }
        int mid = l + r >> 1;
        if (x <= mid) update(p << 1, l, mid, x, v);
        else update(p << 1 | 1, mid + 1, r, x, v);
        pushup(p);
    }
    int query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return a[p];
        int mid = l + r >> 1;
        int ret = -inf;
        if (L <= mid) ret = max(ret, query(p << 1, l, mid, L, R));
        if (mid < R) ret = max(ret, query(p << 1 | 1, mid + 1, r, L, R));
        return ret;
    }
} lst, rst;

int main() {
    int w, s, n, a, b, c;
    while (~scanf("%d%d%d%d%d%d", &w, &s, &n, &a, &b, &c)) {
        for (int i = 0; i < n; i++) point[i].read();
        sort(point, point + n);
        for (int i = 0; i < w; i++) {
            lst.update(1, 0, w - 1, i, i * a);
            rst.update(1, 0, w - 1, i, -(i * a));
        }
        int pos = 0;
        while (pos < n) {
            map<int, int> mp;
            int y = point[pos].y;
            while (pos < n && point[pos].y == y) {
                int x = point[pos].x, z = point[pos].z;
                mp[x] = z;
                if (z < 0) {
                    if (x - 1 >= 0) mp[x - 1];
                    if (x + 1 < w) mp[x + 1];
                }
                pos++;
            }
            for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
                it->second += max(lst.query(1, 0, w - 1, 0, it->first) - it->first * a, rst.query(1, 0, w - 1, it->first, w - 1) + it->first * a);
            }
            for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
                lst.update(1, 0, w - 1, it->first, it->second + it->first * a);
                rst.update(1, 0, w - 1, it->first, it->second - it->first * a);
            }
        }
        int ans = -inf;
        for (int i = 0; i < w; i++) {
            ans = max(ans, lst.query(1, 0, w - 1, i, i) - i * a);
            ans = max(ans, rst.query(1, 0, w - 1, i, i) + i * a);
        }
        ans += b + c;
        printf("%d\n", ans);
    }
    return 0;
}
