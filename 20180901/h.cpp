#include <iostream>
using namespace std;

const int N = 600000 + 10;
const int K = 31;

struct node {
    int child[2];
    int sum;
} node[K * N];

int n, m;

int root[N];
int fa[N];
int a[N];
int tot;

int make_leaf(int x, int k) {
    if (k < 0) return 0;
    int p = ++tot;
    node[p].child[0] = node[p].child[1] = 0;
    node[p].sum = 1;
    node[p].child[x & 1] = make_leaf(x >> 1, k - 1);
    return p;
}

bool is_leaf(int a) {
    return node[a].child[0] == 0 && node[a].child[1] == 0;
}

int merge(int a, int b) {
    if (!a || !b) return a ? a : b;
    if (is_leaf(a)) return b;
    if (is_leaf(b)) return a;
    node[a].sum += node[b].sum;
    node[a].child[0] = merge(node[a].child[0], node[b].child[0]);
    node[a].child[1] = merge(node[a].child[1], node[b].child[1]);
    return a;
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int query(int u, int k, int x) {
    for (int i = 0; i < k; i++) {
        int y = x >> i & 1;
        if (!node[u].child[y]) return 0;
        u = node[u].child[y];
    }
    return node[u].sum;
}

void inc(int a) {
    if (a == 0) return;
    swap(node[a].child[0], node[a].child[1]);
    inc(node[a].child[0]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    root[a] = merge(root[a], root[b]);
    fa[b] = a;
}

void solve() {
    while (~scanf("%d%d", &n, &m)) {
        tot = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            root[i] = make_leaf(a[i], K);
            fa[i] = i;
        }

        int type;
        int u, v, k, x;
        while (m--) {
            scanf("%d", &type);
            if (type == 1) {
                scanf("%d%d", &u, &v);
                Union(u, v);
            } else if (type == 2) {
                scanf("%d", &u);
                u = find(u);
                inc(root[u]);
            } else {
                scanf("%d%d%d", &u, &k, &x);
                u = find(u);
                printf("%d\n", query(root[u], k, x));
            }
        }
    }
}

int main() {
   solve();
   return 0;
}
