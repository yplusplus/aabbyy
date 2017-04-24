#pragma comment(linker,"/STACK:102400000,102400000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long mabs(long long x)
{
    return x < 0 ? (-x) : x;
}

long long a,b;
long long ans;
void cal(long long n,long long x,long long y)
{
    while(1) {
        if(min(x,y) > n) return;
        long long now = min(x,y);
        if(x == y) {
            ans += (min(n,x + a) - x) * mabs(now % a - now % b);
            x += a;
            y += b;
        //    cal(n,x + a,y + b);
        }
        else if(x > y) {
            ans += (min(n,min(x,y + b)) - y) * mabs(now % a - now % b);
            y += b;
        //    cal(n,x,y + b);
        }
        else {
            ans += (min(n,min(y,x + a)) - x) * mabs(now % a - now % b);
            x += a;
        //    cal(n,x + a,y);
        }
    }
}

int main()
{
    int t;
    long long n;
    scanf("%d",&t);
    while(t --) {
        scanf("%I64d%I64d%I64d",&n,&a,&b);
        if(a == b) {
            printf("0\n");
            continue;
        }
        if(a > b) swap(a,b);
        ans = 0;
        cal(1LL * a * b,0,0);
        ans *= (n / (1LL * a * b));
        cal(n % (1LL * a * b),0,0);
        printf("%I64d\n",ans);
    }
    return 0;
}