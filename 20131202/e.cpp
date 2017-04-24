#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int dp[11][55][11][11];
char s[110];
int c[110][110];

void add(int &x,int y)
{
    x += y;
    if(x >= mod) x -= mod;
}

int main()
{
    for(int i = 0; i < 110; i ++) {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; j ++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    int bit[110];
    while(scanf("%s",s) != EOF) {
        memset(dp,0,sizeof(dp));
        int n = strlen(s);
        memset(bit,0,sizeof(bit));
        for(int i = 0; i < n; i ++)
            bit[s[i] - '0'] ++;
        dp[0][0][0][0] = 1;
        int even = n / 2;
        int tot = 0;
        for(int i = 0; i < 10; i ++) {
            for(int j = 0; j <= even && j <= tot; j ++) {
                for(int k = 0; k < 11; k ++) {
                    for(int r = 0; r < 11; r ++) {
                        if(!dp[i][j][k][r]) continue;
                        for(int p = 0; p <= even - j && p <= bit[i]; p ++) {
                            int x = n - even - (tot - j);
                            if(i == 0) x --;
                            if(x < 0 || x < bit[i] - p) continue;
                            add(dp[i + 1][j + p][(k + i * p) % 11][(r + i * (bit[i] - p)) % 11],dp[i][j][k][r] * 1LL * c[even - j][p] % mod * c[x][bit[i] - p] % mod);
                        }
                    }
                }
            }
            tot += bit[i];
        }
        int ans = 0;
        for(int i = 0; i < 11; i ++) add(ans,dp[10][even][i][i]);
        cout << ans << endl;
    }
    return 0;
}
    

