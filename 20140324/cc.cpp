#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const long long MOD = 1000000007LL;
const int N = 222;
long long a[N][N];
int val[N][N];
long long sum[N][N];
int n, m;

void solve(int Case, int t, int sx, int sy) {
    memset(a, 0, sizeof(a));
    a[sx + sy][sx - sy + m] = 1;
    while (t > 1) {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n + m; i++) {
            for (int j = 1; j <= n + m; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
            }
        }
        memset(a, 0, sizeof(a));
        t--;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int x = i + j, y = i - j + m;
                int x1 = max(x - t, 1), y1 = max(y - t, 1);
                int x2 = min(x + t, n + m), y2 = min(y + t, n + m);
                a[x][y] = (sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1] + 2LL * MOD) % MOD;
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = (ans + val[i + j][i - j + m] * a[i + j][i - j + m]) % MOD;
        }
    }
    printf("Case %d: %I64d\n", Case, ans);
}

int main() {
    freopen("treasures.in", "r", stdin);
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int t, x, y;
        scanf("%d%d%d%d%d", &n, &m, &t, &x, &y);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &val[i + j][i - j + m]);
            }
        }
        solve(Case++, t, x, y);
    }
    return 0;
}
