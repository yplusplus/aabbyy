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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1255;
const double eps = 1e-6;
double dp[N][N][2];
int n, m;
double c[N], w[N];

void check_min(double &a, double b) {
    if (b < a) a = b;
}

void check_max(double &a, double b) {
    if (b > a) a = b;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) { scanf("%lf", &c[i]); c[i] /= 100.0; }
        for (int i = 1; i <= n; i++) { scanf("%lf", &w[i]); w[i] /= 100.0; }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j][0] = dinf;
                dp[i][j][1] = -dinf;
            }
        }
        dp[0][0][0] = dp[0][0][1] = 1.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                double tmp;
                //0 min
                if (dp[i][j][0] + eps < dinf) {
                    //0
                    tmp = dp[i][j][0] * (1 - 2 * w[i + 1]);
                    check_min(dp[i + 1][j][0], tmp);
                    check_max(dp[i + 1][j][1], tmp);
                    //1
                    if (j < m) {
                        tmp = dp[i][j][0] * (2 * c[i + 1] - 1);
                        check_min(dp[i + 1][j + 1][0], tmp);
                        check_max(dp[i + 1][j + 1][1], tmp);
                    }
                }
                //1 max
                if (dp[i][j][1] - eps > -dinf) {
                    //0
                    tmp = dp[i][j][1] * (1 - 2 * w[i + 1]);
                    check_min(dp[i + 1][j][0], tmp);
                    check_max(dp[i + 1][j][1], tmp);
                    //1
                    if (j < m) {
                        tmp = dp[i][j][1] * (2 * c[i + 1] - 1);
                        check_min(dp[i + 1][j + 1][0], tmp);
                        check_max(dp[i + 1][j + 1][1], tmp);
                    }
                }
            }
        }
        double ans = dinf;
        for (int i = 0; i <= m; i++) ans = min(ans, dp[n][i][0]);
        ans *= 15000;
        printf("Case #%d: %.3f\n", Case++, ans);
    }
    return 0;
}
