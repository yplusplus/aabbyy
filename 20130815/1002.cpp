#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
const int N = 33333;
int n, m, q;
vector<int> vec[N];
int ans[N];
int sizes;

int get_block(int x) { return x / sizes; }

struct Query {
    int block, qid, l, r;
    void read(int _qid) {
        scanf("%d%d", &l, &r);
        l--, r--;
        qid = _qid;
        block = get_block(l);
    }
    bool operator <(const Query &x) const {
        if (block != x.block) return block < x.block;
        return r < x.r;
    }
} query[N];

struct UFS {
    int fa[N];
    void clear() { for (int i = 0; i < n; i++) fa[i] = i; }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    bool Union(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        fa[ra] = rb;
        return true;
    }
} ufs;

int cy[N];
int fa[N];
int find(int x, int qid) {
    if (cy[x] != qid) {
        fa[x] = ufs.fa[x];
        cy[x] = qid;
    }
    return x == fa[x] ? x : fa[x] = find(fa[x], qid);
}

bool Union(int a, int b, int qid) {
        int ra = find(a, qid), rb = find(b, qid);
        if (ra == rb) return false;
        fa[ra] = rb;
        return true;
}

void solve() {
    sort(query, query + q);
    memset(cy, -1, sizeof(cy));
    for (int i = 0; i < q; i++) {
        int j = i, block = query[i].block;
        while (j + 1 < q && query[j + 1].block == block) j++;
        ufs.clear();
        int rc = 0;
        int R = min((block + 1) * sizes - 1, n - 1);
        int pre = R;
        for (int x = i; x <= j; x++) {
            //right
            if (pre < query[x].r) {
                rc += query[x].r - pre;
                for (int y = pre + 1; y <= query[x].r; y++) {
                    for (int z = 0; z < vec[y].size(); z++) {
                        int v = vec[y][z];
                        if (v <= R || v > query[x].r) continue;
                        rc -= ufs.Union(y, v);
                    }
                }
                pre = query[x].r;
            }
            //left
            int L = query[x].l;
            int cc = min(R, query[x].r) - L + 1 + rc;
            for (int y = L; y <= min(R, query[x].r); y++) {
                for (int z = 0; z < vec[y].size(); z++) {
                    int v = vec[y][z];
                    if (v < L || v > query[x].r) continue;
                    cc -= Union(y, v, query[x].qid);
                }
            }
            ans[query[x].qid] = cc;
        }
        i = j;
    }
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) vec[i].clear();
        sizes = (int) ceil(sqrt(n * 1.0));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--, b--;
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        scanf("%d", &q);
        for (int i = 0; i < q; i++) { query[i].read(i); }
        printf("Case #%d:\n", Case++);
        solve();
    }
    return 0;
}
