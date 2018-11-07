#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 30;
long long dp[N][N][N][2];
int A, B, C;

int bit_count(int x) {
    int res = 0;
    while (x) {
        res += x & 1;
        x >>= 1;
    }
    return res;
}

long long dfs(int i, int x, int y, int c) {
    //cout << i << " " << x << " " << y << " " << c << endl;
    if (x < 0 || y < 0) return 0;
    if (i == -1) {
        return (x == 0 && y == 0 && c == 0) ? 1 : 0;
    }
    if (dp[i][x][y][c] != -1) {
        return dp[i][x][y][c];
    }
    long long res = 0;
    for (int j = 0; j <= 1; j++) {
        for (int k = 0; k <= 1; k++) {
            int nc = c * 2 + (C >> i & 1) - j - k;
            if (nc >= 0 && nc <= 1) {
                res += dfs(i - 1, x - j, y - k, nc);
            }
        }
    }
    return dp[i][x][y][c] = res;
}

void solve() {
    cin >> A >> B >> C;
    int A1 = bit_count(A);
    int B1 = bit_count(B);
    int high = 0;
    //cout << (3 >> 33 & 1) << endl;
    for (int i = N - 1; i >= 0; i--) {
        if ((C >> i) & 1) {
            high = i;
            break;
        }
    }

    memset(dp, -1, sizeof(dp));
    //cout << high << " " << A1 << " " << B1 << endl;
    cout << dfs(high, A1, B1, 0) << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
