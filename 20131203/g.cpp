#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
long long dp[N][4];
int a[N][3];

void update(long long &x,long long y)
{
    x = max(x,y);
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF) {
        for(int i = 1; i <= n; i ++)
            scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);
        if(n == 1) {
            cout << max(0,a[1][0]) << endl;
            continue;
        }
        for(int i = 0; i < n + 5; i ++)
            for(int j = 0; j < 4; j ++)
                dp[i][j] = -1LL << 60;
        for(int i = 0; i < 4; i ++) {
            if(i == 0) dp[2][i] = 0;
            else if(i == 1) dp[2][i] = a[1][0];
            else if(i == 2) dp[2][i] = 0;
            else dp[2][i] = a[1][1];
        }
        for(int i = 2; i < n; i ++) {
            for(int j = 0; j < 4; j ++) {
                for(int k = 0; k < 2; k ++) {
                    int state = (j << 1) + k;
                    state >>= 1;
                    if(j & 2) {
                        int cc = 0;
                        if(j & 1) cc ++;
                        if(k) cc ++;
                        update(dp[i + 1][state],dp[i][j] + a[i][cc]); 
                    }
                    else update(dp[i + 1][state],dp[i][j]);
                }
                            
            }
        }
        dp[n][2] += a[n][0];
        dp[n][3] += a[n][1];
        long long ans = -1LL << 60;
        for(int i = 0; i < 4; i ++) update(ans,dp[n][i]);
        cout << ans << endl;
    }
    return 0;
}



