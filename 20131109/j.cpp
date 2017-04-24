#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 210;
const int mod = 1000000007;
long long c[N][N],fac[N];
int f[N][N][N],cc[N][N][N];
int rev2 = 500000004;
long long p2[N];
void add(int &x,int y)
{
    x += y;
    if(x >= mod) x -= mod;
}

int main()
{
    memset(c,0,sizeof(c));
    memset(f,0,sizeof(f));
    memset(cc,0,sizeof(cc));
    fac[0] = p2[0] = 1;
    for(int i = 1; i < N; i ++) {
        fac[i] = fac[i - 1] * i % mod;
        p2[i] = p2[i - 1] * rev2 % mod;
    }
    for(int i = 0; i < N;i ++) {
        c[i][i] = c[i][0] = 1;
        for(int j = 1; j < i; j ++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    for(int i = 0; i <= 200; i ++) {
        for(int j = 0; i + 2 * j <= 200; j ++) {
            for(int k = 0; i + 2 * j + 2 * k <= 200; k ++) {
                int n = i + j + 2 * k,m = i + 2 * j + k;
                long long tmp = c[n][i] * c[n - i][j] % mod;
                tmp = tmp * fac[i] % mod;
                tmp = tmp * c[m][i] % mod * c[m - i][j * 2] % mod;
                tmp = tmp * fac[2 * j] % mod * p2[j] % mod;
                tmp = tmp * fac[2 * k] % mod * p2[k] % mod;
                add(f[i + 2 * j + 2 * k][n][m],tmp);
            }
        }
    }
    
    for(int i = 0; i <= 200; i ++)
        for(int j = i; j <= 200; j ++)
            for(int k = i; k <= 200; k ++) {
                long long tmp = c[j][i] * c[k][i] % mod * fac[i] % mod;
                add(cc[i][j][k],tmp);
            }    
    for(int i = 1; i <= 200; i ++)
        for(int j = 0; j <= 200; j ++)
            for(int k = 0; k <= 200; k ++) {
                add(f[i][j][k],f[i - 1][j][k]);
                add(cc[i][j][k],cc[i - 1][j][k]);
            }
                
    int  t,n,m,p,q;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d%d%d",&n,&m,&p,&q);
        long long ans = 0;
        for(int i = 0; i <= n; i ++)
            for(int j = 0; j <= m; j ++)
                ans = (ans + (long long)f[p][i][j] * cc[q][n - i][m - j] % mod * c[n][i] % mod * c[m][j]) % mod;
        ans --;
        if(ans < 0) ans += mod;
        cout << ans << endl;
    }
    return 0;
}



