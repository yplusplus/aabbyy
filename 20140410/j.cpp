#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

long long p, m;

long long Union(int a, int b, int c, int d) {
    return max(0LL, min(b, d) - max(a, c) + 1LL);
}

long long calc(int a, int b) {
    if (a < 0 || b < 0) return 0LL;
    long long res = 0;
    long long t;
    int t1 = a % p;
    int t2 = b % p;
    int t3 = (m - t2 + p) % p;
    if (t3 > m) {
        t = Union(0, t1, t3, p - 1) + Union(0, t1, 0, m);
        res += t * (a / p + 1) * (b / p + 1);
        t = t2 + 1 - t;
        res += t * (a / p) * (b / p + 1);
    } else {
        t = Union(0, t1, t3, m);
        res += t * (a / p + 1) * (b / p + 1);
        t = t2 + 1 - t;
        res += t * (a / p) * (b / p + 1);
    }
    if (t2 + 1 < p) {
        int t4 = (m - t2 - 1 + p) % p;
        int t5 = (m - (p - 1) + p) % p;
        if (t5 <= t4) {
            t = Union(0, t1, t5, t4);
            res += t * (a / p + 1) * (b / p);
            t = p - 1 - t2 - t;
            res += t * (a / p) * (b / p);
        } else {
            t = Union(0, t1, t5, p - 1) + Union(0, t1, 0, t4);
            res += t * (a / p + 1) * (b / p);
            t = p - 1 - t2 - t;
            res += t * (a / p) * (b / p);
        }
    }
    return res;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    int a, b, c, d;
    while (T--) {
        scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &p, &m);
        long long ans = 0;
        ans += calc(b, d);
        //cout << ans << endl;
        ans -= calc(a - 1, d);
        //cout << ans << endl;
        ans -= calc(b, c - 1);
        //cout << ans << endl;
        ans += calc(a - 1, c - 1);
        long long t = 1LL * (b - a + 1) * (d - c + 1);
        //cout << t << endl;
        long long gcd = __gcd(ans, t);
        printf("Case #%d: ", Case++);
        cout << ans / gcd << '/' << t / gcd << endl;
    }
    return 0;
}
