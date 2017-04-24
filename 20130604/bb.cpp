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
const int N = 555;
int ans, anscost , eh[N], tot, low[N], p[N], dist[N];
int S, T;
int n, m;
int need[N][10];
bool maz[N][N];
struct Point {
    int x, y, b, p;
    Point(){}
    Point(int _x, int _y, int _b, int _p) {
        x = _x, y = _y, b = _b, p = _p;
    }
}point[N];


ll getDist(Point &a, Point &b) {
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

struct Edge {
    int u, v, cost, cap, flow, next;
} et[N * N];
bool visit[N];
bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    for (int i = 0; i < N; i++) dist[i] = inf;
    visit[S] = true, low[S] = inf, dist[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                p[v] = i;
                low[v] = min(low[u], cap - flow);
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[T] != inf;
}

void costflow() {
    ans = 0, anscost = 0;
    while (spfa()) {
        int x = p[T];
        ans += low[T];
        anscost += low[T] * dist[T];
        while (x != -1) {
            et[x].flow += low[T];
            et[x^1].flow -= low[T];
            et[x^1].cost = -et[x].cost;
            x = p[et[x].u];
        }
    }
}
void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}
void init() {
    tot = 0;
    memset(eh, -1, sizeof (eh));
}

int main() {
    int TT;
    scanf("%d", &TT);
    while (TT--) {
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
        int finalAns = 0;
        for (int i = 0; i < m; i++) {
            init();
            S = 0, T = 2 * n + 2;
            addedge(S, T - 1, 0, inf);
            for (int j = 1; j < n; j++) {
                addedge(S, j, -1, need[j][i]);
                if (maz[0][j]) addedge(T - 1, j + n, 0, inf);
                addedge(j + n, T, 1, need[j][i]);
                for (int k = 1; k < n; k++) {
                    if (maz[j][k] && j != k) addedge(j, k + n, 0, inf);
                }
            }
            costflow();
            finalAns += anscost;
        }
        cout << finalAns << endl;
    }
    return 0;
}
