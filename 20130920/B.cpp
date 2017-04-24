#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
int dp1[110][110][2],dp2[110][110][210],sum[110][110][210];
 
void add(int &x,int y)
{
    x += y;
    if(x >= mod) x -= mod;
}

void dec(int &x,int y)
{
    x -= y;
    if(x < 0) x += mod;
}

void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(dp1,0,sizeof(dp1));
    dp1[0][0][0] = 1;
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j <= m; j ++) {
            for(int k = 0; k <= j; k ++) {
                for(int r = 0; r < 2; r ++) {
                   add(dp1[i][j][(r + j) & 1],dp1[i - 1][k][r]);
                }
            }
        }
    }
    for(int i = 0; i <= n; i ++) 
        for(int j = 0; j <= m; j ++)
            for(int k = 0; k <= 2 * m + 5; k ++)
                dp2[i][j][k] = sum[i][j][k] = 0;
    dp2[0][0][0] = 1;
    sum[0][0][0] = 1;
    for(int i = 1; i <= m; i ++)
        sum[0][i][0] = 1;
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j <= m; j ++) {
            for(int k = j; k <= 2 * m; k ++) {
                /*
                for(int p = 0; p <= j; p ++)
                    add(dp2[i][j][k],dp2[i - 1][p][k - j]);*/
                
                add(dp2[i][j][k],sum[i - 1][j][k - j]); 
            }
        }
        for(int j = 0; j <= m; j ++) {
            for(int k = 0; k <= m * 2; k ++) {
                if(j) add(sum[i][j][k],sum[i][j - 1][k]);
                add(sum[i][j][k],dp2[i][j][k]);
            }
        }
    }
    int ans = 0;
    for(int j = 0; j <= m; j ++) add(ans,dp1[n][j][0]);
    for(int i = 0; i <= m; i ++)
        for(int j = 0; j <= 2 * m; j ++)
            if(2 * i > j && (j % 2) == 0)
                dec(ans,dp2[n][i][j]);
    cout << ans << endl;
}

int main()
{   
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case #%d: ",cas);
        solve();
    }
    return 0;
}

