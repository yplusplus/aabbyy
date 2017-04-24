#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 4111;
int dp[N][2];
short lcp[N][N];
char str[N];
int rec[N];
pair<int, int> pre[N][2];
const int INF = 1 << 20;

void output(int pos, int state) {
    if (pos == 0) return;
    pair<int, int> t = pre[pos][state];
    output(t.first, t.second);
    if (state == 0) printf("%c", str[pos]);
    else {
        printf("(%d,%d)", t.first + 1 - rec[pos], pos - t.first);
    }
}

bool update(int a, int b, int c, int d, int w) {
    if (dp[a][b] > dp[c][d] + w) {
        dp[a][b] = dp[c][d] + w;
        pre[a][b] = pair<int, int>(c, d);
        return true;
    }
    return false;
}

void init() {
    memset(lcp, 0, sizeof(lcp));
    int n = strlen(str + 1);
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            lcp[i][j] = (str[i] == str[j]) ? (lcp[i + 1][j + 1] + 1) : 0;
        }
    }
}

void solve() {
    init();
    int n = strlen(str + 1);
    for (int i = 0; i <= n; i++) dp[i][0] = dp[i][1] = INF;
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        int idx = -1;
        int len = 0;
        for (int j = 1; j <= i; j++) {
            if (idx == -1 || lcp[j][i + 1] > lcp[idx][i + 1]) {
                idx = j;
            }
        }
        if (idx != -1) len = lcp[idx][i + 1];
        //0
        if (dp[i][0] != INF) {
            update(i + 1, 0, i, 0, 8 + 1);
            for (int j = 1; j <= len; j++) {
                if (update(i + j, 1, i, 0, 24 + 1)) rec[i + j] = idx;
            }
        }
        //1
        if (dp[i][1] != INF) {
            update(i + 1, 0, i, 1, 8 + 1);
            for (int j = 1; j <= len; j++) {
                if (update(i + j, 1, i, 1, 24 + 1)) rec[i + j] = idx;
            }
        }
    }
    int ans = min(dp[n][0], dp[n][1]);
    printf("%d\n", ans);
    if (ans == dp[n][0]) output(n, 0);
    else output(n, 1);
    puts("");
}

int main() {
    freopen("lz.in", "r", stdin);
    freopen("lz.out", "w", stdout);
    while (~scanf("%s", str + 1)) {
        solve();
    }
    return 0;
}

