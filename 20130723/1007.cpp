#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
const double eps = 1e-10;
const int N = 333;
const int M = 111;
int n, m, p;
double dis[N][N];
struct Point {//点
    double x, y;
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    Point() {}
    Point(double a, double b) {
        x = a, y = b;
    }
} city[N];
struct Line {//线
    Point a, b;
    Line() {}
    Line(Point x, Point y) {
        a = x, b = y;
    }
} seg[M];
inline int sig(double k) {
    return k < -eps ? -1 : k > eps;
}
inline double det(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}
inline double xmult(Point a, Point b, Point c) {
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}
inline double dotdet(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}
inline double dot(Point a, Point b, Point c) {
    return dotdet(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}
inline int between(Point a, Point b, Point c) {
    return sig(dot(a, b, c));
}
inline int intersect(Point a, Point b, Point c, Point d, Point &p) {
    double s1, s2, s3, s4;
    int d1 = sig(s1 = xmult(a, b, c));
    int d2 = sig(s2 = xmult(a, b, d));
    int d3 = sig(s3 = xmult(c, d, a));
    int d4 = sig(s4 = xmult(c, d, b));
    if ((d1^d2) == -2 && (d3^d4) == -2) {
        p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
        p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
        return 1;
    }
    if (d1 == 0 && between(c, a, b) <= 0) return 2;
    if (d2 == 0 && between(d, a, b) <= 0) return 2;
    if (d3 == 0 && between(a, c, d) <= 0) return 2;
    if (d4 == 0 && between(b, c, d) <= 0) return 2;
    return 0;
}
inline int intersect(Line u, Line v, Point &p) {
    return intersect(u.a, u.b, v.a, v.b, p);
}
bool operator==(const Point &x, const Point &y) {
    return sig(x.x - y.x) == 0 && sig(x.y - y.y) == 0;
}
inline double getDist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int dist[N], cur[N], eh[N], tot;
int s, t;
int que[N];
struct Edge {
    int u, v, cap, flow, next;
} et[99999];
void add(int u, int v, int cap, int flow) {
    Edge e = {u, v, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs() {
    int head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[t] = 0;
    que[tail++] = t;
    while(head < tail && dist[s] == -1) {
        int u = que[head++];
        for(int i = eh[u]; i != -1; i = et[i].next) {
            if(et[i^1].cap > et[i^1].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[s] != -1;
}
int dfs(int u, int d) {
    if(u == t) return d;
    int l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {//当前弧优化
        if(et[i].cap > et[i].flow && dist[u] == dist[et[i].v] + 1) {
            int tmp = dfs(et[i].v, min(et[i].cap - et[i].flow, l)); 
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            l -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}
int Dinic() {
    int flow = 0;
    while(bfs()) {
        for(int i = 0; i < 2 * n + 10; i++) cur[i] = eh[i];
        flow += dfs(s, 1 << 20);
    }
    return flow;
}

const double dlinf = 1e40;
bool visit[N];
double dd[N];
void spfa(int s) {
    int all = n + m * 2;
    queue<int> que;
    for (int i = 1; i <= all; i++) {
        dd[i] = 1e50;
        visit[i] = false;
    }
    dd[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = 1; i <= all; i++) {
            if (i == u) continue;
            if (dd[i] > dd[u] + dis[u][i]) {
                dd[i] = dd[u] + dis[u][i];
                if (!visit[i]) {
                    que.push(i);
                    visit[i] = true;
                }
            }
        }
    }
    for (int i = 1; i <= all; i++) {
        dis[s][i] = dd[i];
    }
}

void init() {
    int all = n + m * 2;
    for (int i = 1; i <= all; i++) {
        dis[i][i] = 0;
        for (int j = i + 1; j <= all; j++) {
            Point e;
            bool found = false;
            for (int k = 1; k <= m; k++) {
                if (intersect(Line(city[i], city[j]), seg[k], e) == 1) {
                    found = true;
                    break;
                }
            }
            if (found) dis[i][j] = dis[j][i] = 1e50;
            else dis[i][j] = dis[j][i] = getDist(city[i], city[j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        spfa(i);
    }
}

int cc[N];
void build(double mid) {
    s = 0, t = 2 * n + 1;
    int tt = t + 1;
    tot = 0;
    memset(eh, -1, sizeof(eh));
    addedge(s, tt, p);
    for (int i = 1; i <= n; i++) {
        int u = cc[i];
        addedge(s, u, 1);
        addedge(tt, u + n, 1);
        addedge(u + n, t, 1);
        for (int j = i + 1; j <= n; j++) {
            int v = cc[j];
            if (dis[u][v] < mid) {
                addedge(u, v + n, 1);
            }
        }
    }
}

void solve() {
    init();
    double l = 0.0, r = 1e30;
    double ans = 1e30;
    for (int i = 0; i < 200; i++) {
        double mid = (l + r) / 2.0;
        build(mid);
        if (Dinic() == n) {
            ans = mid;
            r = mid;
        } else l = mid;
    }    
    printf("%.2f\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &p);
        for (int i = 1; i <= n; i++) {
            city[i].read();
        }
        for (int i = 1; i <= m; i++) {
            int b = n + i * 2;
            int a = b - 1;
            city[a].read();
            city[b].read();
            seg[i] = Line(city[a], city[b]);
        }
        for (int i = 1; i <= n; i++) scanf("%d", &cc[i]);
        solve();
    }
    return 0;
}

