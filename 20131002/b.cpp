#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const long long mod = 1000000007;
 
long long f[10010];
 
long long pow(long long a,long long b)
{
    long long ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans;
}
 
int main()
{
    f[1] = 1;
    for(int i = 2; i <= 10000; i ++) {
        f[i] = f[i - 1] * (4 * i - 2) % mod * pow(i + 1,mod - 2) % mod;
    }
    ios::sync_with_stdio(0);
    int n;
    while(cin >> n) cout << f[n] << endl;
    return 0;
}

