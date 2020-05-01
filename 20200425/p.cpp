#include <iostream>
using namespace std;

const int N = 100000 + 100;
int open[N][5];
int dp[N][5];
int n;
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 4; j++) {
            cin >> open[i][j];
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 4; j++) {
            dp[i][0] = max(dp[i][0], dp[i - 1][j]);
        }
        for (int j = 1; j <= 4; j++) {
            if (open[i][j] == 0) continue;
            for (int k = 0; k <= 4; k++) {
                if (k == j) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + 1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 5; i++) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << endl;

    return 0;
}
