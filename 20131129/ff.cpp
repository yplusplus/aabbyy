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

const int N = 111;
const int W = 1111;
const int MOD = 10007;
int c[N][N];

int cnt[W];
int n, w;
int p[N], sumW[N], sumN[N];
pair<int, int> goods[N];
int dp[N][N][W];

int add(int a, int b) {
    int c = a + b;
    if (c >= MOD) c %= MOD;
    return c;
}

int main() {
    for (int i = 0; i < N; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
    }
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &w);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            int wi;
            scanf("%d", &wi);
            cnt[wi]++;
        }
        int tot = 0;
        for (int i = 0; i < W; i++) { if (cnt[i]) { goods[++tot] = make_pair(i, cnt[i]); } }
        memset(p, 0, sizeof(p));
        p[0] = 1; sumW[0] = 0; sumN[0] = 0;
        for (int i = 1; i <= tot; i++) {
            sumW[i] = sumW[i - 1] + goods[i].first * goods[i].second;
            sumN[i] = sumN[i - 1] + goods[i].second;
            if (sumW[i] > w) break;
            p[i] = p[i - 1] * c[sumN[i]][sumN[i - 1]] % MOD;
        }
        memset(dp[tot + 1], 0, sizeof(dp[tot + 1]));
        dp[tot + 1][0][0] = 1;
        int nowW = 0, nowN = 0;
        for (int i = tot + 1; i > 1; i--) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= w; k++) {
                    dp[i - 1][j][k] = 0;
                }
            }
            for (int j = 0; j <= nowN; j++) {
                for (int k = 0; k <= nowW; k++) {
                    if (dp[i][j][k] == 0) continue;
                    for (int l = 0; l <= goods[i - 1].second; l++) {
                        int ww = k + l * goods[i - 1].first;
                        if (ww > w) break;
                        dp[i - 1][j + l][ww] = add(dp[i - 1][j + l][ww], dp[i][j][k] * c[j + l][j]);
                    }
                }
            }
            nowN += goods[i - 1].second;
            nowW += goods[i - 1].second * goods[i - 1].first;
            nowW = min(nowW, w);
        }
        for (int i = 1; i <= tot + 1; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 1; k <= w; k++) {
                    dp[i][j][k] = add(dp[i][j][k], dp[i][j][k - 1]);
                }
            }
        }
        int ans = p[tot];
        for (int i = 1; i <= tot; i++) {
            if (sumW[i - 1] > w) break;
            for (int j = 0; j < goods[i].second; j++) {
                int nowW = sumW[i - 1] + j * goods[i].first;
                if (nowW > w) break;
                for (int k = 0; k <= n - sumN[i - 1] - j; k++) {
                    int st = w - nowW - goods[i].first;
                    int ed = w - nowW;
                    int tmp = p[i - 1] * c[sumN[i - 1] + j][j] % MOD;
                    int tmp1 = dp[i + 1][k][ed];
                    if (st >= 0) tmp1 = tmp1 + MOD - dp[i + 1][k][st];
                    tmp1 = tmp1 * c[sumN[i - 1] + j + k][k] % MOD;
                    ans = add(ans, tmp * tmp1);
                }
            }
        }
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
