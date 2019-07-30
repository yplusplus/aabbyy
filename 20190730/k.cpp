#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

const int M = 1000 * 300 * 2 * 100;
const int N = 300 * 300 + 30;

inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

int n, m, k;
int eh[N], tot;
int dist[N];
int cur[N];
struct Edge {
    int u, v, cap, next;
} et[M];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void add(int u, int v, int cap) {
    Edge e = {u, v, cap, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    //cout << u << " " << v << " " << cap << endl;
    add(u, v, cap); add(v, u, 0);
}

bool bfs(int s, int t, int n) {
    for (int i = 0; i <= n; i++) {
        dist[i] = -1;
    }
    dist[t] = 0;
    queue<int> que;
    que.push(t);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = eh[u]; ~i; i = et[i].next) {
            int v = et[i].v;
            if (dist[v] == -1 && et[i^1].cap > 0) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
    return dist[s] != -1;
}

int dfs(int u, int t, int d) {
    if (u == t) return d;
    int l = d;
    for (int &i = cur[u]; ~i; i = et[i].next) {
        int v = et[i].v;
        if (dist[u] == dist[v] + 1 && et[i].cap > 0) {
            int tmp = dfs(v, t, min(et[i].cap, l));
            l -= tmp;
            et[i].cap -= tmp;
            et[i^1].cap += tmp;
            if (l == 0) break;
        }
    }
    return d - l;
}

int dinic(int s, int t, int n) {
    int flow = 0;
    while (bfs(s, t, n)) {
        //cout << s << " " << t << " " << n << endl;
        for (int i = 0; i <= n; i++) cur[i] = eh[i];
        flow += dfs(s, t, 500);
    }
    return flow;
}

inline int get_id(int u, int j) { 
    if (j > k) j -= k;
    return (u - 1) * k + j; 
}

void solve() {
    n = read();
    k = read();
    m = read();

    init();
    int s = n * k + 1, t = s + 1;
    for (int i = 0; i < m; i++) {
        int u = read();
        int v = read();
        for (int j = 1; j <= k; j++) {
            addedge(get_id(u, j), get_id(v, (j + 1)), 1);
        }
    }
    for (int i = 1; i <= k; i++) {
        addedge(s, get_id(i, i), 1);
    }
    for (int j = 1; j <= k; j++) {
        addedge(get_id(n, j), t, 500);
    }

    int ans = dinic(s, t, t);
    printf("%d\n", ans);
}

int main() {
    solve();
    return 0;
}

