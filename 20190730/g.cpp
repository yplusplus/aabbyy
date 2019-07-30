#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int N = 5000 + 50;
const long long MOD = 1000000007;
long long row[N];
long long col[N];
long long pown[N];

long long add(long long a, long long b) { return (a + b) % MOD; }
long long mul(long long a, long long b) { return (a * b) % MOD; }

long long power_mod(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b &1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

long long calc(int x) { return (pown[x] - pown[x - 1] + MOD) % MOD; }

void handle(long long cnt[], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int len = j - i + 1;
            long long x = calc(i);
            long long y = calc(n - j + 1);
            cnt[len] = add(cnt[len], mul(x, y));
        }
    }
}

void solve() {
    int n, r, c, k;
    cin >> n >> r >> c >> k;
    for (int i = 1; i < N; i++) { pown[i] = power_mod(i, n); }
    handle(row, c);
    handle(col, r);
    long long ans = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (i * j >= k) {
                ans = add(ans, mul(row[j], col[i]));
            }
        }
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
