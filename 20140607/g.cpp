#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const double DBL_MAX = 1e15;
const int N = 444;
double dist[N];
double g[N][N];
bool visit[N];
int belong[N];
int holes[N];
int n, m;
int colors;
vector<int> vec[N];

inline double sq(double x) { return x * x; }

struct Point {
    int x, y, z;
    int holes;
    void read() {
        scanf("%d%d%d%d", &x, &y, &z, &holes);
    }
    double distanceFrom(const Point &o) {
        return sqrt(sq(x - o.x) + sq(y - o.y) + sq(z - o.z));
    }
} point[N];

void dfs(int u, int maxZ) {
    belong[u] = colors;
    holes[colors] += point[u].holes;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!belong[v] && point[v].z <= maxZ) dfs(v, maxZ);
    }
}

double calc(int maxZ) {
    memset(belong, 0, sizeof(belong));
    memset(holes, 0, sizeof(holes));
    colors = 0;
    for (int i = 1; i <= n; i++) {
        if (!belong[i] && point[i].z <= maxZ) {
            ++colors;
            dfs(i, maxZ);
        }
    }
    if (belong[1] == belong[n]) { return holes[belong[1]] / 2.0; }
    if (holes[belong[1]] == 0 || holes[belong[n]] == 0) return DBL_MAX;

    //cout << maxZ << " " << colors << endl;
    //cout << holes[belong[1]] << " " << holes[belong[n]] << endl;

    for (int i = 1; i <= colors; i++) {
        for (int j = 1; j <= colors; j++) {
            g[i][j] = DBL_MAX;
        }
    }
    vector<int> bag;
    for (int i = 1; i <= n; i++) {
        if (belong[i] && point[i].holes) bag.push_back(i);
    }
    for (int i = 0; i < bag.size(); i++) {
        for (int j = i + 1; j < bag.size(); j++) {
            int u = bag[i], v = bag[j];
            if (belong[u] == belong[v]) continue;
            g[belong[u]][belong[v]] = min(g[belong[u]][belong[v]], point[u].distanceFrom(point[v]));
            g[belong[v]][belong[u]] = g[belong[u]][belong[v]];
        }
    }
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= colors; i++) {
        dist[i] = DBL_MAX;
    }
    dist[belong[1]] = holes[belong[1]] / 2.0;
    //cout << g[belong[1]][belong[n]] << endl;
    priority_queue<pair<double, int > > que;
    que.push(make_pair(-dist[belong[1]], belong[1]));
    while (!que.empty()) {
        int u = que.top().second;
        double val = -que.top().first;
        que.pop();
        if (visit[u]) continue;
        visit[u] = true;
        for (int i = 1; i <= colors; i++) {
            if (visit[i]) continue;
            if (i != belong[n] && holes[i] < 2) continue;
            double cost = val - 0.5 + g[u][i] + (holes[i] - 1) / 2.0;
            if (dist[i] > cost) {
                dist[i] = cost;
                que.push(make_pair(-dist[i], i));
            }
        }
    }
    return dist[belong[n]];
}

void solve() {
    int maxZ = max(point[1].z, point[n].z);
    double ans = DBL_MAX;
    for (int i = 1; i <= n; i++) {
        if (point[i].z >= maxZ) {
            ans = min(ans, calc(point[i].z));
        }
    }
    if (ans == DBL_MAX) {
        puts("impossible");
    } else {
        printf("%.4f\n", ans);
    }
}

int main() {
    int Case = 1;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) { point[i].read(); }
        for (int i = 1; i <= n; i++) { vec[i].clear(); }
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
