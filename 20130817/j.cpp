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

const int N = 122;
const int S = 111;
int n, s;
int c[S][N];
int dp[N][111];
int le[N], ri[N];
int sum[N];
int main() {
    while (~scanf("%d%d", &s, &n)) {
        if (!s && !n) break;
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= s; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &c[i][j]);
                sum[j] += c[i][j];
            }
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &le[i], &ri[i]);
        }
        memset(dp, -1, sizeof(dp));
        dp[0][100] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 100; j++) {
                if (dp[i][j] == -1) continue;
                for (int k = le[i + 1]; k <= ri[i + 1] && k <= j; k++) {
                    dp[i + 1][j - k] = max(dp[i + 1][j - k], dp[i][j] + k * sum[i + 1]);
                }
            }
        }
        //cout << dp[n][0] << " " << n << endl;
        int x = dp[n][0] / (s * 100);
        int y = (dp[n][0] % (s * 100)) * 10 / (s * 100);
        int left = (dp[n][0] % (s * 100)) * 10 % (s * 100);
        int z = left * 10 / (s * 100);
        left = left * 10 % (s * 100);
        if(left * 10 / (s * 100) >= 5) {
            z ++;
            if(z == 10) {
                z = 0;
                y ++;
                if(y == 10) x ++,y = 0;
            }
        }
        printf("%d.%d%d\n",x,y,z);
    }
    return 0;
}



