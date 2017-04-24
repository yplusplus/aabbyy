#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 111;
const int M = 44444;
const int inf = 1 << 25;
int board[N][N];
int n, m, k;

struct MinCostMaxFlow {
    int eh[N], tot;
    int dist[N], low[N], pre[N];
    bool visit[N];
    int maxFlow, minCost;
    struct Edge {
        int u, v, cost, cap, flow, next;
    } et[M];
    void init() {
        maxFlow = minCost = 0;
        memset(eh, -1, sizeof(eh));
        tot = 0;
    }
    void add(int u, int v, int cost, int cap, int flow) {
        Edge e = {u, v, cost, cap, flow, eh[u]};
        et[tot] = e;
        eh[u] = tot++;
    }
    void addedge(int u, int v, int cost, int cap) {
        add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
    }
    bool bfs(int s, int t) {
        for (int i = 0; i < N; i++) dist[i] = inf;
        pre[s] = -1; dist[s] = 0; low[s] = inf;
        memset(visit, false, sizeof(visit));
        queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int u = que.front(); que.pop();
            visit[u] = false;
            for (int i = eh[u]; i != -1; i = et[i].next) {
                int v = et[i].v;
                if (et[i].cap > et[i].flow && dist[u] + et[i].cost < dist[v]) {
                    dist[v] = dist[u] + et[i].cost;
                    low[v] = min(low[u], et[i].cap - et[i].flow);
                    pre[v] = i;
                    if (!visit[v]) {
                        que.push(v);
                        visit[v] = true;
                    }
                }
            }
        }
        return dist[t] != inf;
    }
    void run(int s, int t) {
        while (bfs(s, t) && dist[t] < 0) {
            int x = pre[t];
            maxFlow += low[t];
            minCost += low[t] * dist[t];
            while (x != -1) {
                et[x].flow += low[t];
                et[x ^ 1].flow -= low[t];
                x = pre[et[x].u];
            }
        }
    }
} mcmf;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool check(int x, int y) {
    return x >= 0  && x < n && y >= 0 && y < m;
}

int get_id(int x, int y) {
    return x * m + y;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board[i][j]);
            }
        }
        mcmf.init();
        int s = n * m, t = s + 1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += board[i][j] * board[i][j];
                int color = (i ^ j) & 1;
                int id = get_id(i, j);
                if (color == 0) {
                    for (int l = 0; l < k; l++) {
                        mcmf.addedge(s, id, 2 * l + 1 - 2 * board[i][j], 1);
                    }
                    for (int l = 0; l < 4; l++) {
                        int x = i + dx[l], y = j + dy[l];
                        if (check(x, y)) { mcmf.addedge(id, get_id(x, y), 0, inf); }
                    }
                } else {
                    for (int l = 0; l < k; l++) {
                        mcmf.addedge(id, t, 2 * l + 1 - 2 * board[i][j], 1);
                    }
                }
            }
        }
        mcmf.run(s, t);
        ans += mcmf.minCost;

        printf("Case %d: %d\n", Case++, ans);
    }

    return 0;
}
