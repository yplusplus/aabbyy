#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10000010;
char s[N];
int f[1 << 13];
bool visit[1 << 13];
const int mod = 1000000007;
int fast_pow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }

    return ans;
}

int get_base(int n) {
    int bit[15];
    memset(bit, 0, sizeof(bit));
    for (int i = 1; i <= n; i++) {
        for (int j = 14; j >= 0; j--) {
            if (!(f[i] >> j)) continue;
            if (!bit[j]) {
                bit[j] = f[i];
                break;
            }
            f[i] ^= bit[j];
        }
    }

    int tot = 0;
    for (int i = 0; i< 15; i++)
        if (bit[i]) tot++;
    return tot;
}

int main() {
    scanf("%s", s);
    int n = strlen(s);
    reverse(s, s + n);
    int a, b, c, d, e, md;
    scanf("%d%d%d%d%d%d%d", &f[1], &a, &b, &c, &d, &e, &md);
    visit[f[1]] = 1;
    int tot = 1;
    for (int i = 2; ; i++) {
        f[i] = (1LL * a * f[i - 1] * f[i - 1] * f[i - 1] * f[i - 1] + 
                1LL * b * f[i - 1] * f[i - 1] * f[i - 1] + 
                1LL * c * f[i - 1] * f[i - 1] + 
                1LL * d * f[i - 1] + e - 1) % md + 1;
        if (visit[f[i]]) break;
        tot = i;
        visit[f[i]] = 1;
    }

    if (n >= 10) {
        int base = get_base(tot);
        long long tmp = 0;
        for (int i = n - 1; i >= 0; i--) {
            tmp = (10 * tmp + s[i] - '0') % (mod - 1);
        }
        int temp = tmp -  base;
        if (temp < 0) temp += mod - 1;
        int ans = fast_pow(2, tmp) - fast_pow(2, temp); 
        if (ans < 0) ans += mod;
        printf("%d\n", ans);
    } else {
        int m = 0;
        for (int i = n - 1; i >= 0; i--)
            m = 10 * m + (s[i] - '0');
        tot = min(tot, m);
        int base = get_base(tot);
        int ans = fast_pow(2, m) - fast_pow(2, m - base); 
        if (ans < 0) ans += mod;
        printf("%d\n", ans);
    }
    return 0;
}
