#include <iostream>
#include <climits>
#include <queue>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 33;
const int NN = N * N * 2;
const int M = NN * NN;
char board[N][N];
int id[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int eh[NN], tot;
int dist[NN], cur[NN];
int n, m;

bool inmat(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

struct Edge {
    int u, v, cap, flow, next;
    Edge() {}
    Edge(int u, int v, int cap, int flow, int next) : u(u), v(v), cap(cap), flow(flow), next(next) {}
} et[M];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void add(int u, int v, int cap, int flow) {
    et[tot] = Edge(u, v, cap, flow, eh[u]);
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
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
    int res = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(eh));
        res += dfs(s, t, INT_MAX);
    }
    return res;
}

void solve() {
    //cout << n << " " << m << endl;
    memset(id, 0, sizeof(id));
    tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'W' || board[i][j] == 'N') {
                id[i][j] = ++tot;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'I') {
                id[i][j] = ++tot;
                ++tot;
            }
        }
    }
    //for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { cout << id[i][j] << " "; } cout << endl; }
    int s = 0, t = ++tot;
    init();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'W') {
                addedge(s, id[i][j], 1);
            } else if (board[i][j] == 'N') {
                addedge(id[i][j], t, 1);
            } else {
                addedge(id[i][j], id[i][j] + 1, 1);
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (!inmat(x, y) || board[x][y] == board[i][j]) continue;
                    if (board[x][y] == 'W') {
                        addedge(id[x][y], id[i][j], 1);
                    } else {
                        addedge(id[i][j] + 1, id[x][y], 1);
                    }
                }
            }
        }
    }
    int ans = Dinic(s, t);
    printf("%d\n", ans);
}

int main() {
    while (gets(board[0])) {
        n = 1;
        char *str;
        while ((str = gets(board[n])) && strlen(board[n]) > 0) { n++; }
        m = strlen(board[0]);
        solve();
        if (str == NULL) break;
        //if (signal) break;
    }
    return 0;
}
