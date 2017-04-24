#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 10007;

char s[100010];
int dp[100010];
int main()
{
    memset(dp,0,sizeof(dp));
    dp[0] = dp[1] = 1;
    for(int i = 2; i < 100010; i ++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%s",s);
        int i = 0,n = strlen(s);
        int ans = 1;
        while(i < n) {
            while(i < n && s[i] != 'h') i ++;
            if(i == n) break;
            if(s[i + 1] != 'e' || i + 3 >= n) {
                i ++;
                continue;
            }
            int cnt = 0;
            while(i + 1 < n && s[i] == 'h' && s[i + 1] == 'e') i += 2,cnt ++;
            ans = ans * dp[cnt] % mod;
        }
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}

