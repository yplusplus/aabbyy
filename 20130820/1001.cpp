#pragma comment(linker, "/STACK:10006777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long mod = 1000000007;
struct matrix
{
    long long a[7][7];
    matrix() {
        memset(a,0,sizeof(a));
    }
    matrix operator * (const matrix &p) {
        matrix c;
        for(int i = 0; i < 7; i ++)
            for(int j = 0; j < 7; j ++)
                if(a[i][j])
                for(int k = 0; k < 7; k ++)
                    c.a[i][k] = (c.a[i][k] + a[i][j] * p.a[j][k]) % mod;
        return c;
    }
};

matrix pow(long long n,matrix t)
{
    if(n == 1) return t;
    if(n & 1LL) return pow(n / 2,t * t) * t;
    return pow(n / 2,t * t);
}
    
int main()
{
    int a0,ax,ay,b0,bx,by;
    long long n;
    while(scanf("%I64d",&n) != EOF) {
        scanf("%d%d%d",&a0,&ax,&ay);
        scanf("%d%d%d",&b0,&bx,&by);
        a0 %= mod,b0 %= mod;
        ax %= mod,ay %= mod;
        bx %= mod,by %= mod;
        if(n == 0) {
            printf("0\n");
            continue;
        }
        if(n == 1) {
            printf("%I64d\n",1LL * a0 * b0 % mod);
            continue;
        }
        matrix a;
        a.a[0][0] = 1;
        a.a[0][1] = a.a[1][1] = 1LL * ax * bx % mod;
        a.a[0][2] = a.a[1][2] = 1LL * ax * by % mod;
        a.a[0][3] = a.a[1][3] = 1LL * ay * bx % mod;
        a.a[0][4] = a.a[1][4] = 1;
        a.a[4][4] = a.a[5][5] = a.a[6][6] = 1;
        a.a[2][2] = ax;
        a.a[2][5] = 1;
        a.a[3][3] = bx;
        a.a[3][6] = 1;
        a = pow(n - 1,a);
        long long ans = 1LL * a0 * b0 % mod * a.a[0][0] % mod + 1LL * a0 * b0 % mod * a.a[0][1] + 
            a.a[0][2] * a0 % mod + a.a[0][3] * b0 % mod + 1LL * ay * by % mod * a.a[0][4] + a.a[0][5] * ay % mod + a.a[0][6] * by % mod;
        ans %= mod;
        printf("%I64d\n",ans);
    }
    return 0;
}

