#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1000000 + 10;
const long long inf = 1LL << 60;
vector<pair<int, int> > vec[N];
int n, m, p, q;

void addedge(int u, int v, int w) {
    vec[u].push_back({v, w});
}

long long dist[N];
bool visit[N];
vector<int> X, Y;
int id[N];
int ntot;

struct Node {
    int lson, rson;
    void init() {
        lson = rson = 0;
    }
} node[N];

int newnode() {
    ++ntot;
    node[ntot].init();
    return ntot;
}

int prebuild(int l, int r) {
    int k = newnode();
    if (l == r) {
        id[l] = k;
        return k;
    }

    int mid = (l + r) >> 1;
    node[k].lson = prebuild(l, mid);
    node[k].rson = prebuild(mid + 1, r);
    return k;
}

void build(int p, int l, int r) {
    if (l == r) {
        addedge(p, p + ntot, 0);
        addedge(p + ntot, p, 0);
        return;
    }
    int lson = node[p].lson;
    int rson = node[p].rson;
    int mid = (l + r) >> 1;
    // up
    addedge(lson, p, 0);
    addedge(rson, p, 0);

    // down
    addedge(p + ntot, lson + ntot, 0);
    addedge(p + ntot, rson + ntot, 0);

    build(lson, l, mid);
    build(rson, mid + 1, r);
}

void get_interval(int p, int l, int r, int L, int R, vector<int> &interval) {
    if (L <= l && r <= R) {
        interval.push_back(p);
        return;
    }

    int mid = (l + r) >> 1;
    if (L <= mid) get_interval(node[p].lson, l, mid, L, R, interval);
    if (mid < R) get_interval(node[p].rson, mid + 1, r, L, R, interval);
}

void solve() {
    scanf("%d%d%d%d", &n, &m, &p, &q);
    ntot = 0;
    int root = prebuild(1, 2 * n);
    build(root, 1, 2 * n);

    vector<int> interval;
    for (int i = 1; i <= m; i++) {
        int a, b, c, d, w;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &w);
        interval.clear();
        get_interval(root, 1, 2 * n, a, b, interval);
        int mirror_id = 2 * ntot + 2 * i - 1;
        for (int x: interval) {
            addedge(x, mirror_id, w); 
            addedge(mirror_id + 1, x + ntot, w); 
        }

        interval.clear();
        get_interval(root, 1, 2 * n, c + n, d + n, interval);
        for (int x: interval) { 
            addedge(mirror_id, x + ntot, w); 
            addedge(x, mirror_id + 1, w); 
        }

    }

    X.resize(p);
    for (int i = 0; i < p; i++) { scanf("%d", &X[i]); }
    Y.resize(q);
    for (int i = 0; i < q; i++) { scanf("%d", &Y[i]); }

    priority_queue<pair<long long, int> > pq;
    for (int i = 0; i < N; i++) dist[i] = inf;
    for (int v: Y) {
        pq.push({0, id[v + n]});
        dist[id[v + n]] = 0;
    }
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visit[u]) continue;
        visit[u] = true;
        for (const auto &e: vec[u]) {
            int v = e.first;
            int w = e.second;
            if (!visit[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({-dist[v], v});
            }
        }
    }
    long long ans = 0;
    for (int x: X) {
        ans = max(ans, dist[id[x]]);
    }
    if (ans == inf) {
        puts("boring game");
    } else {
        cout << ans / 2 << endl;
    }
}

int main() {
    solve();
    return 0;
}
