#include <bits/stdc++.h>
#define pii pair <int, int>
#define pic pair <int, char>
#define psi pair <string, int>
#define piii pair <pii, int>
#define UINT unsigned int
#define LL long long
#define xx first
#define yy second
using namespace std;

const int N = 2100000;
const int mod = 998244353;
LL inv[N];

int main () {
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    //    freopen("in.txt", "r", stdin);
    int T, cas = 1;
    cin >> T;
    while (T--) {
        LL n, m;
        cin >> n >> m;
        LL r1 = 1, r2 = m % mod, r = 0;
        for (int i = 1; i <= n; i++) {
            //            cout << r1 << ' ' << r2 << endl;
            r += r1 * r2;
            r %= mod;
            r1 *= (n - i) % mod;
            r1 %= mod;
            r1 *= inv[i];
            r1 %= mod;
            if (i == m) break;
            r2 *= (m - i) % mod;
            r2 %= mod;
        }
        printf("Case #%d: %d\n", cas++, (int)r);
    }
}
