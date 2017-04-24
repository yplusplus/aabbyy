#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const long long MOD = 1000000007LL;

long long &add(long long &a, long long b) { a = (a + b) % MOD; return a; }
long long &sub(long long &a, long long b) { a = (a - b) % MOD; if (a < 0) a += MOD; return a; }

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        long long c1_1 = 0, c2_1 = 0, c3_2 = 0;
        long long all = 0;
        for (int i = 0, x = 0; i < n; i++) {
            scanf("%d", &x);
            all += (x + 2) / 3;
            while (x > 0 && x % 3 != 0) {
                c1_1++;
                x -= 2;
            }
            if (x >= 6) {
                int y = x / 6;
                c3_2 += y;
                x -= y * 6;
            }
            if (x > 0) {
                c2_1++;
            }
        }
        long long ans = 0;
        for (int i = 0; i <= m; i++) {
            long long x = i;
            long long y = all % MOD;
            // 1_1
            long long t = min(x, c1_1);
            sub(y, t);
            x -= t;
            // 3_2
            t = min(x / 3, c3_2);
            sub(y, t * 2);
            x -= t * 3;
            // 2_1
            t = min(x / 2, c2_1 + (c3_2 - t) * 2);
            sub(y, t);
            x -= t * 2;
            add(ans, y);
            //cout << y << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
