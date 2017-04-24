#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define ll long long
const int N = 22;
int digit[N], tot;
ll dp[N][15];

ll dfs(int i, int sum, bool e) {
    //cout << i << endl;
    if (i == -1) return sum == 0;
    if (!e && dp[i][sum] != -1) return dp[i][sum];
    ll res = 0;
    int u = e ? digit[i] : 9;
    for (int d = 0; d <= u; d++) {
        res += dfs(i - 1, (sum + d) % 10, e & (d == u));
    }
    return e ? res : dp[i][sum] = res;
}

ll calc(ll x) {
    if (x < 0) return 0;
    tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 1);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int T, Case = 1;
    ll a, b;
    scanf("%d", &T);
    while (T--) {
        cin >> a >> b;
        ll ans = calc(b) - calc(a - 1);
        printf("Case #%d: %I64d\n", Case++, ans);
    }
    return 0;
}

