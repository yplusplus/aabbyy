//construct a function : f(x) = (x - 1) * (x - 2) * ... * (x - Fib(k)) = x^k + a1 * x^(k - 1) + .. + ak * x^0
//obvious f(1) = ... f(Fib(k)) = 0
//c1 * f(1) + c2 * f(2) + .. + ck * f(Fib(k)) = 0 (p(i) = sigma(cj * Fib(j) ^ i as the problem states)
//we have p(k + 1) + a1 * p(k) + ... + ak * p(1) = 0
#include <bits/stdc++.h>
using namespace std;

const int N = 4010;
long long fib[N],a[N],b[N],c[N];

void solve()
{
    long long n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> b[i];
    fib[1] = 1,fib[2] = 2;
    for(int i = 3; i <= n; i ++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % m;
    }
    memset(a,0,sizeof(a));
    a[0] = 1;
    for(int i = 1; i <= n; i ++) {
        c[0] = 0;
        for(int j = 1; j <= n; j ++) c[j] = a[j - 1];
        for(int j = 0; j <= n; j ++) {
            c[j] = (c[j] - a[j] * fib[i]) % m;
        }
        for(int j = 0; j <= n; j ++) a[j] = c[j];
    }
    long long ans = 0;
    for(int i = 1; i <= n; i ++)
        ans = (ans + a[i - 1] * b[i]) % m;
    ans = -ans;
    cout << (ans + m) % m << endl;
    //for(int i = n; i >= 0; i --)
        //cout << a[i] << " ";
    //cout << endl;
}
        
int main()
{
    int t;
    ios::sync_with_stdio(0);
    cin >> t;
    while(t --) solve();
    return 0;
}

