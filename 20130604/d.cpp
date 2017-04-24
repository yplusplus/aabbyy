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

const int N = 11111;
const int M = 111111;
int n, m;
int fa[N];
int ans[M];
pii edge[M];

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
        for (int i = 0; i < n; i++) fa[i] = i;
        int cc = n;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &edge[i].fi, &edge[i].se);
        }
        for (int i = m - 1; i >= 0; i--) {
            ans[i] = cc;
            cc -= Union(edge[i].fi, edge[i].se);
        }
        for (int i = 0; i < m; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
