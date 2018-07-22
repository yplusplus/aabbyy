#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int mod = 1000000007;
const int N = 2010;
long long fac[N], inv[N];

long long mpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return ans;
}

map<pair<int, int>, int > mp;

int main()
{
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mpow(fac[i], mod - 2);
    }

    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n > m) swap(n, m);
        if (mp.count(make_pair(n, m))) {
            printf("%d\n", mp[make_pair(n, m)]);
            continue;
        }

        long long ans1 = 1, ans2 = 1;

        for (int i = 0; i < n; i++) {
            int st = 3 + i;
            ans1 = ans1 * fac[st + m - 1] % mod;
            ans2 = ans2 * fac[st - 1] % mod;

            st = n - i + m - 1;
            ans2 = ans2 * fac[st] % mod;
            ans1 = ans1 * fac[st - m] % mod;
        }

        ans1 *= mpow(ans2, mod - 2);
        ans1 %= mod;
        mp[make_pair(n, m)] = ans1;
        printf("%d\n", (int)ans1);
    }
    return 0;
}
