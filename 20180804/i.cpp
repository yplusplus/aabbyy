#include <iostream>
#include <set>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 200002;
const int M = N * 24;

int attach[N];
int n, m;
int nodecnt;
bool visit[N];
struct Node {
    int l, r;
    int eh;
} node[M];
int tot;
struct Edge {
    int v, next;
} et[M * 2];

void addedge(int u, int v) {
    tot++;
    Edge e = {v, node[u].eh};
    et[tot] = e;
    node[u].eh = tot;
}

int insert(int p, int l, int r, int L, int R, int v) {
    if (p == 0) {
        p = ++nodecnt;
        node[p].l = node[p].r = 0;
        node[p].eh = -1;
    }

    if (L <= l && r <= R) {
        addedge(p, v);
        return p;
    }

    int mid = (l + r) >> 1;
    if (L <= mid) {
        node[p].l = insert(node[p].l, l, mid, L, R, v);
        node[p].r = node[p].r;
    }
    if (mid < R) {
        node[p].l = node[p].l;
        node[p].r = insert(node[p].r, mid + 1, r, L, R, v);
    }
    return p;
}

vector<int> segs;
void query(int p, int l, int r, int x) {
    if (p == 0) return;
    for (int i = node[p].eh; i != -1; i = et[i].next) {
        int s = et[i].v;
        if (!visit[s]) {
            visit[s] = true;
            segs.push_back(s);
        }
    }
    node[p].eh = -1;

    if (l == r) { return; }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        query(node[p].l, l, mid, x);
    } else {
        query(node[p].r, mid + 1, r, x);
    }
}

using Segment = pair<int, int>;
vector<Segment> segments;

int get_idx(vector<int> &vec, int x) {
    if (x > vec.back()) return -1;
    auto it = lower_bound(vec.begin(), vec.end(), x);
    return it - vec.begin();
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        nodecnt = 0;
        tot = 0;
        int root = 0;
        vector<int> vec;
        segments.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &segments[i].first, &segments[i].second);
            visit[i] = false;
            attach[i] = 0;
            int L = segments[i].first;
            vec.push_back(L - 1);
            vec.push_back(L);
            vec.push_back(L + 1);
            int R = segments[i].second;
            vec.push_back(R - 1);
            vec.push_back(R);
            vec.push_back(R + 1);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        for (int i = 0; i < n; i++) {
            int L = get_idx(vec, segments[i].first);
            int R = get_idx(vec, segments[i].second);
            root = insert(root, 0, (int)vec.size() - 1, L, R, i);
        }

        int pre = 0;
        printf("Case #%d:\n", Case++);
        for (int i = 0; i < m; i++) {
            int x;
            scanf("%d", &x);
            x ^= pre;
            x = get_idx(vec, x);
            segs.clear();
            if (x >= 0) query(root, 0, (int)vec.size() - 1, x);

            if (segs.empty()) {
                pre = 0;
            } else {
                pre = 1;
                for (int s: segs) {
                    attach[s] = i + 1;
                    pre = 1LL * pre * (s + 1) % 998244353;
                }
            }
            printf("%d\n", (int)segs.size());
        }
        for (int i = 0; i < n; i++) {
            printf("%d%c", attach[i], i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
