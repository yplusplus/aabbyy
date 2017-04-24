#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
const int mod = 1000000007;
int dp[N][N];

void add(int &x,int y)
{
    x += y;
    if(x >= mod) x -= mod;
}

int dfs(int x,int y)
{
    if(x < 0 || y < 0) return 0;
    if(!x && !y) return 1;
    if(dp[x][y] != -1) return dp[x][y];
    dp[x][y] = 0;
    for(int i = 1; i <= y; i ++) {
        add(dp[x][y],dfs(x + i - 1,y - i));
    }
    add(dp[x][y],dfs(x - 1,y));
    return dp[x][y];
}

//321-avoid permutation
bool check(int m,int a[],int &x,int &y,int n)
{
    for(int i = 1; i <= m; i ++)
        for(int j = i + 1; j <= m; j ++)
            for(int k = j + 1; k <= m; k ++)
                if(a[i] > a[j] && a[j] > a[k]) return true;
    bool visit[N];
    memset(visit,0,sizeof(visit));
    for(int i = 1; i <= m; i ++) visit[a[i]] = 1;
    int xx = 0,yy = 0;
    x = y = 0;
    for(int i = 1; i <= m; i ++)
        if(a[i] > xx) xx = a[i];
        else if(a[i] > yy) yy = a[i];
    for(int i = 1; i <= yy; i ++) if(!visit[i]) return true;
    for(int i = yy + 1; i <= xx; i ++) if(!visit[i]) x ++;
    for(int i = xx + 1; i <= n; i ++) if(!visit[i]) y ++;
    return false;
}

void solve()
{
    int n,m,a[N];
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; i ++)
        scanf("%d",&a[i]);
    int x,y;
    if(check(m,a,x,y,n)) {
        puts("0");
        return;
    }
    cout << dfs(x,y) << endl;
}
    
int main()
{
    memset(dp,-1,sizeof(dp));
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case #%d: ",cas);
        solve();
    }
    return 0;
}

