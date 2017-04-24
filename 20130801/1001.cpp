#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 10007;
int dp[1010][1010];
char s[1010];

int main()
{
    int t;
    scanf("%d",&t);
    memset(dp, 0, sizeof(dp));
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%s",s);
        int n = strlen(s);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (i == j) dp[i][j] = 1;
                else {
                    if (s[i] != s[j]) dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + mod) % mod;
                    else dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % mod;
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[0][n - 1]);
    }
    return 0;
}

