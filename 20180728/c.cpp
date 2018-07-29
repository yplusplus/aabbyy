#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

using LL = long long;
const int OFFSET = 100;
const LL MOD = 1000000007;
LL dp[70][200][3];
int bits[70];
long long dfs(int i, int sum, int last, bool e) {
    //cout << i << " " << sum << " " << last << " " << e << endl;
    if (i == -1) {
        return abs(sum - OFFSET);
    }
    if (!e && dp[i][sum][last] != -1) {
        return dp[i][sum][last];
    }

    int u = e ? bits[i] : 1;
    LL res = 0;
    for (int d = 0; d <= u; d++) {
        int nsum = sum;
        int nlast = last;
        if (last != 2) {
            nsum += d == last ? 1 : -1;
            nlast = d;
        } else {
            nlast = d > 0 ? d : nlast;
        }
        res += dfs(i - 1, nsum, nlast, e && d == u);
        res %= MOD;
    }
    if (!e) dp[i][sum][last] = res;
    return res;
}

LL calc(LL n) {
    LL x = n;
    int tot = 0;
    while (x) {
        bits[tot++] = x & 1;
        x >>= 1;
    }
    return dfs(tot - 1, OFFSET, 2, true);
}

int main() {
    memset(dp, -1, sizeof(dp));    
    int T;
    cin >> T;
    while (T--) {
        LL n;
        cin >> n;
        cout << calc(n) << endl;
    }
    return 0;
}
