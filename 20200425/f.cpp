#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int P = 13;
const int M = 10;
const int N = 15;
int a[N];
int digit[N][N];
int dp[N][N][N][1 << 10];
int n;

template<typename T>
void add(T &a, T b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int dfs(int i, int j, int sum, int mask) {
    if (j == n) i--, j = 0, sum = 0;
    if (i == -1) return 1;
    if (dp[i][j][sum][mask] != -1) return dp[i][j][sum][mask];
    int &res = dp[i][j][sum][mask];
    res = 0;
    bool end = mask >> j & 1;
    int u = end ? digit[j][i] : P - 1;
    for (int d = 0; d <= u && d + sum < P; d++) {
        int nmask = mask;
        if (d < u && end) nmask ^= (1 << j);
        add(res, dfs(i, j + 1, d + sum, nmask));
    }
    return res;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++) {
        int x = a[i];
        for (int j = 0; j < M; j++) {
            digit[i][j] = x % P;
            x /= P;
        }
    }
    long long t = dfs(M - 1, 0, 0, (1 << n) - 1);
    //cout << t << endl;
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        ans *= a[i] + 1;
        if (ans >= MOD) ans %= MOD;
    }
    //cout << ans << endl;
    add(ans, MOD - t);
    cout << ans << endl;
}

int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        cout << "Case #" << Case++ << ": ";
        solve();
    }
    return 0;
}
