#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510;
int dp[N][26];
char s[N];
int sa[N],rak[N];

int main()
{
    int n;
    while(scanf("%d",&n) != EOF) {
        memset(rak,-1,sizeof(rak));
        scanf("%s",s);
        for(int i = 0; i < n; i ++) {
            scanf("%d",&sa[i]);
            rak[sa[i]] = i;
        }
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < 26; j ++)
                dp[i][j] = 0x3f3f3f3f;
        for(int i = 0; i < 26; i ++) dp[0][i] = (s[sa[0]] != 'a' + i);
        for(int i = 1; i < n; i ++) {
            for(int j = 0; j < 26; j ++) {
//                cout << dp[i][j] << " ";
                int cost = (s[sa[i]] != 'a' + j);
//                cout << i << " " << j << " : " << cost << endl;
                for(int k = 0; k < j; k ++)
                    dp[i][j] = min(dp[i][j],dp[i - 1][k] + cost);
                if(rak[sa[i - 1] + 1] < rak[sa[i] + 1]) dp[i][j] = min(dp[i][j],dp[i - 1][j] + cost);
//                cout << dp[i][j] << endl;
            }
        }
        int ans = 0x3f3f3f;
        for(int i = 0; i < 26; i ++)
            ans = min(ans,dp[n - 1][i]);
        if(ans > n) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}

