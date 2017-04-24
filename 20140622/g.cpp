#include <bits/stdc++.h>
using namespace std;

long long dp[65][2][3];

long long cal(long long n)
{
    if(n < 3) return 0;
    int len = 0,bits[65];
    while(n) {
        bits[++ len] = n & 1LL;
        n >>= 1;
    }
    reverse(bits + 1,bits + len + 1);
    memset(dp,0,sizeof(dp));
    dp[0][1][0] = 1;
    for(int i = 0; i < len; i ++)
        for(int j = 0; j < 2; j ++)
            for(int k = 0; k < 3; k ++) {
                if(!dp[i][j][k]) continue;
                //cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
                int f = 1;
                if(j == 1) {
                    f = 1 - bits[i + 1];
                }
                else f = 0;
                dp[i + 1][f][k] += dp[i][j][k];
                int flag = 0;
                if(j == 1 && bits[i + 1] == 0) continue;
                if(j == 1) flag = 1;
                dp[i + 1][flag][(k + 1) % 3] += dp[i][j][k];
            }
    return dp[len][0][0] + dp[len][1][0] - 1;
}
                    
int main()
{
    long long n;
    while(scanf("%lld",&n) != EOF) {
        printf("Day %lld: Level = %lld\n",n,cal(n));
    }
    return 0;
}

