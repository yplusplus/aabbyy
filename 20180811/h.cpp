#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1 << 19;
int a[N], c[N];
int bit[24];
int real[24];

void solve(int n) {
    memset(bit, 0, sizeof(bit));
    int state = 0, zero = 0;
    for (int i = 1; i <= n; i++) {
        state ^= a[i];
        int t = a[i];
        if (!t) zero++;
        for (int j = 18; j >= 0; j--) {
            if (!(a[i] & (1 << j))) continue;
            if (!bit[j]) {
                real[j] = t;
                bit[j] = a[i];
                break;
            }
            a[i] ^= bit[j];
        }
    }
    int ans = 0;

    if (state == 0) {
        printf("%d\n", n);
        return;
    }

    for (int i = 0; i < (1 << 19); i++) {
        int mask = 0, tot = 0;
        bool flag = true;
        for (int j = 0; j < 19; j++) {
            if ((i & (1 << j)) == 0) continue;
            if (!real[j]) {
                flag = false;
                continue;
            }
            if (real[j]) {
                tot++;
                mask ^= real[j];
            }
        }

        if (!flag) continue;

        if ((state ^ mask) == 0) ans = max(ans, n - tot);
        if (c[state ^ mask] >= 1) ans = max(ans, n - tot - 1);

    }
    printf("%d\n", ans);
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            c[a[i]]++;
        }
        solve(n);
    }
    return 0;
}
