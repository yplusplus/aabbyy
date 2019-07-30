#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef pair<int, int> Point;

const int N = 400000 + 40;

inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

Point points[N];
vector<int> vec[N];
vector<pair<int, int> > row[N];
vector<pair<int, int> > col[N];
vector<int> g[N];
int f[N];
char mv[N];
int deg[N];
int n, m, k;

void addedge(int u, int v) {
    g[u].push_back(v);
    deg[v]++;
}

void get_mv(int fa, int u) {
    const Point &fp = points[fa];
    const Point &p = points[u];
    if (fp.first > p.first) mv[u] = 'v';
    if (fp.first < p.first) mv[u] = '^';
    if (fp.second < p.second) mv[u] = '<';
    if (fp.second > p.second) mv[u] = '>';
}

void dfs(int u, int fa) {
    f[u] = fa;
    for (int v: vec[u]) {
        if (v == fa) continue;
        get_mv(u, v);
        addedge(v, u);
        dfs(v, u);
    }
}

void build(const vector<pair<int, int> > &X) {
    int sz = X.size();
    for (int i = 0; i + 1 < sz; i++) {
        if (X[i].first + 1 == X[i + 1].first) {
            vec[X[i].second].push_back(X[i + 1].second);
            vec[X[i + 1].second].push_back(X[i].second);
        }
    }
}

void solve() {
    n = read();
    m = read();
    k = read();

    for (int i = 1; i <= k; i++) {
        int x = read();
        int y = read();
        points[i] = {x, y};
        row[x].push_back({y, i});
        col[y].push_back({x, i});
    }

    for (int i = 1; i <= n; i++) {
        if (row[i].empty()) continue;
        sort(row[i].begin(), row[i].end()); 
        build(row[i]);
    }
    for (int j = 1; j <= m; j++) {
        if (col[j].empty()) continue;
        sort(col[j].begin(), col[j].end()); 
        build(col[j]);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        int sz = row[i].size();
        for (int j = 0; j < sz; j++) {
            int u = row[i][j].second;
            if (mv[u] == '<') {
                for (int k = j + 1; k < sz; k++) {
                    int v = row[i][k].second;
                    addedge(v, u);
                    if (mv[v] == mv[u]) break;
                }
            }
            if (mv[u] == '>') {
                for (int k = j - 1; k >= 0; k--) {
                    int v = row[i][k].second;
                    addedge(v, u);
                    if (mv[v] == mv[u]) break;
                }
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        int sz = col[i].size();
        for (int j = 0; j < sz; j++) {
            int u = col[i][j].second;
            if (mv[u] == '^') {
                for (int k = j + 1; k < sz; k++) {
                    int v = col[i][k].second;
                    addedge(v, u);
                    if (mv[v] == mv[u]) break;
                }
            }
            if (mv[u] == 'v') {
                for (int k = j - 1; k >= 0; k--) {
                    int v = col[i][k].second;
                    addedge(v, u);
                    if (mv[v] == mv[u]) break;
                }
            }
        }
    }


    queue<int> que;
    vector<int> ops;
    deg[1]++;
    for (int i = 1; i <= k; i++) {
        if (deg[i] == 0) { que.push(i); }
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        ops.push_back(u);
        for (int v: g[u]) {
            deg[v]--;
            if (deg[v] == 0) que.push(v);
        }
    }
    if (ops.size() == k - 1) {
        reverse(ops.begin(), ops.end());
        puts("possible");
        for (int i = 0; i < k - 1; i++) {
            int u = ops[i];
            int x;
            if (mv[u] == '<' || mv[u] == '>')  x = points[u].first;
            else x = points[u].second;
            printf("%c %d\n", mv[ops[i]], x);
        }
    } else {
        puts("impossible");
    }
}

int main() {
    solve();
    return 0;
}
