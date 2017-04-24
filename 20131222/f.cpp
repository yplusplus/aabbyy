#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

float f[1 << 15],dp[1 << 15];
float a[25][5];
float mask[1 << 15][5];
float msk[1 << 15][8];
int rev[1 << 15];
int lowbit(int x)
{
    return x & (-x);
}

void solve()
{
    for(int i = 0; i < 15; i ++)
        rev[1 << i] = i;
    int n;
    scanf("%d",&n);
    for(int i = 0; i < 3; i ++) scanf("%f",&a[n][i]);
    a[n][3] = a[n][0];
    a[n][4] = a[n][1];
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < 3; j ++)
            scanf("%f",&a[i][j]);
        a[i][3] = a[i][0];
        a[i][4] = a[i][1];
    }
    mask[0][0] = mask[0][1] = mask[0][2] = mask[0][3] = mask[0][4] = 1;
    for(int i = 1; i < (1 << n); i ++) {
        int x = rev[lowbit(i)];
        for(int k = 0; k < 3; k ++)
            mask[i][k] = mask[i ^ lowbit(i)][k] * a[x][k];
        mask[i][3] = mask[i][0];
        mask[i][4] = mask[i][1];
    }
    for(int i = 0; i < (1 << n); i ++)
        for(int j = 0; j < 8; j ++)
            msk[i][j] = 0;
    for(int i = 0; i < 3; i ++)
        msk[0][1 << i] = a[n][i];
    for(int i = 1; i < (1 << n); i ++) {
        int x = rev[lowbit(i)];
        for(int k = 0; k < 8; k ++) {
            for(int j = 0; j < 3; j ++) {
                msk[i][k | (1 << j)] += msk[i ^ (1 << x)][k] * a[x][j];
            }
        }
    }
    f[0] = 1;
    for(int i = 1; i < (1 << n); i ++) {
        float tmp, p = 0;
        float tot = 0;
        for(int j = i; j; j = (j - 1) & i) {
            tmp = mask[j][0] * a[n][1] * mask[i ^ j][1] + mask[j][1] * a[n][2] * mask[i ^ j][2] + mask[j][2] * a[n][3] * mask[i ^ j][3];
            tot += tmp * f[i ^ j];
            //p += tmp;
            //p += mask[j][1] * a[n][0] * mask[i ^ j][0] + mask[j][2] * a[n][1] * mask[i ^ j][1] + mask[j][3] * a[n][2] * mask[i ^ j][2];
        }
        p = msk[i][7] + msk[i][1] + msk[i][2] + msk[i][4];
        f[i] = tot / (1 - p);
    }
    dp[0] = max(a[n][1] / (1 - a[n][0]),a[n][2] / (1 - a[n][1]));
    dp[0] = max(dp[0],a[n][3] / (1 - a[n][2]));
    for(int i = 1; i < (1 << n); i ++) {
        float maxn = 0;
        for(int j = 1; j <= 3; j ++) {
            float p = 0,tot = 0;
            for(int k = i; ; k = (k - 1) & i) {
                if(k) {
                    tot += mask[k][j - 1] * a[n][j] * mask[k ^ i][j] * dp[k ^ i];
                    //p += mask[k][j - 1] * a[n][j] * mask[k ^ i][j];
                    //p += mask[k][j + 1] * a[n][j] * mask[k ^ i][j];
                }
                tot += mask[k][j] * a[n][j + 1] * mask[k ^ i][j + 1] * f[k ^ i];
                //p += mask[k][j] * a[n][j + 1] * mask[k ^ i][j + 1];
                //p += mask[k][j] * a[n][j - 1] * mask[k ^ i][j - 1];
                if(!k) break;                
            }
            for(int k = 0; k < 8; k ++) {
                int x = k | (1 << (j == 3 ? 0 : j));
                if(x == 7 || x == 1 || x == 2 || x == 4) p += msk[i][k];
            }
            maxn = max(maxn,tot / (1 - p));    
        }
        dp[i] = maxn;
    }
    printf("%.10f\n",dp[(1 << n) - 1]);
}
        
int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
    }
    return 0;
}

