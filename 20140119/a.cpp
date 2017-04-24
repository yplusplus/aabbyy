#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const long long MOD = 1000000009LL;
const int N = 8;
int n, base;
long long st[N], ed[N];
int digit[N][60];
long long dp[N][60][20][1 << N];
int mark[N][60][20][1 << N];
int times;

long long dfs(int now, int pos, int sum, int mask) {
    if (now == n) {
        if (--pos == -1) return 1LL;
        now = sum = 0;
    }
    if (mark[now][pos][sum][mask] == times) return dp[now][pos][sum][mask];
    mark[now][pos][sum][mask] = times;
    int u = (mask >> now & 1) ? digit[now][pos] : base - 1;
    long long res = 0;
    for (int d = 0; d <= u; d++) {
        int nmask = mask;
        if ((mask >> now & 1) && d < u) nmask ^= 1 << now;
        if (sum + d < base) res = (res + dfs(now + 1, pos, sum + d, nmask)) % MOD;
    }
    //cout << res << endl;
    return dp[now][pos][sum][mask] = res;
}

void solve() {
    long long ans = 0;
    for (int mask = 0; mask < 1 << n; mask++) {
        //cout << mask << endl;
        memset(digit, 0, sizeof(digit));
        int sign = 1, tot = 0;
        for (int i = 0; i < n; i++) {
            long long x;
            int t = 0;
            if (mask >> i & 1) {
                if (st[i] == 0) { sign = 0; break; }
                x = st[i] - 1;
                sign *= - 1;
            } else {
                x = ed[i];
            }
            while (x) {
                digit[i][t++] = x % base;
                //cout << x % base << endl;
                x /= base;
            }
            tot = max(tot, t);
        }
        if (sign == 0) continue;
        //cout << "tot = " << tot << endl;
        times++;
        ans = (ans + MOD + dfs(0, tot - 1, 0, (1 << n) - 1) * sign) % MOD;
        //cout << ans << endl;
    }
    printf("%lld\n", ans);
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &base);
        for (int i = 0; i < n; i++) scanf("%lld", &st[i]);
        for (int i = 0; i < n; i++) scanf("%lld", &ed[i]);
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
