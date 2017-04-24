#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#define gcc 10007
#define MAX ((INT)1 << 63) - 1

using namespace std;

typedef unsigned long long INT;

INT p[10] = {2,3,5,7,11,13,17,19,23,29};
inline INT gcd(INT a,INT b)
{
    INT m = 1;
    if(!b) return a;
    while(m) {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}

inline INT multi_mod(INT a,INT b,INT mod)
{
    INT sum = 0;
    while(b) {
        if(b & 1) sum = (sum + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return sum;
}

inline INT quickmod(INT a,INT b,INT mod)
{
    INT sum = 1;
    while(b) {
        if(b & 1) sum = multi_mod(sum,a,mod);
        a = multi_mod(a,a,mod);
        b >>= 1;
    }
    return sum;
}

bool miller_rabin(INT n)
{
    int i,j,k = 0;
    INT u,m,buf;
    if(n == 2) return true;
    if(n < 2 || !(n & 1)) return false;
    m = n - 1;
    while(!(m & 1)) k ++, m >>= 1;
    for(i = 0; i < 9; i ++) {
        if(p[i] >= n) return true;
        u = quickmod(p[i],m,n);
        if(u == 1) continue;
        for(j = 0; j < k; j ++) {
            buf = multi_mod(u,u,n);
            if(buf == 1 && u != 1 && u != n - 1) return false;
            u = buf;
        }
        if(u - 1) return false;
    }
    return true;
}

INT pollard(INT n)
{
    INT i = 1;
    INT x = rand() % (n - 1) + 1;
    INT y = x;
    INT k = 2;
    INT d;
    do {
        i ++;
        d = gcd(n + y - x,n);
        if(d > 1 && d < n) return d;
        if(i == k) y = x,k *= 2;
        x = (multi_mod(x,x,n) + n - gcc) % n;
    }while(y != x);
    return n;
}

INT MIN;
INT pollard_min(INT n)
{
    INT p,a,b = MAX;
    if(n == 1) return MAX;
    if(miller_rabin(n)) return n;
    p = pollard(n);
    a = pollard_min(p);
    INT y = n / p;
    b = pollard_min(y);
    return a < b ? a : b;
}

int main()
{
    ios::sync_with_stdio(0);
    INT n;
    while(cin >> n) {
        if(n <= 5) {
            cout << "is not a D_num" << endl;
            continue;
        }
        INT a = pollard_min(n);
        if(a == n || a > 1000000) {
            cout << "is not a D_num" << endl;
            continue;
        }
        if(a * a * a == n) {
            cout << a << " " << a * a << " " << a * a * a << endl;
            continue;
        }
        INT b = n / a;
        if(!miller_rabin(b) || a == b) {
            cout << "is not a D_num" << endl;
            continue;
        }
        cout << a << " " << b << " " <<  a * b << endl;
    }
    return 0;
}