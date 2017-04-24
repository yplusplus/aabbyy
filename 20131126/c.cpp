#include <bits/stdc++.h>
using namespace std;

struct point
{
    int id,x,y;
    point() {}
    point(int id,int x,int y):id(id),x(x),y(y) {}
};
vector<point> v[55];
double dp[1 << 14];

void dfs(int u,int pre,int tot,int sum,int state)
{
    if(tot) dp[state] = sum * 1.0 / tot;
    for(int i = 0; i < v[u].size(); i ++) {
        if(v[u][i].x == pre) continue;
        dfs(v[u][i].x,u,tot + 1,sum + v[u][i].y,state ^ (1 << v[u][i].id));
    }
}

int main()
{
    int n;
    while(scanf("%d",&n), n != 0) {
        int x,y,z;
        for(int i = 0; i < n; i ++) v[i].clear();
        for(int i = 0; i < (1 << n); i ++) dp[i] = 1e20;
        for(int i = 0; i < n - 1; i ++) {
            scanf("%d%d%d",&x,&y,&z);
            v[x].push_back(point(i,y,z));
            v[y].push_back(point(i,x,z));
        }
        for(int i = 0; i < n; i ++)
            dfs(i,-1,0,0,0);
        for(int i = 1; i < (1 << (n - 1)); i ++) {
            for(int j = (i - 1) & i; j; j = (j - 1) & i)
                dp[i] = min(dp[i],dp[j] + dp[i ^ j]);
        }
        printf("%.4lf\n",dp[(1 << (n - 1)) - 1]);
    }
    return 0;
}

