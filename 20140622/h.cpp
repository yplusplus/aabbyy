#include <bits/stdc++.h>
using namespace std;

map<string,int> ma;
const int N = 100010;
long long a[N];

int lowbit(int x)
{
    return x & (-x);
}

void insert(int x,long long y)
{
    for(int i = x; i < N; i += lowbit(i)) a[i] += y;
}

long long query(int x)
{
    long long ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)) ans += a[i];
    return ans;
}

char s[1000100];

int main()
{
    int n;
    while(scanf("%d",&n) != EOF) {
        if(!n) break;
        ma.clear();
        for(int i = 1; i <= n; i ++) {
            scanf("%s",s);
            ma[s] = i;
        }
        long long ans = 0;
        memset(a,0,sizeof(a));
        for(int i = 1; i <= n; i ++) {
            scanf("%s",s);
            int x = ma[s];
            ans += query(N - 1) - query(x);
            insert(x,1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

