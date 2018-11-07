#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007LL;

long long add(long long a, long long b) { return (a + b) % MOD; }
long long mul(long long a, long long b) { return a * b % MOD; }

const int N = 100000 + 10;
int a[N];

long long calc(long long x) {
    if (x == 0) return 1;
    assert(x % 2 == 0);
    long long y = x / 2;
    // x! / (2 ^ y) / y!
    long long res = 1;
    long long inv2 = (MOD + 1) / 2;
    for (int i = y + 1; i <= x; i++) {
        res = mul(res, i);
        res = mul(res, inv2);
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, greater<int>());
    bool owe = false;
    long long ans = 1;
    for (int i = 0, j; i < n; i = j) {
        j = i;
        while (j < n && a[j] == a[i]) j++;
        int cnt = j - i;
        if (owe) {
            ans = mul(ans, cnt);
            cnt--;
            owe = false;
        }

        if (cnt % 2 == 1) {
            ans = mul(ans, cnt);
            cnt--;
            owe = true;
        }
        ans = mul(ans, calc(cnt));
    }
    assert(owe == false);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
