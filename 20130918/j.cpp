#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 1000000000;
const int N = 2010;
int dp[N][N][2];
int maxn[N][N];
int a[N];

void init(int n)
{
    for(int i = 1; i <= n; i ++) {
        maxn[i][i] = a[i];
        for(int j = i + 1; j <= n; j ++) {
            maxn[i][j] = max(maxn[i][j - 1],a[j]);
        }
    }
}

void update(int &x,int y)
{
    x = min(x,y);
}

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF) {
        int number = 0;
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&a[i]);
            number += a[i];
        }
        int tot = 0;
        for(int i = m + 2; i <= n - m; i ++)
           a[++ tot] = a[i];
        n = tot; 
        if(!n) {
            printf("%d\n",number);
            continue;
        }
        init(n);
        for(int i = 0; i <= n; i ++)
            for(int j = 0; j <= n; j ++)
                dp[i][j][0] = dp[i][j][1] = oo;
        dp[0][0][0] = dp[0][0][1] = 0;
        for(int i = 1; i <= n; i ++) {
            for(int j = 0; j <= i; j ++) {
                if(j) {
                    update(dp[j][i - j][0],dp[j - 1][i - j][0] + maxn[j][n - (i - j)]);
                    update(dp[j][i - j][0],dp[j - 1][i - j][1] + maxn[j][n - (i - j)] * i);
                }
                if(i - j) {
                    update(dp[j][i - j][1],dp[j][i - j - 1][1] + maxn[j + 1][n - (i - j - 1)]);
                    update(dp[j][i - j][1],dp[j][i - j - 1][0] + maxn[j + 1][n - (i - j - 1)] * i);
                }
            }
        }
        int ans = oo;
        for(int i = 0; i <= n; i ++) {
            update(ans,min(dp[i][n - i][0],dp[i][n - i][1]));
        }
        printf("%d\n",ans + number);
    }
    return 0;
}

