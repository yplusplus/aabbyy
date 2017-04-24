#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 1 << 25;
const int N = 1005;
int dp[N][N];
int a[N][N], b[N][N], c[N][N];

int sign(int x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

void check_min(int &a, int b) {
    if (b < a) a = b;
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = b[i][j] = c[i][j] = INF;
        }
    }
    dp[0][0] = -INF;
    a[0][0] = b[0][0] = c[0][0] = -INF;
    for (int i = 1; i < N; i++) {
        dp[0][i] = INF - 1;
        b[0][i] = min(b[0][i - 1], dp[0][i]);
        dp[i][0] = INF - 1;
        a[i][0] = min(a[i - 1][0], dp[i][0]);
    }
    for (int l = 1; l < N; l++) {
        for (int r = 1; r < N; r++) {
            dp[l][r] = INF;
            check_min(dp[l][r], a[l - 1][r]);
            check_min(dp[l][r], b[l][r - 1]);
            check_min(dp[l][r], c[l - 1][r - 1]);
            dp[l][r] = sign(dp[l][r]) - dp[l][r];
            a[l][r] = min(a[l - 1][r], dp[l][r]);
            b[l][r] = min(b[l][r - 1], dp[l][r]);
            c[l][r] = min(c[l - 1][r - 1], dp[l][r]);
        }
    }
    int T, X, Y, P;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &X, &Y, &P);
        if (X > Y) swap(X, Y);
        int ans = dp[X][Y];
        if (ans > 0) {
            ans = INF - ans + 2 * P;
            printf("Sita %d\n", ans);
        } else {
            ans = INF + ans + 2 * P;
            printf("Gita %d\n", ans);
        }
    }
    return 0;
}
