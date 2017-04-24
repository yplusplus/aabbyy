#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 1111;
const int M = 111;
const int K = 111;
double city[M][M], whet[M][K], dp[N][M];
int cond[N];
const double FINF = 1e100;

int main() {
    //freopen("in", "r", stdin);
    ios::sync_with_stdio(0);
    int T, n, m, k;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) cin >> cond[i];
        for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) {
            cin >> city[i][j];
            city[i][j] = log(city[i][j]);
        }
        for (int i = 0; i < m; i++) for (int j = 0; j < k; j++) {
            cin >> whet[i][j];
            whet[i][j] = log(whet[i][j]);
        }
        for (int i = 0; i < m; i++) dp[n][i] = 0;
        for (int i = n - 1; i >= 0; i--) // day i+1 -> i
            for (int j = 0; j < m; j++) { // from city j
                dp[i][j] = -FINF;
                for (int k = 0; k < m; k++) // to city k
                    dp[i][j] = max(dp[i][j], dp[i + 1][k] + city[j][k] + whet[k][cond[i + 1]]);
            }
        //cout << dp[0][0] << endl;
        for (int i = 0, mk = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (fabs(dp[i][mk] - (dp[i + 1][j] + city[mk][j] + whet[j][cond[i + 1]])) < 1e-8) {
                    mk = j;
                    break;
                }
            }
            if (i) cout << ' ';
            cout << mk;
        }
        cout << endl;
    }
    return 0;
}