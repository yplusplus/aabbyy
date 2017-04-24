#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int mod = 100000000;
char s[110];
int dp[110][110][10][3];

void add(int &x,int y)
{
    x += y;
    if(x >= mod) x -= mod;
}

int cal(int bit[],int n)
{
    int m = strlen(s);
    reverse(bit,bit + n);
    /*
    for(int i = 0; i < n; i ++) cout << bit[i];
    cout << endl;*/
    memset(dp,0,sizeof(dp));
    for(int i = 1; i < 10; i ++) {
        if(i > bit[0]) dp[0][0][i][2] = 1;
        else if(i == bit[0]) dp[0][0][i][1] = 1;
        else dp[0][0][i][0] = 1;
    }
    for(int i = 0; i + 1 < n; i ++) {
        for(int j = 0; j <= i && j < m; j ++) {
            for(int k = 0; k < 10; k ++) {
                for(int r = 0; r < 10; r ++) {
                    if(s[j] == '-' && k != r) continue;
                    if(s[j] == '\\' && k <= r) continue;
                    if(s[j] == '/' && k >= r) continue;
                    if(j + 1 == m || (j + 1 < m && s[j] != s[j + 1])) {
                        add(dp[i + 1][j][r][0],dp[i][j][k][0]);
                        add(dp[i + 1][j][r][2],dp[i][j][k][2]);
                        if(r == bit[i + 1]) {
                            add(dp[i + 1][j][r][1],dp[i][j][k][1]);
                        }
                        else if(r > bit[i + 1]) {
                            add(dp[i + 1][j][r][2],dp[i][j][k][1]);
                        }
                        else add(dp[i + 1][j][r][0],dp[i][j][k][1]);
                    }
                        
                        add(dp[i + 1][j + 1][r][0],dp[i][j][k][0]);
                        add(dp[i + 1][j + 1][r][2],dp[i][j][k][2]);
                        if(r == bit[i + 1]) {
                            add(dp[i + 1][j + 1][r][1],dp[i][j][k][1]);
                        }
                        else if(r > bit[i + 1]) {
                            add(dp[i + 1][j + 1][r][2],dp[i][j][k][1]);
                        }
                        else 
                            add(dp[i + 1][j + 1][r][0],dp[i][j][k][1]);                    
                }
            }
        }
    }
    /*
    for(int i = 1; i < n; i ++)
        for(int k = 0; k <= m; k ++)
            for(int j = 0; j < 10; j ++)
                if(dp[i][k][j][1]) cout << i << " " << j << " " << k << " : " << dp[i][k][j][1] << endl;*/
    int ans = 0;
    for(int i = m; i < n; i ++) {
        for(int j = 0; j < 10; j ++)
            for(int k = 0; k < 3; k ++) {
                if(i == n - 1 && k == 2) continue;
                add(ans,dp[i][m][j][k]);
                /*
                if(i == n - 1 && dp[i][m][j][k])
                    cout << i << " " << j << " " << k << " : " << dp[i][m][j][k] << endl;*/
            }
    }
    //cout << ans << endl;
    return ans;
}
        
    
int solvea(char *str)
{
    int pos = -1;
    int n = strlen(str),m = 0;
    for(int i = 0; i < n; i ++)
        if(str[i] != '0') {
            pos = i;
            break;
        }
    if(pos == -1) return 0;
    int ct = 0;
    for(int i = pos; i < n; i ++)
        str[ct ++] = str[i];
    str[ct] = 0;
    int a[110];
    memset(a,0,sizeof(a));
    for(int i = 0; i < ct; i ++) {
        a[i] = str[ct - i - 1] - '0';
    }
    a[0] --;
    for(int i = 0; i < ct; i ++)
        if(a[i] < 0) {
            a[i] += 10;
            a[i + 1] --;
        }
    while(ct && !a[ct - 1]) ct --;
    if(ct == 0) return 0;
//    cout << str << endl;
    return cal(a,ct);
}
        
int solveb(char *str)
{
    int pos = -1;
    int n = strlen(str),m = 0;
    for(int i = 0; i < n; i ++)
        if(str[i] != '0') {
            pos = i;
            break;
        }
    if(pos == -1) return 0;
    int ct = 0;
    for(int i = pos; i < n; i ++)
        str[ct ++] = str[i];
    str[ct] = 0;
    int a[110];
    memset(a,0,sizeof(a));
    for(int i = 0; i < ct; i ++) {
        a[i] = str[ct - i - 1] - '0';
    }
//    cout << str << endl;
    return cal(a,ct);
}

int main()
{
    char sa[1010],sb[1010];
    while(scanf("%s",s) != EOF) {
        scanf("%s%s",sa,sb);
        int ans = solveb(sb) - solvea(sa);
        if(ans < 0) ans += mod;
        printf("%08d\n",ans);
    }
    return 0;
}
