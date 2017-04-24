#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

const int INF = 1 << 20;
const int N = 666; 
int eh[N], tot;
int n, m;
vector<int> items[N];
int s, t, ss, st;
int dist[N], cur[N];

struct Edge {
    int v, cap, flow, next;
    Edge() {}
    Edge(int v, int cap, int flow, int next) : v(v), cap(cap), flow(flow), next(next) {}
} et[N * N];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
    et[tot] = Edge(v, cap, flow, eh[u]);
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}

void myaddedge(int u, int v, int l, int r) {
    addedge(ss, v, l);
    addedge(u, st, l);
    addedge(u, v, r - l);
}

bool bfs(int s, int t) {
    queue<int> que;
    que.push(s);
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (et[i].cap > et[i].flow && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int u, int t, int d) {
    if (u == t) return d;
    int l = d;
    for (int &i = cur[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
            int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
            et[i].flow += tmp;
            et[i ^ 1].flow -= tmp;
            l -= tmp;
            if (l == 0) break;
        }
    }
    return d - l;
}

int Dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(cur));
        flow += dfs(s, t, INF);
    }
    return flow;
}

int cnt[N], g[N][N];
void solve() {
    s = n + m;
    t = n + m + 1;
    ss = n + m + 2;
    st = n + m + 3;
    memset(cnt, 0, sizeof(cnt));
    memset(g, 0, sizeof(g));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < items[i].size(); j++) {
            int x = items[i][j];
            cnt[abs(x) - 1]++;
            g[abs(x) - 1][i] = x;
        }
    }
    init();
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 2) {
            myaddedge(s, i, 1, 1);
        } else {
            myaddedge(s, i, 0, 1);
        }
    }
    for (int i = 0; i < m; i++) {
        myaddedge(n + i, t, 1, 1);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != 0) {
                myaddedge(i, j + n, 0, 1);
            }
        }
    }
    myaddedge(t, s, 0, INF);
    Dinic(ss, st);
    bool valid = true;
    for (int i = eh[ss]; i != -1; i = et[i].next) {
        if (et[i].cap > et[i].flow) {
            valid = false;
            break;
        }
    }
    if (valid) {
        int ans[N] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = eh[i]; j != -1; j = et[j].next) {
                int v = et[j].v;
                if (v >= n && v < n + m) {
                    ans[i] = (et[j].flow > 0) ^ (g[i][v - n] < 0);
                } 
            }
        }
        puts("YES");
        for (int i = 0; i < n; i++) {
            printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
        }
    } else {
        puts("NO");
    }
}

int main() {
    freopen("sat.in", "r", stdin);
    freopen("sat.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0, k; i < m; i++) {
        scanf("%d", &k);
        items[i].resize(k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &items[i][j]);
        }
    }
    solve();
    return 0;
}
