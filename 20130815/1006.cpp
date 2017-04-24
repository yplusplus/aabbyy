#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp1[1010][1010],dp2[1010][1010];
int match1[1010],match2[1010];

void process(char *s,char *ss,int match[],int n,int m)
{
    int next[256],pos[1010];
    memset(next,-1,sizeof(next));
    for(int i = n; i >= 1; i --) {
        pos[i] = next[s[i]];
        next[s[i]] = i;
    }
    for(int i = 1; i <= n; i ++) {
        int x = i,y = 1;
        while(x <= n && y <= m) {
            if(s[x] == ss[y]) x ++,y ++;
            else x ++;
        }
        if(y > m) match[i] = x - 1;
        else match[i] = -1;
    }
}
        
int main()
{
    char s[1010],str[1010],ss[1010];
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%s",s + 1);
        scanf("%s",str + 1);
        scanf("%s",ss + 1);
        int n = strlen(s + 1);
        int m = strlen(str + 1);
        int r = strlen(ss + 1);
        for(int i = 0; i <= n + 5; i ++)
            for(int j = 0; j <= m + 5; j ++)
                dp1[i][j] = dp2[i][j] = 0;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                if(s[i] == str[j]) dp1[i][j] = dp1[i - 1][j - 1] + 1;
                else dp1[i][j] = max(dp1[i - 1][j],dp1[i][j - 1]);
        process(s,ss,match1,n,r);
        process(str,ss,match2,m,r);
        reverse(s + 1,s + n + 1);
        reverse(str + 1,str + m + 1);
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                if(s[i] == str[j]) dp2[i][j] = dp2[i - 1][j - 1] + 1;
                else dp2[i][j] = max(dp2[i - 1][j],dp2[i][j - 1]);
        int ans = 0;
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m; j ++) {
               if(match1[i] == -1 || match2[j] == -1) continue;
               int x = match1[i],y = match2[j];
               ans = max(ans,dp1[i - 1][j - 1] + r + dp2[n - x][m - y]);
            }
        }
        printf("Case #%d: %d",cas,ans);
        cout << endl;
    }
    return 0;
}

