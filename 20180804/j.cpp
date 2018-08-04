#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

unsigned int maxn[20];

unsigned x, y, z;

unsigned tang() {
    unsigned t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

unsigned long long get_lcm(unsigned long long x, unsigned long long y) {
    unsigned long long d = __gcd(x, y);
    return x / d * y;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; cas++) {
        int n;
        cin >> n >> x >> y >> z;
        int pos = 0;
        for (int i = 1; i <= n; i++) {
            unsigned v = tang();
            if (pos < 20) {
                maxn[pos++] = v;
                sort(maxn, maxn + pos);
            } else {
                for (int j = 0; j < 20; j++) {
                    if (v > maxn[j]) {
                        for (int k = 19; k > j; k--)
                            maxn[k] = maxn[k - 1];
                        maxn[j] = v;
                        break;
                    }
                }
            }
        }

        unsigned long long ans = maxn[0];
        for (int i = 0; i < pos; i++)
            for (int j = 0; j < pos; j++)
                ans = max(ans, get_lcm(maxn[i], maxn[j]));
        cout << "Case #" << cas << ": " << ans << endl;
    }
    return 0;
}
