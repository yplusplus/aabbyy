#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 400000 + 40;
int a[N];
int n;
int last[N];
int pos[N];
int nxt[N];

struct Node {
    int mi;
} node[N << 2];

void build(int p, int l, int r) {
    node[p].mi = N;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return node[p].mi;
    }

    int mid = (l + r) >> 1;
    int res = N;
    if (L <= mid) res = min(res, query(p << 1, l, mid, L, R));
    if (mid < R) res = min(res, query(p << 1 | 1, mid + 1, r, L, R));
    return res;
}

void modify(int p, int l, int r, int x, int y) {
    if (l == r) {
        node[p].mi = y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) modify(p << 1, l, mid, x, y);
    else modify(p << 1 | 1, mid + 1, r, x, y);
    node[p].mi = min(node[p << 1].mi, node[p << 1 | 1].mi);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        last[a[i]] = 0;
        nxt[i] = 0;
    }

    for (int i = n; i >= 1; i--) {
        int x = a[i];
        if (last[x] == 0) last[x] = i;
        nxt[i] = pos[x];
        pos[x] = i;
    }
    
    build(1, 1, n);
    pair<int, int> ans{N, N};
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        if (i + 1 <= last[x] - 1) {
            int res = query(1, 1, n, i + 1, last[x] - 1);
            if (res != N) {
                ans = min(ans, {res, x});
            }
        }
        if (nxt[i])
            modify(1, 1, n, nxt[i], x);
    }

    if (ans.first != N) {
        printf("%d %d\n", ans.first, ans.second);
    } else {
        puts("-1");
    }
    return 0;
}
