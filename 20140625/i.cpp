#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <assert.h>
using namespace std;

int n, D;
const int N = 111;
const int inf = 1 << 20;
int dist[N][N];
int eh[N], tot;
int pointSet[N];
int ans;

inline int sq(int x) { return x * x; }
struct Edge {
    int u, v, next;
    Edge() {}
    Edge(int u, int v, int next) : u(u), v(v), next(next) {}
} et[N * N];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v) {
    et[tot] = Edge(u, v, eh[u]);
    eh[u] = tot++;
}

struct Point {
    int x, y;
    void read() { scanf("%d%d", &x, &y); }
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    int distFrom(const Point &p) const { return sq(x - p.x) + sq(y - p.y); }
} point[N];

int dirOnSegment(const Point &a, const Point &b, const Point &c) {
    return (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y) <= 0;
}

vector<int> points[2];
int Mx[N], My[N];
int dx[N], dy[N], dis;
bool visit[N];
bool searchPath() {
    queue<int> Q;
    dis = inf;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i = 0; i < points[0].size(); i++) {
    //for (int i = 1; i <= n; ++i) {
        int u = points[0][i];
        if (Mx[u] == -1) {
            Q.push(u); dx[u] = 0;
        }
    }
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        if (dx[u] > dis) break;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (My[v] == -1) dis = dy[v];
                else {
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != inf;
}

bool dfs(int u) {
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!visit[v] && dy[v] == dx[u] + 1) {
            visit[v] = true;
            if (My[v] != -1 && dy[v] == dis) continue;
            if (My[v] == -1 || dfs(My[v])) {
                My[v] = u, Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}

int Match() {
    memset(Mx, -1, sizeof(Mx));
    memset(My, -1, sizeof(My));
    int cnt = 0;
    while(searchPath()) {
        memset(visit, false, sizeof(visit));
        for (int i = 0; i < points[0].size(); i++) {
            int u = points[0][i];
            if (Mx[u] == -1 && dfs(u)) cnt++;
        }
    }
    return cnt;
}


void dfs1(int u) {
    if (visit[u]) return;
    visit[u] = true;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!visit[v]) {
            visit[v] = true;
            assert(My[v] != -1);
            dfs1(My[v]);
        }
    }
}

void getPointSet() {
    tot = 0;
    memset(visit, false, sizeof(visit));
    for (int i = 0; i < points[0].size(); i++) {
        int u = points[0][i];
        if (Mx[u] == -1) { dfs1(u); }
    }
    for (int i = 0; i < points[0].size(); i++) {
        int u = points[0][i];
        if (visit[u]) { pointSet[++tot] = u; }
    }
    for (int i = 0; i < points[1].size(); i++) {
        int u = points[1][i];
        if (!visit[u]) { pointSet[++tot] = u; }
    }
}

int calc(int p1, int p2) {
    int d = dist[p1][p2];
    points[0].clear();
    points[1].clear();
    for (int k = 1; k <= n; k++) {
        if (k == p1 || k == p2 || dist[k][p1] > d || dist[k][p2] > d) continue;
        points[dirOnSegment(point[p1], point[p2], point[k])].push_back(k);
    }
    if (ans > 2 + points[0].size() + points[1].size()) return -1;
    init();
    for (int i = 0; i < points[0].size(); i++) {
        int u = points[0][i];
        for (int j = 0; j < points[1].size(); j++) {
            int v = points[1][j];
            if (dist[u][v] > d) {
                addedge(u, v);
            }
        }
    }
    return 2 + points[0].size() + points[1].size() - Match();
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = point[i].distFrom(point[j]);
        }
    }
    ans = 0;
    int p1 = -1, p2 = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist[i][j] > D) continue;
            int res = calc(i, j);
            if (res > ans) {
                ans = res;
                p1 = i, p2 = j;
            }
        }
    }
    if (ans == 0) {
        printf("1\n1\n");
    } else {
        printf("%d\n", ans);
        calc(p1, p2);
        getPointSet();
        pointSet[++tot] = p1;
        pointSet[++tot] = p2;
        assert(tot == ans);
        for (int i = 1; i <= tot; i++) {
            printf("%d%c", pointSet[i], i == tot ? '\n' : ' ');
        }
    }
}

int main() {
    scanf("%d%d", &n, &D);
    D *= D;
    for (int i = 1; i <= n; i++) { point[i].read(); }
    solve();
    return 0;
}

