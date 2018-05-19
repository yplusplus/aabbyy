#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 111111;
const int M = N * 17;
struct Node {
    int left, right, cnt;
} nodes[M];

int root[N];
int tot;
int n;

void init() {
    tot = 0;
    nodes[tot].left = nodes[tot].right;
    nodes[tot].cnt = 0;
}

int get_node() {
    int k = ++tot;
    nodes[k].left = nodes[k].right = 0;
    nodes[k].cnt = 0;
    return k;
}

int insert(int p, int l, int r, int x) {
    int k = get_node();
    if (l == r) {
        nodes[k].cnt = nodes[p].cnt + 1;
        return k;
    }
    nodes[k] = nodes[p];
    int mid = (l + r) >> 1;
    if (x <= mid) {
        nodes[k].left = insert(nodes[p].left, l, mid, x);
    } else {
        nodes[k].right = insert(nodes[p].right, mid + 1, r, x);
    }
    // pushup
    nodes[k].cnt = nodes[nodes[k].left].cnt + nodes[nodes[k].right].cnt;
    return k;
}

int query(int u, int v, int l, int r, int L, int R) {
    int res = 0;
    if (L <= l && r <= R) {
        return nodes[u].cnt - nodes[v].cnt;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) {
        res += query(nodes[u].left, nodes[v].left, l, mid, L, R);
    }
    if (mid < R) {
        res += query(nodes[u].right, nodes[v].right, mid + 1, r, L, R);
    }
    return res;
}

int main() {
    int q;
    while (~scanf("%d%d", &n, &q)) {

        init();
        root[0] = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            root[i] = insert(root[i - 1], 1, n, x);
        }

        for (int i = 1; i <= q; i++) {
            int L, R;
            scanf("%d%d", &L, &R);
            int l = 1, r = n;
            int ans = 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                int cnt = query(root[R], root[L - 1], 1, n, mid, n);
                if (cnt >= mid) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}