#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

const int N = 20;
long long dp[1 << N];
int bits[1 << N];
int mask[N];
int a[N], b[N];

void update(long long &x, long long y) {
    x = max(x, y);
}

int main()
{
    for (int i = 1; i < (1 << N); i++)
        bits[i] = bits[i >> 1] + (i & 1);

    int n;
    while (scanf("%d", &n) != EOF) {
        dp[0] = 0;
        for (int i = 1; i < (1 << n); i++) dp[i] = -1LL << 60;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i], &b[i]);
            mask[i] = 0;
            int x, y;
            scanf("%d", &x);
            while (x--) {
                scanf("%d", &y);
                y--;
                mask[i] |= (1 << y);
            }
        }

        for (int i = 0; i < (1 << n); i++) {
            if (dp[i] == (-1LL << 60)) continue;
            for (int j = 0; j < n; j++) {
                if ((i & mask[j]) != mask[j]) continue;
                if (i & (1 << j)) continue;
                update(dp[i | (1 << j)], dp[i] + bits[i | (1 << j)] * a[j] + b[j]);
            }
        }
        printf("%lld\n", *max_element(dp, dp + (1 << n)));
    }

    return 0;
}
