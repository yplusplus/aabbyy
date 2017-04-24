#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <functional>

using namespace std;

const int inf = 1 << 30;
const int N = 555;
const int M = 555555;
int eh[N], tot;
int dist[N], pre[N];
bool visit[N];
int n, m;
int mem[N];
int where[N], st[N], ed[N];
int need[N][N];
vector<pair<int, int> > prog[N];

struct Edge {
    int u, v, cost, cap, flow, next;
} et[M];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

bool spfa(int s, int t) {
    for (int i = s; i <= t; i++) { dist[i] = inf; }
    queue<int> que;
    que.push(s);
    dist[s] = 0;
    pre[s] = -1;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        visit[u] = false;
        for (int i = eh[u]; ~i; i = et[i].next) {
            int v = et[i].v;
            if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
                dist[v] = dist[u] + et[i].cost;
                pre[v] = i;
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[t] != inf;
}

int mcmf(int s, int t) {
    int anscost = 0;
    while (spfa(s, t)) {
        anscost += dist[t];
        int x = pre[t];
        while (x != -1) {
            et[x].flow++;
            et[x ^ 1].flow--;
            x = pre[et[x].u];
        }
    }
    return anscost;
}

vector<pair<int, int> > used[N];

void get_scheme() {
    for (int i = 1; i <= m; i++) used[i].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = eh[i]; ~j; j = et[j].next) {
            if (et[j].cap == et[j].flow && et[j].v > n) {
                int id = (et[j].v - 1) / n;
                where[i] = id;
                used[id].push_back(make_pair(need[i][id], i));
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        sort(used[i].begin(), used[i].end());
        int cur_time = 0;
        for (int j = 0; j < used[i].size(); j++) {
            int t = used[i][j].first;
            int id = used[i][j].second;
            st[id] = cur_time;
            cur_time += t;
            ed[id] = cur_time;
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id = -1;
            for (int k = 0; k < prog[i].size(); k++) {
                if (prog[i][k].first <= mem[j]) id = k;
            }
            if (id == -1) need[i][j] = -1;
            else need[i][j] = prog[i][id].second;
        }
    }
    int s = 0, t = n * m + n + 1;
    init();
    for (int i = 1; i <= n; i++) {
        addedge(s, i, 0, 1);
        for (int j = 1; j <= m; j++) {
            if (need[i][j] == -1) continue;
            for (int k = 1; k <= n; k++) {
                addedge(i, n + (j - 1) * n + k, need[i][j] * k, 1);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            addedge(n + (i - 1) * n + j, t, 0, 1);
        }
    }
    int ans = mcmf(s, t);
    get_scheme();
    printf("Average turnaround time = %.2f\n", ans * 1.0 / n);
    for (int i = 1; i <= n; i++) {
        printf("Program %d runs in region %d from %d to %d\n", i, where[i], st[i], ed[i]);
    }
}

int main() {
    int Case = 1;
    while (~scanf("%d%d", &m, &n), n + m) {
        for (int i = 1; i <= m; i++) scanf("%d", &mem[i]);
        for (int i = 1; i <= n; i++) {
            prog[i].clear();            
            int s, t, k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                scanf("%d%d", &s, &t);
                prog[i].push_back(make_pair(s, t));
            }
        }
        printf("Case %d\n", Case++);
        solve();
        puts("");
    }
    return 0;
}
