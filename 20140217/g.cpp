#include <bits/stdc++.h>
using namespace std;

const int N = 55;
double p[N][N][2][2];
double dp[N][N][2];
double a[N];
int n,m;
bool visit[N][N];

void update(int x,int y)
{
    p[x][y][0][0] = (1 - a[x]) / (1 - a[x] + a[x] * p[x + 1][y][0][1]);
    p[x][y][0][1] = a[x] * p[x + 1][y][0][1] / (1 - a[x] + a[x] * p[x + 1][y][0][1]);
    p[x][y][1][1] = a[y] / (a[y] + (1 - a[y]) * p[x][y - 1][1][0]);
    p[x][y][1][0] = (1 - a[y]) * p[x][y - 1][1][0] / (a[y] + (1 - a[y]) * p[x][y - 1][1][0]);
    dp[x][y][0] = dp[x][y - 1][1] * p[x][y][1][0] + dp[x + 1][y][0] * p[x][y][0][0];
    dp[x][y][1] = dp[x][y - 1][1] * p[x][y][1][1] + dp[x + 1][y][0] * p[x][y][0][1];
}

int main()
{
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 1; i < n; i ++) {
            cin >> a[i];
        }
        memset(p,0,sizeof(p));
        memset(dp,0,sizeof(dp));
        dp[m][m][0] = 1 - a[m],dp[m][m][1] = a[m];
        for(int i = 1; i < n; i ++) {
            p[i][i][0][0] = p[i][i][1][0] = 1 - a[i];
            p[i][i][0][1] = p[i][i][1][1] = a[i];
            visit[i][i] = 1;
        }
        for(int len = 2; len < n; len ++)
            for(int i = 1; i + len - 1 < n; i ++)
                update(i,i + len - 1);
        double ans = dp[1][n - 1][0] + dp[1][n - 1][1];
        printf("%.20lf\n",ans);
    }
        
    return 0;
}

