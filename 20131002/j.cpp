#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int dp[12][10][3];
int bit[15];
 
int cal(int n)
{
    if(!n) return 0;
    int len = 0;
    if(n < 10) return n;
    while(n) {
        bit[++ len] = n % 10;
        n /= 10;
    }
    for(int i = 0; i <= len; i ++)
        for(int j = 0; j < 10; j ++)
            for(int k = 0; k < 3; k ++)
                dp[i][j][k] = 0;
    reverse(bit + 1,bit + len + 1);
    for(int i = 1; i <= 9; i ++)
        if(i == bit[1]) dp[1][i][1] ++;
        else if(i > bit[1]) dp[1][i][2] ++;
        else dp[1][i][0] ++;
    for(int i = 1; i < len; i ++)
        for(int j = 0; j < 10; j ++) {
            if(!(dp[i][j][0] + dp[i][j][1] + dp[i][j][2])) continue;
            for(int k = 0; k < 10; k ++) {
                if(k && j && k == j) continue;
                int newbit = k;
                dp[i + 1][newbit][0] += dp[i][j][0];
                dp[i + 1][newbit][2] += dp[i][j][2];
                if(k == bit[i + 1]) dp[i + 1][newbit][1] += dp[i][j][1];
                else if(k > bit[i + 1]) dp[i + 1][newbit][2] += dp[i][j][1];
                else dp[i + 1][newbit][0] += dp[i][j][1];
            }
        }
    int ans = 0;
    for(int i = 1; i <= len; i ++)
        for(int j = 0; j < 10; j ++)
            for(int k = 0; k < 3; k ++)
                if(i == len && k == 2) continue;
                else ans += dp[i][j][k];
    return ans;
}
 
int f[10010],bt[10010];
int main()
{
    int ct = 0;
    for(int i = 0; i <= 100000000; i += 10000) {
        bt[++ ct] = i;
        f[ct] = cal(i);
    }
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        while(n >= 100000000) cout << "wrong data" << endl;
        if(n < 0) {
            printf("0\n");
            continue;
        }
        int tot = cal(n);
        int x = 1,y = ct,mid,xx;
        while(x <= y) {
            mid = (x + y) / 2;
            if(f[mid] >= tot + 1) {
                xx = mid;
                y = mid - 1;
            }
            else x = mid + 1;
        }
        int lt = max(n + 1,bt[xx - 1]),rt = bt[xx],ans;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(cal(mid) - tot >= 1) {
                ans = mid;
                rt = mid - 1;
            }
            else lt = mid + 1;
        }
        printf("%d\n",ans);
    }
    return 0;
}

