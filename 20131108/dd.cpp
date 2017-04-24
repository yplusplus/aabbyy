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
const int MOD = 1000000007;
const int N = 1111;
int fac[N], inv_fac[N];
int n, m;
int a[N], dp[N];
int cnt[N];

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

int power_mod(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) { fac[i] = mul(fac[i - 1], i); }
    for (int i = 0; i < N; i++) inv_fac[i] = power_mod(fac[i], MOD - 2);

    while (~scanf("%d%d", &n, &m), n + m) {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        a[0] = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] == a[i - 1]) cnt[i] = cnt[i - 1] + 1;
            else cnt[i] = 1;
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 0; j--) {
                dp[j] = mul(dp[j], (cnt[i] + j));
                if (j) dp[j] = add(dp[j], mul(dp[j - 1], (i - cnt[i] - j + 1)));
            }
        }
        int ans = 0;
        for (int i = 0; i <= m; i++) ans = add(ans, dp[i]);
        a[n + 1] = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] != a[i + 1]) {
                ans = mul(ans, inv_fac[cnt[i]]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
