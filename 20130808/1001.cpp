#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

long long mod = 1000000007;
long long dp[1000010];
long long prot[1000010];
int a[1000010],c[1000010];

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++)
            scanf("%d",&a[i]);
        sort(a + 1,a + n + 1);
        int p = 1,q = n;
        for(int i = 1; i <= n; i ++)
            if(i & 1) c[i] = a[p ++];
            else c[i] = a[q --];
        dp[1] = c[1];
        prot[0] = 1;
        prot[1] = c[1];
        for(int i = 2; i <= n; i ++) {
            dp[i] = dp[i - 1] * c[i] % mod;
            dp[i] = (dp[i] + max(0,c[i] - c[i - 1]) * prot[i - 1]) % mod;
            dp[i] = (dp[i] + min(c[i],c[i - 1]) * prot[i - 2] % mod * (c[i - 1] - 1)) % mod;
            prot[i] = prot[i - 1] * c[i] % mod;
        }
        printf("%I64d\n",dp[n]);
    }
    return 0;
}

