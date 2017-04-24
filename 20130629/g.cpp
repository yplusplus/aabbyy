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
const int N = 111;
double dp[N][N][N][2][2];
//时间点 剩余假手 持续时间 hunter warner
int t, n, m, K;
int ti[N];

int main() {
    //ios::sync_with_stdio(false);
    int T;
    scanf("%d", &T);
    //cin >> T;
    while (T--) {
        //cin >> t >> n >> m >> K;
        scanf("%d%d%d%d", &t, &n, &m, &K);
        for (int i = 1; i <= n; i++) scanf("%d", &ti[i]);//cin >> ti[i];
        ti[0] = 0;
        //memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= t; k++) {
                    memset(dp[i][j][k], 0, sizeof(dp[i][j][k]));
                }
            }
        }
        dp[0][m][0][0][0] = 1.0;
        double p1 = 1.0 / K;
        double p2 = (K - 2.0) / K;
        //0 for outside
        //1 for inside
        int delta;
        for (int i = 0; i < n; i++) {
            delta = ti[i + 1] - ti[i];
            //00
            for (int j = 0; j <= m; j++) {
                dp[i + 1][j][0][0][0] += dp[i][j][0][0][0] * p2;
                dp[i + 1][j][0][0][1] += dp[i][j][0][0][0] * p1;
                dp[i + 1][j][0][1][0] += dp[i][j][0][0][0] * p1;
            }
            //01
            for (int j = 0; j <= m; j++) {
                dp[i + 1][j][0][0][0] += dp[i][j][0][0][1] * p1;
                dp[i + 1][j][0][0][1] += dp[i][j][0][0][1] * p2;
                dp[i + 1][j][0][1][1] += dp[i][j][0][0][1] * p1;
            }
            //10
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= t; k++) {
                    int tmp = k + delta;
                    dp[i + 1][j][0][0][0] += dp[i][j][k][1][0] * p1;
                    dp[i + 1][max(0, j - (tmp >= t))][tmp >= t ? 0 : tmp][1][1] += dp[i][j][k][1][0] * p1;
                    dp[i + 1][j][min(t, tmp)][1][0] += dp[i][j][k][1][0] * p2;
                }
            }
            //11
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= t; k++) {
                    int tmp = k + delta; 
                    dp[i + 1][max(j - tmp / t, 0)][0][0][1] += dp[i][j][k][1][1] * p1;
                    dp[i + 1][max(j - tmp / t, 0)][tmp % t][1][1] += dp[i][j][k][1][1] * p2;
                    dp[i + 1][max(j - tmp / t, 0)][tmp % t][1][0] += dp[i][j][k][1][1] * p1;
                }
            }
        }
        delta = 1440 - ti[n];
        double ans = 0;
        for (int j = 0; j <= m; j++) {
            //00
            ans += dp[n][j][0][0][0] * j;
            //01
            ans += dp[n][j][0][0][1] * j;
            for (int k = 0; k <= t; k++) {
                //10
                ans += dp[n][j][k][1][0] * j;
                //11
                int tmp = delta + k;
                ans += dp[n][j][k][1][1] * max(0, j - tmp / t);
            }
        } 
        printf("%.6lf\n", ans);
        //cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}
