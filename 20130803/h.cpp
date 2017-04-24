#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long dp[25][25];
long long c[25][25];
long long fac[25];
void init()
{
    memset(c,0,sizeof(c));
    for(int i = 0; i < 25; i ++) {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; j ++)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
    fac[0] = 1;
    for(long long i = 1; i < 25; i ++)
        fac[i] = fac[i - 1] * i;
}

long long cal(int n,int m)
{
    if(n < m) return dp[n][m] = 0;
    if(n == m) return dp[n][m] = 1;
    if(dp[n][m] != -1) return dp[n][m];
    if(n && !m) return 0;
    dp[n][m] = 0;
    for(int i = 1; i <= n; i ++)
        dp[n][m] += c[n - 1][i - 1] * cal(i - 1,m - 1) * fac[n - i];
    return dp[n][m];
}
        
        
int main()
{
    init();
    memset(dp,-1,sizeof(dp));
    dp[0][0] = 1;
    for(int i = 1; i <= 20; i ++)
        for(int j = 1; j <= 20; j ++)
            cal(i,j);
    int t,n,m,r;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d%d",&n,&m,&r);
        long long ans = 0;
        for(int i = m; i <= n; i ++)
            if(dp[i - 1][m - 1] != -1 && dp[n - i][r - 1] != -1) ans += c[n - 1][i - 1] * dp[i - 1][m - 1] * dp[n - i][r - 1];
        printf("%lld\n",ans);
    }
    return 0;
}


