#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

typedef pair<long long, long long> PLL;
typedef multiset<PLL> Heap;
typedef multiset<PLL>::iterator Heap_itr;
const long long inf = 1LL << 60;
const int N = 222222;
vector<int> vec[N];
int n, target;
int val[N];

Heap *merge(Heap *a, Heap *b) {
    if (a->size() < b->size()) swap(a, b);
    for (Heap_itr it = b->begin(); it != b->end(); it++) {
        a->insert(*it);
    }
    delete b;
    return a;
}

void insert(Heap *heap, PLL w) {
    while (!heap->empty()) {
        PLL t = *(heap->begin());
        if (w.second >= t.first) {
            heap->erase(heap->begin());
            w = PLL(w.first, w.second - t.first + t.second);
        } else if (w.first >= w.second) {
            heap->erase(heap->begin());
            w = PLL(w.first - w.second + t.first, t.second);
        } else {
            break;
        }
    }
    if (w.second > w.first) heap->insert(w);
}

Heap *dfs(int u, int fa) {
    Heap *heap = new Heap;
    if (u == target) {
        PLL t(0, inf);
        if (val[u] < 0) t.first = -val[u];
        insert(heap, t);
        return heap;
    }
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        Heap *child = dfs(v, u);
        heap = merge(heap, child);
    }
    PLL t(0, 0);
    if (val[u] < 0) t.first = -val[u];
    else t.second = val[u];
    insert(heap, t);
    return heap;
}

void solve() {
    Heap *heap = dfs(1, 0);
    long long hp = 0;
    for (Heap_itr it = heap->begin(); it != heap->end(); it++) {
        if (hp >= it->first) {
            hp += it->second - it->first;
        } else {
            break;
        }
    }
    delete heap;
    puts((hp > inf / 2) ? "escaped" : "trapped");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &target);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            vec[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        solve();
    }
    return 0;
}
