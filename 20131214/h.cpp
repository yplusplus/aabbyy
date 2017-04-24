#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <cassert>
#include <vector>
using namespace std;

const int N = 333;
int n, m, all;
int state[N][N];
int g[N][N];
map<pair<int, int>, int> mp;

int dfs(int start, int now) {
    if (start == all + 1) { return 0; }
    if (now & 1) { return dfs(start + 1, now >> 1); }
    pair<int, int> t = make_pair(start, now);
    if (mp.count(t)) return mp[t];
    int que[N], tot = 0;
    for (int i = start; i <= start + n && i <= all; i++) {
        if ((~now >> (i - start) & 1) && ((state[start][i] & now) == state[start][i])) que[tot++] = i; 
    }
    int res = all;
    if (tot > 1) {
        for (int i = 0; i < tot; i++) {
            int c = que[i];
            for (int j = i + 1; j < tot; j++) {
                int d = que[j];
                res = min(res, dfs(start, now | (1 << (c - start)) | (1 << (d - start))));
            }
        }
    } else {
        int c = que[0];
        res = min(res, dfs(start, now | (1 << (c - start))));
    }
    return mp[t] = res + 1;
}

int main() {
    while (~scanf("%d%d", &m, &n), n + m) {
        all = n * m;
        memset(g, 0, sizeof(g));
        for (int i = 1; i < all; i++) {
            int k, x;
            scanf("%d", &k);
            if (k == -1) {
                for (int j = i + 1; j <= all && j <= i + n; j++) {
                    g[i][j] = 1;
                }
            } else {
                for (int j = 0; j < k; j++) {
                    scanf("%d", &x);
                    g[i][x] = 1;
                }
            }
        }
        memset(state, 0, sizeof(state));
        for (int i = 1; i <= all; i++) {
            for (int j = max(i - n, 1); j <= i; j++) {
                for (int k = j; k < i; k++) {
                    if (g[k][i]) state[j][i] |= (1 << (k - j));
                }
            }
        }
        mp.clear();
        int ans = dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
