#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

long long ceil(long long a, long long b) {
    return (a + b - 1) / b;
}

int calc(long long a, long long b, long long c, long long x, long long y) {
    long long diy = a / c;
    long long first_month = ceil((x - 1) * a, b) * b - (x - 1) * a;
    long long st = (y == 0) ? 0 : (first_month + (y - 1) * b) / c;
    long long ed = (first_month + y * b) / c;
    return max(min(ed, diy) - st, 0LL);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, c, x, y, n;
        scanf("%d%d%d%d", &a, &b, &c, &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            int ans = calc(a, b, c, x, y);
            printf("%d\n", ans);
        }
    }
    return 0;
}
