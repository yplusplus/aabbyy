#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long mod = 1000000007;
struct matrix
{
    long long a[4][4];
    matrix operator * (const matrix &p) {
        matrix c;
        memset(c.a,0,sizeof(c.a));
        for(int i = 0; i < 4; i ++)
            for(int j = 0; j < 4; j ++)
                for(int k = 0; k < 4; k ++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
                }
        return c;
    }
};

matrix pow(int n,matrix t)
{
    if(n == 1) return t;
    if(n & 1) return pow(n / 2,t * t) * t;
    return pow(n / 2,t * t);
}

int main()
{
    int t,n,m;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d",&n,&m);
        if(n < m) {
            printf("0\n");
            continue;
        }
        n -= m;
        ++ n;
        if(n == 1) {
            printf("1\n");
            continue;
        }
        if(n == 2) {
            printf("2\n");
            continue;
        }
        if(n == 3) {
            printf("5\n");
            continue;
        }
        matrix a;
        memset(a.a,0,sizeof(a.a));
        a.a[0][0] = 2;
        a.a[0][1] = 2;
        a.a[1][1] = 2;
        a = pow(n - 3,a);
        long long ans = (a.a[0][0] * 5 + a.a[0][1]) % mod;
        printf("%I64d\n",ans);
    }
    return 0;
}

