#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
using namespace std;

typedef long long ll;
const int N = 1111;
char str[N];
ll dp[N][N][2];
bool can[N][N];

long long get_value(int l, int r) {
    for (int i = l; i <= r; i++) {
        if (!isdigit(str[i])) return -1;
    }
    if (str[l] == '0' && l != r) return -1;
    long long res = 0;
    for (int i = l; i <= r; i++) {
        res = 10 * res + str[i] - '0';
    }
    return res;
}

void solve() {
    int n = strlen(str);
    memset(can, false, sizeof(can));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; j <= n; j++) {
            if (i + j - 1 >= n) continue;
            dp[i][j][0] = LLONG_MAX;
            dp[i][j][1] = LLONG_MIN;
            if (str[i] == '+') {
                for (int k = 1; k < j - 1; k++) {
                    if (can[i + 1][k] && can[i + k + 1][j - 1 - k]) {
                        dp[i][j][0] = min(dp[i][j][0], dp[i + 1][k][0] + dp[i + k + 1][j - 1 - k][0]);
                        dp[i][j][1] = max(dp[i][j][1], dp[i + 1][k][1] + dp[i + k + 1][j - 1 - k][1]);
                        can[i][j] = true;
                    }
                }
            } else if (str[i] == '-') {
                if (can[i + 1][j - 1]) {
                    dp[i][j][0] = min(dp[i][j][0], -dp[i + 1][j - 1][1]);
                    dp[i][j][1] = max(dp[i][j][1], -dp[i + 1][j - 1][0]);
                    can[i][j] = true;
                }
                for (int k = 1; k < j - 1; k++) {
                    if (can[i + 1][k] && can[i + k + 1][j - 1 - k]) {
                        dp[i][j][0] = min(dp[i][j][0], dp[i + 1][k][0] - dp[i + k + 1][j - 1 - k][1]);
                        dp[i][j][1] = max(dp[i][j][1], dp[i + 1][k][1] - dp[i + k + 1][j - 1 - k][0]);
                        can[i][j] = true;
                    }
                }
            } else {
                if (j > 9) continue;
                long long ret = get_value(i, i + j - 1);
                if (ret != -1) {
                    dp[i][j][0] = dp[i][j][1] = ret;
                    can[i][j] = true;
                }
            }
        }
    }
    cout << dp[0][n][0] << " " << dp[0][n][1] << endl;
}

int main() {
    while (~scanf("%s", str)) {
        solve();
    }
    return 0;
}
