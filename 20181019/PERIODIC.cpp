#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 100000 + 10;
int a[N];

void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) continue;
        mx = max(mx, a[i]);
        for (int j = 1; i - j >= 0 && a[i] - j >= 1; j++) {
            if (a[i - j] == -1) a[i - j] = a[i] - j;
            else if (a[i - j] == a[i] - j) break;
            else {
                puts("impossible");
                return;
            }
        }
    }

    int pre = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) continue;
        if (pre != -1 && a[pre] >= a[i]) {
            int x = pre - a[pre] + 1;
            int y = i;
            ans = __gcd(ans, y - x);
        }
        pre = i;
    }

    if (ans == 0) {
        puts("inf");
    } else if (ans < mx) {
        puts("impossible");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
