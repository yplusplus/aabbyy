#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[90010];
int pri[90010];

void prime()
{
    memset(a,0,sizeof(a));
    for(int i = 2; i <= 300; i ++)
        if(!a[i])
            for(int j = i * i; j <= 90000; j += i)
                a[j] = 1;
    for(int i = 0, j = 2; j <= 90000; j ++)
        if(!a[j]) pri[i ++] = j;
}

bool isprime(int n)
{
    if(n < 2) return false;
    for(int i = 0; pri[i] * pri[i] <= n; i ++)
        if(n % pri[i] == 0) return false;
    return true;
}

long long get_ans(int n)
{
    if(n == 2) return 1;
    if(n == 3) return 2;
    if(n == 4) return 3;
    long long ans = 0;
    int cnt = 0;
    for(int i = n / 2 + 1; i < n && cnt < 2; i ++) {
        ans = max(ans,1LL * i * (n - i) / __gcd(i,n - i));
        if(isprime(i)) {
            cnt ++;
        }
    }
    cnt = 0;
    for(int i = n / 2; i >= 1 && cnt < 2; i --) {
        ans = max(ans,1LL * i * (n - i) / __gcd(i,n - i));
        if(isprime(i)) {
            cnt ++;
        }
    }
    return ans;
}

int main()
{
    prime();
    int n,t;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        int ans = 0;
        /*
        for(int i = 1; i < n; i ++) {
            ans = max(ans,i * (n - i) / __gcd(i,n - i));
        }*/
      //  cout << n << "  :  " << ans << "  ";
        long long x = get_ans(n);
        printf("%I64d\n",get_ans(n));
    //    while(ans != x) printf("fuck\n");
    }
    return 0;
}

