#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 30;
int dp[N << 1][N << 1];
int in[N], out[N];
int cnt[N << 1][N << 1];
int n;
int dfs(int l, int r) {
    if (l > r) return -2;
    if (dp[l][r] != -1) return dp[l][r];
    if (cnt[l][r] == 1) return dp[l][r] = 0;
    if (cnt[l][r] == 0) return dp[l][r] = -2;
    dp[l][r] = inf;
    for (int i = 1; i <= n; i++) {
        int t = -1;
        if (in[i] >= l && out[i] <= r) {
            //yy
            t = max(t, dfs(out[i], r) + 1);
            //yn
            t = max(t, dfs(in[i] + 1, out[i] - 1) + 1);
            //nn
            t = max(t, dfs(l, in[i] - 1) + 1);
        } else if (in[i] >= l && in[i] <= r) {
            //y
            t = max(t, dfs(in[i] + 1, r) + 1);
            //n
            t = max(t, dfs(l, in[i] - 1) + 1);
        } else if (out[i] >= l && out[i] <= r) {
            //y
            if (out[i] != l) t = max(t, dfs(out[i], r) + 1);
            //n
            t = max(t, dfs(l, out[i] - 1) + 1);
        }
        if (t != -1) dp[l][r] = min(dp[l][r], t);
    }
    if (dp[l][r] == inf) dp[l][r] = -2;
    return dp[l][r];

}
int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        scanf("%d", &n);
        memset(dp, -1, sizeof(dp));
        memset(in, -1, sizeof(in));
        memset(out, -1, sizeof(out));
        for (int i = 1; i <= n << 1; i++) {
            int id;
            scanf("%d", &id);
            if (in[id] == -1) in[id] = i;
            else out[id] = i;
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n << 1; i++) {
            for (int j = i; j <= n << 1; j++) {
                for (int k = 1; k <= n; k++) cnt[i][j] += (out[k] >= i && out[k] <= j);
            }
        }
        printf("Case #%d: %d\n", Case++, dfs(1, n << 1));
    }
    return 0;
}
