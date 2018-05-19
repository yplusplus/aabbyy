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

const int N = 200010;
long long sum[N];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++) {
            scanf("%lld", &sum[i]);
        }
        for (int i = n - 1; i >= 0; i--) sum[i] += sum[i + 1];
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            if (sum[i] >= i) ans = i;
        }
        printf("%d\n", ans);
    }
    return 0;
}