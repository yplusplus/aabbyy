#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 100000007;
const int N = 52;
int n;
struct matrix
{
    int a[N][N];
    matrix() {
        memset(a,0,sizeof(a));
    }
    void init() {
        memset(a,0,sizeof(a));
    }
    matrix operator * (const matrix &p) {
        matrix c;
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
                for(int k = 0; k < n; k ++)
                    c.a[i][j] = (c.a[i][j] + (long long)a[i][k] * p.a[k][j]) % mod;
        return c;
    }
};

matrix pow(matrix T,int m)
{
    matrix B;
    for(int i = 0; i < n; i ++)
        B.a[i][i] = 1;
    while(m) {
        if(m & 1) B = B * T;
        T = T * T;
        m /= 2;
    }
    return B;
}

matrix T[65],A[65];

int main()
{
    int a[N][N],c[N][N],p[N];
    int m,s,t;
    while(scanf("%d%d%d%d",&n,&m,&s,&t) != EOF) {
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
                scanf("%d",&a[i][j]);
        for(int i = 0; i < n; i ++) {
            scanf("%d",&p[i]);
            for(int j = 0; j < p[i]; j ++)
                scanf("%d",&c[i][j]);
        }
        for(int times = 0; times < 60; times ++) {
            A[times].init();
            for(int i = 0; i < n; i ++) {
                A[times].a[i][i] = 1;
                if(i == t) continue;
                if(!c[i][times % p[i]]) continue;
                for(int j = 0; j < n; j ++) {
                    if(a[i][j]) A[times].a[i][j] = 1;
                }
            }
            if(times == 0) T[0] = A[0];
            else T[times] = T[times - 1] * A[times];
        }
        m --;
        if(m < 60) {
            cout << T[m].a[s][t] << endl;
            continue;
        }
        matrix ans = pow(T[59],m / 60) * T[m % 60];
        cout << ans.a[s][t] << endl;
    }
    return 0;
}
            
        

