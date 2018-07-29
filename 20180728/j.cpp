#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 200010;
int n;
int a[N];
int suffix[N];
vector<int> vec[N * 4 + 10];
int attach[N * 4 + 10];
priority_queue<pair<int, int>, vector<pair<int, int> >, std::greater<pair<int, int> > > que;
int deg[N * 4 + 10];
int b[N];

int tot;
void addedge(int u, int v) {
    deg[v]++;
    vec[u].push_back(v);
}

void build(int p, int l, int r) {
    attach[p] = -1;
    tot = max(tot, p);
    if (l == r) { 
        b[l] = p;
        return;
    }

    addedge(p << 1, p);
    addedge(p << 1 | 1, p);

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void build2(int p, int l, int r, int L, int R, int x) {
    if (L <= l && r <= R) {
        addedge(p, x);
        return;
    }

    int mid = (l + r) >> 1;
    if (L <= mid) build2(p << 1, l, mid, L, R, x);
    if (R > mid) build2(p << 1 | 1, mid + 1, r, L, R, x);
}

bool solve() {
    suffix[n] = 0;
    for (int i = n - 1; i >= 0; i--) { suffix[i] = suffix[i + 1] + (a[i] >= 0 ? 1 : 0); }
    for (int i = 0; i <= n * 4; i++) {
        vec[i].clear();
        deg[i] = 0;
    }
    tot = 0;
    build(1, 0, n - 1);
    int x = tot;
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) continue;
        int pos = a[i] % n;
        ++tot;
        if (i > pos) {
            if (suffix[pos] - suffix[i] != i - pos) { return false; }
            build2(1, 0, n - 1, pos, i - 1, tot);
        } else if (i < pos) {
            if (suffix[0] - suffix[i] + suffix[pos] != (n - (pos - i))) { return false; }
            if (i > 0) build2(1, 0, n - 1, 0, i - 1, tot);
            build2(1, 0, n - 1, pos, n - 1, tot);
        }
        attach[tot] = a[i];
        addedge(tot, b[i]);
    }

    for (int i = x + 1; i <= tot; i++) {
        if (deg[i] == 0)
            que.push({attach[i], i});
    }
    for (int i = 0; i < n; i++) {
        int x = b[i];
        if (deg[x] == 0)
            que.push({attach[x], x});
    }

    vector<int> insertions;
    while (!que.empty()) {
        pair<int, int> t = que.top();
        que.pop();
        int u = t.second;
        if (attach[u] != -1) {
            insertions.push_back(attach[u]);
        }

        for (int v: vec[u]) {
            if (--deg[v] == 0) que.push({attach[v], v});
        }
    }

    if (insertions.size() != suffix[0]) return false;
    if (insertions.empty()) puts("");
    else {
        for (int i = 0; i < insertions.size(); i++) {
            printf("%d%c", insertions[i], i + 1 == insertions.size() ? '\n' : ' ');
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        if (!solve()) {
            puts("-1");
        }
    }

    return 0;
}
