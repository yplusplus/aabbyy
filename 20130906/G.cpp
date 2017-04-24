#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long mod;
int fac[55],cnt,num[55];

void factor(long long n)
{
    cnt = 0;
    memset(num,0,sizeof(num));
    for(long long i = 2; i * i <= n; i ++) {
        if(n % i) continue;
        while(n % i == 0) n /= i,num[cnt] ++;
        fac[cnt ++] = i;
    }
    if(n > 1) {
        num[cnt] = 1;
        fac[cnt ++] = n;
    }
}

long long gcd,tot;

long long cal(long long n)
{
    long long x = n,y = n + 1;
    if(x % 2 == 0) x /= 2;
    else y /= 2;
    return (x % mod) * (y % mod) % mod;
}

void dfs(int pos,long long x,long long phi,int flag)
{
    if(flag) {
        gcd = (gcd + (phi % mod) * ((tot / x) % mod)) % mod;
    }
    if(pos == cnt) return;
    dfs(pos + 1,x,phi,0);
    long long y = x,tphi = phi;
    for(int i = 0; i < num[pos]; i ++) {
        if(i == 0) tphi *= (fac[pos] - 1);
        else tphi *= fac[pos];
        y *= fac[pos];
        dfs(pos + 1,y,tphi,1);
    }
}
    
    
long long get_gcd(long long n)
{
    tot = n;
    gcd = 0;
    dfs(0,1,1,1);
//    cout << gcd << endl;
    return gcd;
}

long long lcm;
long long cal(long long x,long long y)
{
    if(x == y && x == 1) return 1;
    if(x % 2) y /= 2;
    else x /= 2;
    return (x % mod) * (y % mod) % mod;
}

void ddfs(int pos,long long x,long long phi,int step,int flag)
{
    if(flag) {
        lcm = (lcm + tot % mod * cal(x,phi)) % mod;
        //cout << tot << " " << x << " " << phi << endl;
        //cout << x << " " << phi << " " << lcm << endl;
    }
    if(pos == cnt) return;
    ddfs(pos + 1,x,phi,step,0);
    long long y = x,tphi = phi;
    for(int i = 0; i < num[pos]; i ++) {
        if(i == 0) tphi *= (fac[pos] - 1);
        else tphi *= fac[pos];
        y *= fac[pos];
        ddfs(pos + 1,y,tphi,step,1);
    }
}

long long get_lcm(long long n)
{
    tot = n;
    lcm = 0;
    ddfs(0,1,1,1,1);
  //  cout << lcm << endl;
    return lcm;
}

int main()
{
    ios::sync_with_stdio(0);
    long long n;
    int t;
    cin >> t;
    while(t --) {
        cin >> n >> mod;
        if(n == 1) {
            cout << "yes" << endl;
            continue;
        }
        factor(n);
        long long x = get_gcd(n);
        long long y = get_lcm(n);
        if((y - x) % mod == 0) cout << "yes" << endl;
        else cout << "no" << endl;
        /*
        long long ansx = 0,ansy = 0;
        for(long long i = 1; i <= n; i ++) {
            ansx += i * n / __gcd(i,n);
            ansy += __gcd(i,n);
        }
        cout << ansx << " " << ansy << endl;*/
    }
    return 0;
}

