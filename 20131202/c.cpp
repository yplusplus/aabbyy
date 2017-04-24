#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long cal(long long n)
{
    n ++;
    long long ans = 0;
    for(int i = 0; ; i ++) {
        if((1LL << i) > n) break;
        ans += (n / (1LL << (i + 1))) * (1LL << i);
        long long m = n % (1LL << (i + 1));
        if(m > (1LL << i)) ans += m - (1LL << i);        
    }
    return ans;
}
        
int main()
{
    long long n,m;
    while(cin >> n >> m) cout << cal(m) - cal(n - 1) << endl;
    return 0;
}

