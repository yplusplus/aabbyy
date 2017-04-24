#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int digit[N], tot;
long long pw[N];

long long dfs(int pos, int e1, int e2, bool used) {
    int half = tot / 2;
    if (pos < half) { return e1 == 0 || e2 <= 1; }
    if (!e1) {
        int op = tot - 1 - pos;
        long long t = 0;
        if (used) t = 1;
        else t = (half - op) * 9 + 1;
        long long res = pw[pos - half + 1] * t;
        return res;
    }
    long long res = 0;
    int u = digit[pos];
    if (pos == half && (tot & 1)) {
        long long res = 0;
        for (int d = 0; d <= u; d++) {
            res += dfs(pos - 1, e1 && (u == d), e2, used);
        }
        return res;
    } else {
        for (int d = 0; d <= u; d++) {
            if (pos == tot - 1 && d == 0) continue;
            for (int d1 = 0; d1 <= 9; d1++) {
                if (d1 != d && used) continue;
                int ne2;
                int t = digit[tot - 1 - pos];
                if (d1 > t) ne2 = 2;
                else if (d1 == t) ne2 = e2;
                else ne2 = 0;
                res += dfs(pos - 1, e1 && (u == d), ne2, used | (d1 != d));
            }
        }
        return res;
    }
}

long long calc(long long x) {
    tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    long long ret = dfs(tot - 1, 1, 1, 0);
    return ret;
}

int main() {
    freopen("almost.in", "r", stdin);
    freopen("almost.out", "w", stdout);
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 10;
    }
    long long n;
    while (cin >> n, n) {
        if (n < 10) cout << n << endl;
        else {
            long long ans = calc(n);
            for (int i = 1; i < tot; i++) {
                int half = i / 2;
                long long res = 9 * pw[i - half - 1] * (9 * (half) + 1);
                ans += res;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
