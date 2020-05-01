#include <iostream>
#include <cstring>
using namespace std;

const int N = 100 + 10;
long long sum[N];
long long dp[N][N];
long long a[N];
int n;

long long get_sum(int L, int R) {
    return sum[R] - sum[L - 1];
}

long long dfs(int L, int R) {
    if (L == R) return 0;
    if (dp[L][R] != 0) return dp[L][R];
    long long &res = dp[L][R];
    res = 1LL << 60;
    for (int i = L; i < R; i++) {
        res = min(res, dfs(L, i) + dfs(i + 1, R) + get_sum(L, i) * get_sum(i + 1, R));
    }
    return res;
}

int main() {
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        memset(dp, 0, sizeof(dp));
        cout << dfs(1, n) << endl;
    }
    return 0;
}
