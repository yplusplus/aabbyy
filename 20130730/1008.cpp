#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[1 << 16];
char s[110];
int bit[1 << 16];
int a[25],c[25];

bool check(int n)
{
    for(int i = 0; i < n; i ++)
        if(s[c[i]] != s[c[n - i - 1]]) return false;
    return true;
}

int update(int n,int state)
{
    int ans = dp[state];
    for(int i = (state - 1) & state; i; i = (i - 1) & state)
        ans = min(ans,dp[i] + dp[state ^ i]);
    return ans;
}
            
    
    
int solve(int n)
{
    for(int i = 0; i < (1 << n); i ++)
        dp[i] = bit[i];
    for(int i = 1; i < (1 << n); i ++) {
        int ct = 0;
        for(int j = 0; j < n; j ++) {
            if(i & (1 << j)) c[ct ++] = j;
        }
        if(check(ct)) dp[i] = 1;
    }
    for(int i = 1; i < (1 << n); i ++) {
        if(dp[i] == 1) continue;
        dp[i] = update(n,i);
    }
    return dp[(1 << n) - 1];
}
    
    
int main()
{
    memset(bit,0,sizeof(bit));
    for(int i = 1; i < (1 << 16); i ++)
        for(int j = 0; j < 16; j ++)
            if(i & (1 << j)) bit[i] ++;
    int t;
    scanf("%d",&t);
    while(t --) {
        scanf("%s",s);
        int n = strlen(s);
        printf("%d\n",solve(n));
    }
    return 0;
}
    

