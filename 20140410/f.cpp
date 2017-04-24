#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 111111;
int fib[50];
int n, m;
struct UFS {
    int fa[N];
    void clear() { for (int i = 0; i <= n; i++) { fa[i] = i; } }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    bool Union(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        fa[x] = y;
        return true;
    }
} ufs;

struct Edge {
    int u, v, c;
    void read() { scanf("%d%d%d", &u, &v, &c); }
    bool operator <(const Edge &x) const { return c < x.c; }
} edge[N];

int mst() {
    ufs.clear();
    int res = 0;
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (ufs.Union(edge[i].u, edge[i].v)) {
            cnt++;
            res += edge[i].c;
        }
    }
    if (cnt != n - 1) return -1;
    return res;
}

int main() {
    fib[0] = 1, fib[1] = 2;
    for (int i = 2; i < 50; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    //cout << fib[35] << endl;
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) edge[i].read();
        sort(edge, edge + m);
        int mi = mst();
        reverse(edge, edge + m);
        int ma = mst();
        bool found = false;
        //cout << mi << " " << ma << endl;
        for (int i = 0; i < 35; i++) {
            if (mi <= fib[i] && fib[i] <= ma) found = true;
        }
        printf("Case #%d: %s\n", Case++, found ? "Yes" : "No");
    }
    return 0;
}
