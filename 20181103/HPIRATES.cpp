#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

const int N = 100 + 10;
vector<int> vec[N];
int n, m;
char board[N][300];
int cnt[N];

int dfs(int u, int fa) {
    cnt[u] = 1;
    int res = 0;
    for (int v: vec[u]) {
        if (v == fa) continue;
        if (cnt[v] > 0) {
            return 0;
        }
        res = max(res, dfs(v, u));
        cnt[u] += cnt[v];
    }
    return res + 1;
}

void construct(int u, int fa, int L, int R, int dep, int r) {
    assert(L <= R);
    assert(R <= 2 * n - 1);
    assert(dep < r);
    //cout << u << " " << fa << " " << L << " " << R << " " << dep << " " << r<<  endl;
    char ch = (dep & 1) + '0';
    for (int i = L; i <= R; i++) board[dep][i] = ch;
    for (int i = dep; i < r; i++) {
        board[i][L] = board[i][R] = ch;
    }
    for (int v: vec[u]) {
        if (v == fa) continue;
        construct(v, u, L + 1, L + 2 * cnt[v] - 1, dep + 1, r);
        L += 2 * cnt[v];
        for (int i = dep; i < r; i++) {
            board[i][L] = ch;
        }
    }
}

void solve() {
    if (m != n - 1) {
        puts("-1");
        return;
    }
    int r = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] > 0) continue;
        if (i != 1) {
            puts("-1");
            return;
        }
        r = dfs(i, 0);
    }
    int c = 2 * n - 1;
    construct(1, 0, 0, c - 1, 0, r);
    assert(r <= n);
    assert(c <= 2 * n - 1);
    printf("%d %d\n", r, c);
    for (int i = 0; i < r; i++) {
        board[i][c] = '\0';
        puts(board[i]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    solve();
    return 0;
}
