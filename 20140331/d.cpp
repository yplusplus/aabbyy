#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
int deg[N];

int main()
{
    int t,n,m,x,y;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d",&n,&m);
        memset(deg,0,sizeof(deg));
        while(m --) {
            scanf("%d%d",&x,&y);
            deg[x] ++,deg[y] ++;
        }
        long long ans = 0;
        for(int i = 1; i <= n; i ++)
            ans += 1LL * deg[i] * deg[i];
        printf("%lld",ans);
        puts("");
        if(t) puts("");
    }
    return 0;
}
    
