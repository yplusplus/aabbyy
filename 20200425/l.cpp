#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10000 + 100;
int a[N], b[N];
int dp[N];
int n;

struct BIT {
    void clear() { memset(c, 0,sizeof(c)); }
    int lowbit(int x) { return x & (-x); }
    void update(int x, int v) {
        for (int i = x; i < N; i += lowbit(i)) {
            c[i] = max(c[i], v);
        }
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            res = max(res, c[i]);
        }
        return res;
    }
    int c[N];
}bit;

int calc() {
    bit.clear();
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        if (b[i] <= 0) continue;
        int x = bit.query(a[i]);
        dp[a[i]] = max(dp[a[i]], x + b[i]);
        bit.update(a[i], dp[a[i]]);
    }
    int ans = bit.query(N - 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            b[i] = x / 10000;
            a[i] = x % 10000 + 1;
        }
        int ans = calc();
        reverse(a + 1, a + 1 + n);
        reverse(b + 1, b + 1 + n);
        ans = max(ans, calc());
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
