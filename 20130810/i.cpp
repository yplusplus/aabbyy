#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 1000000000;
int dp[12][210];
int a[] = {1000,20,20,20,25,25,30,30,1000};

int divv(int x,int y)
{
    if(!y) return oo;
    return x % y == 0 ? x / y : x / y + 1;
}

int main()
{
    int c[15];
    while(scanf("%d%d%d%d%d%d%d",&c[1],&c[2],&c[3],&c[4],&c[5],&c[6],&c[7]) != EOF) {
        bool flag = false;
        for(int i = 1; i <= 7; i ++)
            if(c[i]) flag = true;
        if(!flag) break;
        for(int i = 0; i <= 10; i ++)
            for(int j = 0; j <= 200; j ++)
                dp[i][j] = oo;
        dp[0][0] = 0;
        c[0] = c[8] = 0;
        for(int i = 0; i <= 7; i ++)
            for(int j = 0; j <= c[i]; j ++) {
                if(dp[i][j] == oo) continue;
                for(int k = 0; k <= c[i + 1]; k ++) {
                    dp[i + 1][c[i + 1] - k] = min(dp[i + 1][c[i + 1] - k],dp[i][j] + divv(j + k,min(a[i],a[i + 1])));
                }
            }
        printf("%d\n",dp[8][0]);
    }
    return 0;
}


