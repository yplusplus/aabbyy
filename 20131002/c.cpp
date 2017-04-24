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

const int N = 2222;
const int M = 222222;
int n, m;
int eh[N], tot, cur[N], dist[N];
struct Edge {
    int u, v, cap, flow, next;
} et[M];
void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void add(int u, int v, int cap, int flow) {
    Edge e = {u, v, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs(int s, int t) {
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    que.push(s);
    dist[s] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = eh[u]; ~i; i = et[i].next) {
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
    for (int &i = cur[u]; ~i; i = et[i].next) {
        int v = et[i].v;
        if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
            int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
            et[i].flow += tmp;
            et[i ^ 1].flow -= tmp;
            if ((l -= tmp) == 0) break;
        }
    }
    return d - l;
}

int Dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(cur));
        flow += dfs(s, t, inf);
    }
    return flow;
}

int dream[N], cost[N];
int main() {
    while (~scanf("%d%d", &n, &m)) {
        int sum = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &dream[i]), sum += dream[i];
        for (int i = 1; i <= m; i++) scanf("%d", &cost[i]);
        init();
        int s = 0, t = n + m + 1;
        for (int i = 1; i <= m; i++) {
            if (cost[i] > 0) {
                sum += cost[i];
                addedge(s, i + n, cost[i]);
            } else {
                addedge(i + n, t, -cost[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            addedge(s, i, dream[i]);
            int cnt, v;
            scanf("%d", &cnt);
            while (cnt--) {
                scanf("%d", &v);
                addedge(i, v + n, inf);
            }
        }
        int ans = Dinic(s, t);
        int number = 0;
        for (int i = 1; i <= n; i++) {
            number += dist[i] != -1;
        }
        cout << sum - ans << " " << number << endl;
    }
    return 0;
}
