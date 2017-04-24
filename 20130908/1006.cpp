#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

int n, m, k;
const int N = 1111;
const int M = 111;
const int K = 111;
const double EPS = 1e-8;
const double FINF = 1e100;
double city[M][M], whet[M][K];
double dp[N][M];
int cond[N], stk[N], top;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}

int main() {
    //freopen("in", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) scanf("%d", cond + i);
        for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) {
            scanf("%lf", city[i] + j);
            city[i][j] = log(city[i][j]);
        }
        for (int i = 0; i < m; i++) for (int j = 0; j < k; j++) {
            scanf("%lf", whet[i] + j);
            whet[i][j] = log(whet[i][j]);
        }
        dp[0][0] = 0;
        for (int i = 1; i < m; i++) dp[0][i] = -FINF;
        for (int i = 1; i <= n; i++) { // day i
            for (int j = 0; j < m; j++) { // to j
                dp[i][j] = -FINF;
                for (int k = 0; k < m; k++) { // from k
                    dp[i][j] = max(dp[i][j], dp[i - 1][k] + city[k][j] + whet[j][cond[i]]);
                }
            }
        }
        //for (int i = 0; i <= n; i++) {
            //for (int j = 0; j < m; j++) cout << dp[i][j] << ' '; cout << endl;
        //}
        double mx = -FINF;
        for (int i = 0; i < m; i++) {
            if (sgn(mx - dp[n][i]) < 0) {
                top = -1;
                stk[++top] = i;
                mx = dp[n][i];
            } else if (sgn(mx - dp[n][i]) == 0) stk[++top] = i;
        }
        double rec = mx;
        //cout << mx << endl;
        for (int i = 0; i < m; i++) dp[n][i] = -FINF;
        for (int i = 0; i <= top; i++) {
            dp[n][stk[i]] = 0;
            //cout << stk[i] << ' '; cout << endl;
        }
        for (int i = n - 1; i >= 0; i--) { // day i
            for (int j = 0; j < m; j++) { // to j
                dp[i][j] = -FINF;
                for (int k = 0; k < m; k++) { // from k
                    dp[i][j] = max(dp[i][j], dp[i + 1][k] + city[j][k] + whet[k][cond[i + 1]]);
                }
            }
        }
        //for (int i = 0; i <= n; i++) {
            //for (int j = 0; j < m; j++) cout << dp[i][j] << ' '; cout << endl;
        //}
        //cout << dp[0][0] << endl;
        int mk = 0;
        top = -1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                if (sgn(dp[i - 1][mk] - (dp[i][j] + city[mk][j] + whet[j][cond[i]])) == 0) {
                    mk = j;
                    break;
                }
            }
            stk[++top] = mk;
        }
        for (int i = 0; i <= top; i++) {
            if (i) putchar(' '); 
            printf("%d", stk[i]);
        }
        puts("");
    }
    return 0;
}