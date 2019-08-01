#include <iostream>
using namespace std;

const long long MOD = 1000000007LL;
long long add(long long a, long long b) { return (a + b) % MOD; }
long long mul(long long a, long long b) { return (a * b) % MOD; }

long long power_mod(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

void solve() {
   long long n, k;
    cin >> n >> k;

    long long ans = 0;
    // i * (i - 1) * Bi
    if (n >= 2) {
        long long t = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                long long v = mul(power_mod(i - 1, 2 * n - 4), power_mod(j - 1, 2 * n - 4));
                v = mul(v, power_mod(min(i, j) - 1, 2));
                t = add(t, v);
            }
        }
        t = mul(t, power_mod(k, (n - 2) * (n - 2)));
        t = mul(t, n * n * (n - 1) * (n - 1));
        ans = add(ans, t);
    }

    // i * Bi
    {
        long long t = 0;
        for (int i = 1; i <= k; i++) {
            long long v = power_mod(i - 1, 2 * (n - 1));
            t = add(t, v);
        }
        t = mul(t, n * n);
        t = mul(t, power_mod(k, (n - 1) * (n - 1)));
        ans = add(ans, t);
    }
    cout << ans << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
