#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int N = 1010;
const int mod = 1000000007;

long long mpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long fac[N], inv[N];
long long pd[N][N];

void init() {
    fac[0] = inv[0] = fac[1] = inv[1] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mpow(fac[i], mod - 2);
    }

    for (int m = 1; m < N; m++) {
        pd[m][0] = 1;
        for (int j = 1; j < N; j++) {
            pd[m][j] = pd[m][j - 1] * m % mod;
        }
    }
}

long long val[N];
long long forwar[N], backwar[N];
long long cal(long long n, int m) {
    if (n < 1) return 0;
    for (int i = 1; i <= m + 2; i++) {
        val[i] = (val[i - 1] + pd[i][m]) % mod;
    }

    if (n <= m + 2) return val[n];

    m++;
    forwar[0] = 1;
    for (int i = 1; i <= m + 1; i++)
        forwar[i] = forwar[i - 1] * (n - i) % mod;

    backwar[m + 2] = 1;
    for (int i = m + 1; i >= 1; i--)
        backwar[i] = backwar[i + 1] * (n - i) % mod;

    long long ans = 0;
    int flag = m % 2 == 0 ? 1 : -1;
    for (int i = 1; i <= m + 1; i++, flag *= -1) {
        ans = (ans + flag * forwar[i - 1] * backwar[i + 1] % mod * val[i] % mod * inv[m + 1 - i] % mod * inv[i - 1]) % mod;
    }
    return (ans + mod) % mod;
}

int a[N];
int main()
{
    init();
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        sort(a + 1, a + n + 1);

        long long ans = 0;
        int i = 1;
        long long pre = 1;
        while (i <= n) {
            int j = i;
            while (j <= n && a[i] == a[j]) j++;
            int m = n - i + 1;
            long long tmp = mpow(a[i], m + 1) - mpow(a[i - 1], m + 1) % mod;
            tmp -= cal(a[i] - 1, m) - cal(a[i - 1] - 1, m);
            tmp %= mod;
            ans = (ans + pre * tmp) % mod;
            if (ans < 0) ans += mod;
            for (int k = i; k < j; k++) pre = pre * a[i] % mod;
            i = j;
        }

        printf("%lld\n", ans);
    }
    return 0;
}

