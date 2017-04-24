#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;

long long pow(long long a,long long b)
{
    if(b < 0) b += mod;
    long long ans = 1;
    while(b) {
        if(b & 1LL) ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans;
}

void solve(char *s)
{
    long long x;
    /*
    if(strlen(s) < 10) {
        sscanf(s,"%I64d",&x);
        x --;
        printf("%I64d\n",pow(2LL,x));
        return 0;
    }*/
    long long t = mod - 1;
    long long sum = 0;
    for(int i = 0; s[i]; i ++) {
        sum = (10 * sum + s[i] - '0') % t;
    }
    printf("%I64d\n",pow(2LL,sum - 1));
}

char s[1000010];

int main()
{
    while(scanf("%s",s) != EOF) {
        solve(s);
    }
    return 0;
}

