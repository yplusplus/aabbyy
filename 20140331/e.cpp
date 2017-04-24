#include <bits/stdc++.h>
using namespace std;

struct bignum
{
    int a[110];
    bignum() {
        memset(a,0,sizeof(a));
    }
    bignum operator / (int x) {
        bignum c;
        memcpy(c.a,a,sizeof(a));
        int tmp = 0;
        for(int i = 105; i >= 0; i --) {
            int temp = (10 * tmp + c.a[i]) % x;
            c.a[i] = (10 * tmp + c.a[i]) / x;
            tmp = temp;
        }
        return c;
    }
    bool zero() {
        for(int i = 0; i < 110; i ++) if(a[i]) return false;
        return true;
    }
    bignum operator - (int x) {
        bignum c;
        memcpy(c.a,a,sizeof(a));
        c.a[0] -= x;
        for(int i = 0; i < 110; i ++)
            if(c.a[i] < 0) {
                c.a[i] += 10;
                c.a[i + 1] --;
            }
        return c;
    }
};

int mod,size;
struct matrix
{
    int a[1 << 5][1 << 5];
    matrix() {
        memset(a,0,sizeof(a));
    }
    matrix operator * (const matrix &p) {
        matrix c;
        for(int i = 0; i < size; i ++) {
            for(int j = 0; j < size; j ++) {
                for(int k = 0; k < size; k ++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
                }
            }
        }
        return c;
    }
};

matrix pow(matrix a,bignum n)
{
    matrix b;
    for(int i = 0; i < size; i ++) b.a[i][i] = 1;
    while(!n.zero()) {
        if(n.a[0] & 1) b = b * a;
        a = a * a;
        n = n / 2;
    }
    return b;
}

bool check(int state1,int state2,int m)
{
    if(m == 1) return true;
    int a[6],b[6];
    for(int i = 0; i < m; i ++) {
        if(state1 & (1 << i)) a[i] = 1;
        else a[i] = 0;
        if(state2 & (1 << i)) b[i] = 1;
        else b[i] = 0;
    }
    for(int i = 0; i < m - 1; i ++)
        if(a[i] == b[i] && a[i + 1] == b[i + 1] && a[i] == a[i + 1]) return false;
    return true;
}

void solve()
{
    char s[110];
    int m;
    scanf("%s%d%d",s,&m,&mod);
    size = (1 << m);
    bignum n;
    int len = strlen(s);
    for(int i = 0; i < len; i ++) n.a[i] = s[len - i - 1] - '0';
    n = n - 1;
    if(n.zero()) {
        printf("%d",size % mod);
        puts("");
        return;
    }
    matrix a;
    for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++)
            if(check(i,j,m)) {
                a.a[i][j] = 1;
            }
    a = pow(a,n);
    int ans = 0;
    for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++)
            ans = (ans + a.a[i][j]) % mod;
    printf("%d",ans);
    puts("");
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
        if(t) puts("");
    }
    return 0;
}
        
