#include <bits/stdc++.h>
using namespace std;

const long long mod = 10;
long long tot;
int r[4],c[4];

void dfs(int x,int y,int used,int left)
{
    if(y == 4) x ++,y = 0;
    if(x == 4) {
        if(!left) tot ++;
        return;
    }
    if(16 - (4 * x + y) == left) {
        tot ++;
        return;
    }
    for(int i = 0; i < used; i ++) {
        if(c[y] & (1 << i)) continue;
        if(r[x] & (1 << i)) continue;
        c[y] |= (1 << i);
        r[x] |= (1 << i);
        dfs(x,y + 1,used,left);
        c[y] ^= (1 << i);
        r[x] ^= (1 << i);
    }
    if(left) {
        r[x] |= (1 << used);
        c[y] |= (1 << used);
        dfs(x,y + 1,used + 1,left - 1);
        r[x] ^= (1 << used);
        c[y] ^= (1 << used);
    }
}

struct bignum
{
    int len;
    unsigned long long a[2000];
    bignum() {
        memset(a,0,sizeof(a));
        len = 0;
    }

    void operator += (const bignum &p) {
        len = max(len,p.len);
        for(int i = 0; i < len; i ++)
            a[i] += p.a[i];
        for(int i = 0; i < len; i ++)
            if(a[i] >= mod) {
                a[i + 1] ++;
                a[i] -= mod;
            }
        if(a[len]) len ++;
    }

    void sqr() {
        bignum c;
        for(int i = 0; i < len; i ++)
            for(int j = 0; i + j < 2000 && j < len; j ++)
                c.a[i + j] += a[i] * a[j];
        for(int i = 0; i < 1999; i ++) {
            c.a[i + 1] += c.a[i] / mod;
            c.a[i] %= mod;
        }
        for(int i = 0; i < 2000; i ++) a[i] = c.a[i];
        len = 1999;
        while(len && !a[len - 1]) len --;
    }

    void operator *= (const long long x) {
        for(int i = 0; i < len; i ++) a[i] *= x;
        for(int i = 0; i < len + 20; i ++) {
            if(a[i] >= mod) {
                a[i + 1] += a[i] / mod;
                a[i] %= mod;
            }
        }
        len += 20;
        while(len && !a[len - 1]) len --;
    }

    void init(long long x) {
        a[0] = x;
        len = 20;
        for(int i = 0; i < len; i ++) {
            a[i + 1] += a[i] / mod;
            a[i] %= mod;
        }
        while(len && !a[len - 1]) len --;
    }

    void output() {
        for(int i = len - 1; i >= 0; i --) printf("%llu",a[i]);
        if(!len) printf("0\n");
        else printf("\n");
    }
};

long long dp[25];

bignum com(long long n,int x)
{
    long long a[25];
    for(int i = 1; i <= x; i ++) {
        a[i] = n - i + 1;
    }
    for(int i = 2; i <= x; i ++) {
        long long y = i;
        for(int j = 1; j <= x && y != 1; j ++) {
            long long d = __gcd(y,a[j]);
            y /= d;
            a[j] /= d;
        }
    }
    bignum ans;
    ans.a[0] = 1;
    ans.len = 1;
    for(int i = 1; i <= x; i ++) ans *= a[i];
    return ans;
}

void solve()
{
    bignum ans;
    long long n;
    scanf("%lld",&n);
    for(int i = 4; i <= n && i <= 16; i ++) {
        bignum tmp = com(n,i);
        tmp *= dp[i];
        ans += tmp;
    }
    ans.sqr();
    ans.sqr();
    ans.output();
}

int main()
{
    double times1 = 1.0 * clock() / CLOCKS_PER_SEC;
    for(int i = 4; i <= 16; i ++) {
        memset(r,0,sizeof(r));
        memset(c,0,sizeof(c));
        tot = 0;
        dfs(0,0,0,i);
        //cout << i << " : " << ans << " ";
        for(int j = 2; j <= i; j ++) tot *= j;
        dp[i] = tot;
    }
    int t;
    scanf("%d",&t);
    while(t --) solve();
    double times2 = 1.0 * clock() / CLOCKS_PER_SEC;
    //printf("%.10lf\n",times2 - times1);
    return 0;
}
