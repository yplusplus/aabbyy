#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <climits>
using namespace std;

const int N = 1111;
const int OFFSET = 512;

int id[N][N];
int x[N], y[N];
int eh[N], tot;
int dist[N], cur[N];
int s, t, ss, tt;
int n;
int dx[] = {-1, -1, 1};
int dy[] = {1, 0, 0};
vector<int> vec[N];
bool visit[N];
int color[N];

struct Edge {
    int u, v, cap, flow, next;
    Edge() {}
    Edge(int u, int v, int cap, int flow, int next) : u(u), v(v), cap(cap), flow(flow), next(next) {}
} et[N * N];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
    et[tot] = Edge(u, v, cap, flow, eh[u]);
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}

void myaddedge(int u, int v, int l, int r) {
    addedge(ss, v, l);
    addedge(u, tt, l);
    addedge(u, v, r - l);
}

bool bfs(int s, int t) {
    memset(dist, -1, sizeof(dist));
    queue<int> que;
    que.push(s);
    dist[s] = 0;
    while (!que.empty()) {
        int u = que.front(); que.pop();
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
        memcpy(cur, eh, sizeof(eh));
        flow += dfs(s, t, INT_MAX);
    }
    return flow;
}

inline bool is_down(int x, int y) { return x & 1; }

void build() {
    init();
    s = n, t = n + 1;
    ss = n + 2, tt = n + 3;
    for (int i = 0; i < n; i++) {
        if (is_down(x[i], y[i])) {
            for (int j = 0; j < 3; j++) {
                int nx = x[i] + dx[j], ny = y[i] + dy[j];
                if (id[nx][ny] != -1) {
                    myaddedge(id[x[i]][y[i]], id[nx][ny], 0, 1);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (is_down(x[i], y[i])) {
            myaddedge(s, id[x[i]][y[i]], 1, 2);
        } else {
            myaddedge(id[x[i]][y[i]], t, 1, 2);
        }
    }
    myaddedge(t, s, 0, INT_MAX);
}

void get_graph() {
    for (int i = 0; i < n; i++) {
        if (is_down(x[i], y[i])) {
            int u = id[x[i]][y[i]];
            for (int j = eh[u]; j != -1; j = et[j].next) {
                int v = et[j].v;
                if (v >= 0 && v < n && et[j].flow > 0) {
                    vec[u].push_back(v);
                    vec[v].push_back(u);
                }
            }
        }
    }
}

vector<int> link;
void dfs(int u) {
    link.push_back(u);
    visit[u] = true;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            dfs(v);
        }
    }
}

void solve() {
    build();
    Dinic(ss, tt);
    bool valid = true;
    for (int i = eh[ss]; i != -1; i = et[i].next) {
        if (et[i].cap > et[i].flow) {
            valid = false;
            break;
        }
    }
    if (valid) {
        get_graph();
        //for (int i = 0; i < n; i++) { cout << "************* " << i << endl; for (int j = 0; j < vec[i].size(); j++) { cout << vec[i][j] << " "; } cout << endl; }
        int ans = 0;
        memset(visit, false, sizeof(visit));
        for (int i = 0; i < n; i++) {
            if (!visit[i]) {
                link.clear();
                dfs(i);
                int j = 0;
                assert(link.size() >= 2);
                if (link.size() & 1) {
                    ans++;
                    for (j = 0; j < 3; j++) {
                        color[link[j]] = ans;
                    }
                }
                for (; j < link.size(); j += 2) {
                    ans++;
                    for (int k = 0; k < 2; k++) {
                        color[link[j + k]] = ans;
                    }
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            cout << color[i];
            if (i == n - 1) cout << endl;
            else cout << ' ';
        }
    } else {
        cout << "No solution" << endl;
    }
}

int main() {
    freopen("tiling.in", "r", stdin);
    freopen("tiling.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;
    memset(id, -1, sizeof(id));
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i] += OFFSET, y[i] += OFFSET;
        id[x[i]][y[i]] = i;
    }
    solve();
    return 0;
}
