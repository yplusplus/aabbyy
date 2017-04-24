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

const int N = 444;
const int M = 555555;
int need[N][10];
int eh[N], tot;
int dist[N], cur[N], que[N];
int s, t;
int ss, tt;
int n, m;
bool maz[N][N];
struct Point {
    int x, y, b, p;
    Point(){}
    Point(int _x, int _y, int _b, int _p) {
        x = _x, y = _y, b = _b, p = _p;
    }
}point[N];

struct Edge {
    int v, cap, flow, next;
}et[M];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}
void add(int u, int v, int cap, int flow) {
    Edge e = {v, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}
bool bfs() {
    int head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[tt] = 0;
    que[tail++] = tt;
    while(head < tail && dist[ss] == -1) {
        int u = que[head++];
        for(int i = eh[u]; i != -1; i = et[i].next) {
            if(et[i^1].cap > et[i^1].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[ss] != -1;
}
int dfs(int u, int d) {
    if(u == tt) return d;
    int l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {
        if(et[i].cap > et[i].flow && dist[et[i].v] + 1 == dist[u]) {
            int tmp = dfs(et[i].v, min(l, et[i].cap - et[i].flow));
            l -= tmp;
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}
int Dinic() {
    int flow = 0;
    while(bfs()) {
        for(int i = 0; i < N; i++) cur[i] = eh[i];
        flow += dfs(ss, inf);
    }
    return flow;
}

int in[N], out[N];
struct EE {
    int u, v, low, high;
    EE(){}
    EE(int _u, int _v, int _low, int _high) {
        u = _u, v = _v, low = _low, high = _high;
    }
}ee[M];

int eet;
bool check(int mid) {
    ee[eet] = EE(t, s, 0, mid);
    int sum = 0;
    init();
    for (int i = 0; i <= eet; i++) {
        addedge(ee[i].u, ee[i].v, ee[i].high - ee[i].low);
    }
    for (int i = s; i <= t; i++) {
        int delta = in[i] - out[i];
        if (delta == 0) continue;
        if (delta > 0) {
            sum += delta;
            addedge(ss, i, delta);
        } else {
            addedge(i, tt, -delta);
        }
    }
    int res = Dinic();
    return res == sum;
}

int solve(int id) {
    s = 0, t = 2 * n;
    ss = t + 1, tt = ss + 1;
    eet = 0;
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 1; i < n; i++) {
        if (maz[0][i]) {
            ee[eet++] = EE(s, i, 0, inf);
        }
        ee[eet++] = EE(i, i + n, need[i][id], inf);
        ee[eet++] = EE(i + n, t, 0, inf);
        for (int j = 1; j < n; j++) {
            if (maz[i][j]) {
                ee[eet++] = EE(i + n, j, 0, inf);
            }
        }
    }
    for (int i = 0; i < eet; i++) {
        out[ee[i].u] += ee[i].low;
        in[ee[i].v] += ee[i].low;
    }
    int l = 0, r = 2222, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, res = mid;
        else l = mid + 1;
    }
    return res;
}

ll getDist(Point &a, Point &b) {
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        scanf("%d%d", &point[0].x, &point[0].y);
        for (int i = 1; i < n; i++) {
            scanf("%d%d%d%d", &point[i].x, &point[i].y, &point[i].b, &point[i].p);
            for (int j = 0; j < m; j++) {
                scanf("%d", &need[i][j]);
            }
        }
        memset(maz, false, sizeof(maz));
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (i != j) {
                    ll delta = point[j].b - (point[i].b + point[i].p);
                    if (delta < 0) continue;
                    maz[i][j] = (getDist(point[i], point[j]) <= delta * delta);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < m; i++) {
            ans += solve(i);
        }
        cout << ans << endl;
    }
    return 0;
}
