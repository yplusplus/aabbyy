#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
int dp[N][N][2];
int f[N][N][2];

void up(int &x,int y)
{
    x = min(x,y);
}

void up2(int &x,int y)
{
    x = max(x,y);
}

int dfs(int x,int y,int flag)
{
    if(dp[x][y][flag] != -1) return dp[x][y][flag];
    if(flag & 1) {
        if(y < 2) return dp[x][y][flag] = 0;
        int wins = 0;
        if(x >= 1 && !dfs(x - 1,y - 2,0)) wins = 1;
        if(!dfs(x + 1,y - 2,0)) wins = 1;
        if(wins) {
            f[x][y][1] = 0x7fffffff;
            if(x >= 1 && !dfs(x - 1,y - 2,0)) up(f[x][y][1],f[x - 1][y - 2][0] + 1);
            if(!dfs(x + 1,y - 2,0)) up(f[x][y][1],f[x + 1][y - 2][0] + 1);
        }
        else {
            if(x >= 1 && dfs(x - 1,y - 2,0)) up2(f[x][y][1],f[x - 1][y - 2][0] + 1);
            up(f[x][y][1],f[x + 1][y - 2][0] + 1);
        }
        return dp[x][y][1] = wins;
    }
    else {
        if(x < 2) return dp[x][y][flag] = 0;
        int wins = 0;
        if(y >= 1 && !dfs(x - 2,y - 1,1)) wins = 1;
        if(!dfs(x - 2,y + 1,1)) wins = 1;
        if(wins) {
            f[x][y][0] = 0x7fffffff;
            if(y >= 1 && !dfs(x - 2,y - 1,1)) up(f[x][y][0],f[x - 2][y - 1][1] + 1);
            if(!dfs(x - 2,y + 1,1)) up(f[x][y][0],f[x - 2][y + 1][1] + 1);
        }
        else {
            if(y >= 1) up2(f[x][y][0],f[x - 2][y - 1][1] + 1);
            up2(f[x][y][0],f[x - 2][y + 1][1] + 1);
        }
        return dp[x][y][0] = wins;
    }
}

int steps(int x,int y)
{
    if(x < 2) return 0;
    int step = min(x - 2,y) / 3;
    x -= 2 + 3 * step;
    y -= 3 * step;
    int ans = step * 2 + 1;
    if(y >= 3) return ans + 1;
    return ans;
}

int main()
{
    memset(dp,-1,sizeof(dp));
    for(int i = 1; i <= 10; i ++) {
        for(int j = 1; j <= 20; j ++) {
            dfs(i,j,0);
            //cout << f[i][j][0] << " ";
            assert(f[i][j][0] == steps(i,j));
        }
        //cout << endl;
    }
    freopen("knights.in","r",stdin);
    freopen("knights.out","w",stdout);
    int n,x,y;
    while(scanf("%d",&n) != EOF) {
        if(!n) break;
        int ansx = 0x7fffffff,ansy = 0x7fffffff;
        while(n --) {
            scanf("%d%d",&x,&y);
            int step = steps(x,y);
            if(step & 1) up(ansx,step);
            else up(ansy,step);
        }
        if(ansx < ansy) puts("Andrew wins the game");
        else puts("Peter wins the game");
    }
    return 0;
}

