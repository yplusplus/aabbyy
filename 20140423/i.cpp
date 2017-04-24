#include <bits/stdc++.h>
using namespace std;

const int N = 55;
double ans;
double a[N];
double dp[N];
int n,c;

void dfs(double tot,double p,int pos,int used)
{
    dp[pos - 1] += tot * p;
    if(pos == n + 1) return;
    if(pos == used) {
        if(tot >= c) {
            dfs((tot - c) * 2,p * a[pos],pos + 1,used);
            dfs(tot - c,p * (1 - a[pos]),pos + 1,used);
        }
    }
    else dfs(tot * 2,p * a[pos],pos + 1,used);
}
    
int main()
{
    freopen("tvshow.in","r",stdin);
    freopen("tvshow.out","w",stdout);
    cin >> n >> c;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i];
        a[i] /= 100.0;
    }
    ans = 100;
    for(int i = 0; i <= n; i ++) {
        memset(dp,0,sizeof(dp));
        dfs(100,1,1,i);
        for(int j = 1; j <= n; j ++)
            ans = max(ans,dp[j]);
    }
    printf("%.20lf\n",ans);
    return 0;
}

