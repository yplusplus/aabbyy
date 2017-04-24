#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

map<long long, int> ma;

long long pow(long long a,long long b,long long c)
{
    long long ans = 1;
    while(b) {
        if(b & 1LL) ans = ans * a % c;
        a = a * a % c;
        b /= 2LL;
    }
    return ans % c;
}

long long x,y;
long long ex_gcd(long long a,long long b)
{
    if(b == 0) {
        x = 1,y = 0;
        return a;
    }
    long long d = ex_gcd(b,a % b);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return d;
}

long long inv(long long a,long long b)
{
    ex_gcd(a,b);
    x %= b;
    if(x <= 0) x += b;
    while(x * a % b != 1) cout << "wrong inverse" << endl;
    return x;
}

long long babystep_giantstep(long long a,long long b,long long n)
{
    long long m = ceil(sqrt(n * 1.0));
    long long x = 1;
    ma.clear();
    for(int i = 0; i < m; i ++) {
        if(!ma.count(x)) ma[x] = i;
        x = x * a % n;
        //cout << x << endl;
    }
    long long y = inv(x,n);
    x = 1;
    for(int i = 0; i < m; i ++) {
        long long tmp = x * b % n;
        if(ma.count(tmp)) return i * m + ma[tmp];
        x = x * y % n;
    }
    return -1;
}
        
long long ex_babystep_giantstep(long long a,long long b,long long n)
{
    for(int i = 0; i <= 100; i ++)
        if(pow(a,i,n) == b) return i;
    long long c = 0,x = 1;
    while(1) {
        long long d = __gcd(a,n);
        if(d == 1) break;
        if(b % d) return -1;
        b /= d;
        n /= d;
        x = x * (a / d) % n;
        c ++;
    }
    b = b * inv(x,n) % n;
    long long ans = babystep_giantstep(a,b,n);
    if(ans == -1) return ans;
    return ans + c;
}

long long get_phi(long long n)
{
    long long ans = n;
    for(long long i = 2; i * i <= n; i ++) {
        if(n % i) continue;
        while(n % i == 0) {
            n /= i;
        }
        ans = ans / i * (i - 1);
    }
    if(n > 1) ans = ans / n * (n - 1); 
    return ans;
}

int main()
{
    long long a,b,n,m;
    while(cin >> a >> n >> b >> m) {
        long long ans = ex_babystep_giantstep(a,b,n);
        if(ans == -1 || ans > m) printf("0\n"); 
        else {
            long long phi = get_phi(n);
            if(pow(a,ans + phi,n) != b) cout << 1 << endl;
            else {
                long long minx = phi;
                for(long long i = 1; i * i <= phi; i ++) {
                    if(phi % i) continue;
                    if(pow(a,ans + i,n) == b) {
                        minx = min(minx,i);
                    }
                    if(pow(a,ans + phi / i,n) == b) {
                        minx = min(minx,phi / i);
                    }
                }
                unsigned long long tot = (unsigned long long)(m - ans) / minx + 1;
                cout << tot << endl;
            }
        }
    }
    return 0;
}



