#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1111111;
long long dp[N];
long long a[5], b[5];
long long height, bottom, top;
long long delta;

long long dfs(int h) {
    if (dp[h] != -1) return dp[h];
    long long res = 0;
    for (int i = 0; i < 3; i++) {
        if (h < a[i]) continue;
        long long x = delta * (h - a[i]) / height + top;
        long long cnt = x / a[i];
        res = max(res, dfs(h - a[i]) + cnt * cnt * b[i]);
    }
    return dp[h] = res;
}

int main() {
    while (cin >> height >> bottom >> top >> a[0] >> a[1] >> a[2]) {
        for (int i = 0; i < 3; i++) { b[i] = a[i] * a[i] * a[i]; }
        memset(dp, -1, sizeof(dp));
        delta = (bottom - top);
        cout << dfs(height) << endl;
    }
    return 0;
}
