#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <map>
using namespace std;

int get(int n, int d) {
    return n / d;
}

int main()
{
    int a, b, c, d;
    while (scanf("%d%d%d%d", &a, &b, &c, &d) != EOF) {
        long long x2 = get(b, 2) - get(a - 1, 2);
        long long x1009 = get(b, 1009)- get(a - 1, 1009);
        long long x2018 = get(b, 2018) - get(a - 1, 2018);
        long long y2 = get(d, 2) - get(c - 1, 2);
        long long y1009 = get(d, 1009) - get(c - 1, 1009);
        long long y2018 = get(d, 2018) - get(c - 1, 2018);
        long long ans = x2018 * (d - c + 1) + (x2 - x2018) * y1009 + (x1009 - x2018) * y2 +
                        (b - a + 1 - x2 - x1009 + x2018) * y2018;
        printf("%lld\n", ans);
    }
        
    return 0;
}