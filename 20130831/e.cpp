#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 10000;
int size = 6;

struct matrix
{
    int a[6][6];
    matrix () {
        memset(a,0,sizeof(a));
    }
    matrix operator * (const matrix &p) {
        matrix c;
        for(int i = 0; i < size; i ++)
            for(int j = 0; j < size; j ++)
                for(int k = 0; k < size; k ++)
                    c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
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
    int t,n;
    int cas = 0;
    while(scanf("%d",&n) != EOF) {
        matrix a;
        a.a[0][1] = 3,a.a[0][2] = 2,a.a[0][3] = 1;
        a.a[1][0] = a.a[2][1] = a.a[3][2] = a.a[4][3] = a.a[5][4] = 1;
        printf("Case %d: ",++ cas);
        if(n == 0) {
            printf("2\n");
            continue;
        }
        a = pow(n,a);
        int sum = 0;
        for(int i = 0; i < size; i ++)
            sum += a.a[i][0];
        sum %= 10000;
        cout << sum * 2 % 10000 << endl;
    }
    return 0;
}


