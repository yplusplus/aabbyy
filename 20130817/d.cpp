#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long dp[15][3],sum[15][3];
long long bit[15];

long long cal(long long n)
{
    if(!n) return 0;
    int len = 0;
    while(n) {
        bit[++ len] = n % 10;
        n /= 10;
    }
    reverse(bit + 1,bit + len + 1);
    memset(dp,0,sizeof(dp));
    memset(sum,0,sizeof(sum));
    for(int i = 1; i < 10; i ++) {
        if(i == bit[1]) {
            sum[1][1] ++;
            dp[1][1] += i;
        }
        else if(i > bit[1]) {
            sum[1][2] ++;
            dp[1][2] += i;
        }
        else {
            sum[1][0] ++;
            dp[1][0] += i;
        }
    }
    for(int i = 1; i < len; i ++)
        for(int j = 0; j < 10; j ++) {
            dp[i + 1][0] += dp[i][0] + sum[i][0] * j;
            sum[i + 1][0] += sum[i][0];
            dp[i + 1][2] += dp[i][2] + sum[i][2] * j;
            sum[i + 1][2] += sum[i][2];
            if(j == bit[i + 1]) {
                dp[i + 1][1] += dp[i][1] + sum[i][1] * j;
                sum[i + 1][1] += sum[i][1];
            }
            else if(j > bit[i + 1]) {
                dp[i + 1][2] += dp[i][1] + sum[i][1] * j;
                sum[i + 1][2] += sum[i][1];
            }
            else {
                dp[i + 1][0] += dp[i][1] + sum[i][1] * j;
                sum[i + 1][0] += sum[i][1];
            }
        }
    long long ans = 0;
    for(int i = 1; i <= len; i ++)
        if(i < len)
            for(int j = 0; j < 3; j ++)
                ans += dp[i][j];
        else ans += dp[i][1] + dp[i][0];
    return ans;
}

int main()
{
    int n,m;
    ios::sync_with_stdio(0);
    while(cin >> n >> m) {
        if(!n && !m) break;
        cout << cal(m) - cal(n - 1) << endl;
    }
    return 0;
}


