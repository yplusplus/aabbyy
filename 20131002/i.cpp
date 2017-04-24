#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int N = 1010;
struct edge
{
    int v,next;
}e[N * 2];
 
int head[N],cnt;
void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}
 
int visit[N],dp[N],f[N];
int V,a[N],b[N];
 
void dfs(int u)
{
    visit[u] = 1;
    for(int i = V; i >= b[u]; i --)
        f[i] = max(f[i],dp[i - b[u]] + a[u]);
    for(int i = head[u]; i != -1; i = e[i].next)
        if(!visit[e[i].v])
            dfs(e[i].v);
}
 
int main()
{
    int x,y,z;
    int n,r;
    while(scanf("%d%d%d",&n,&V,&r) != EOF) {
        memset(dp,0,sizeof(dp));
        memset(visit,0,sizeof(visit));
        for(int i = 1; i <= n; i ++) scanf("%d%d",&a[i],&b[i]);
        cnt = 0;
        memset(head,-1,sizeof(head));
        while(r --) {
            scanf("%d%d",&x,&y);
            addedge(x,y);
            addedge(y,x);
        }
        for(int i = 1; i <= n; i ++) {
            if(!visit[i]) {
                memset(f,0,sizeof(f));
                dfs(i);
                for(int i = 0; i <= V; i ++)
                    dp[i] = max(dp[i],f[i]);
            }
        }
        printf("%d\n",dp[V]);
    }
    return 0;
}

