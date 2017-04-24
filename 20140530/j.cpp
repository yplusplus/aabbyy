#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 111;
long long dp[N][4];
int n, m;

bool bet(int n, int a, int b) {
    memset(dp, 0, sizeof(dp));
    dp[n + 1][0] = 1;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= 3; j++) {
            dp[i][j] += dp[i + 1][j];
            if (i != a && i != b && j) {
                int another = min(a + b - i, i - 1);
                if (i + another == a + b && i > max(a, b)) {
                    another--;
                }
                another -= (another >= a) + (another >= b);
                another -= j - 1;
                if (another <= 0) continue;
                dp[i][j] += dp[i + 1][j - 1] * another;
            }
        }
    }
    long long total = 1;
    for (int i = 1; i <= 3; i++) {
        long long t = n - i * 2;
        total *= (t * (t - 1)) / 2;
    }
    long long win = dp[1][3] * 6;
    return win * 4 > total;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        printf("Case #%d: ", Case++);
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            putchar(bet(n, a, b) ? 'B' : 'F');
        }
        puts("");
    }
    return 0;
}
