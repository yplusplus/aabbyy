#pragma comment(linker, "/STACK:10006777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct edge
{
    int v,next;
}e[N * 2];

int head[N],cnt;
long long dp[N],size[N],f[N];

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

void dfs(int u,int fa)
{
    size[u] = 1;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(e[i].v == fa) continue;
        dfs(e[i].v,u);
        dp[u] += dp[e[i].v];
        dp[u] += f[u] * size[e[i].v];
        dp[u] += size[u] * f[e[i].v];
        f[u] += f[e[i].v];
        f[u] += size[e[i].v];
        size[u] += size[e[i].v];
    }
}

int main()
{
    int n,x,y;
    while(scanf("%d",&n) != EOF) {
        cnt = 0;
        memset(head,-1,sizeof(head));
        for(int i = 1; i < n; i ++) {
            scanf("%d%d",&x,&y);
            addedge(x,y);
            addedge(y,x);
        }
        memset(dp,0,sizeof(dp));
        memset(size,0,sizeof(size));
        memset(f,0,sizeof(f));
        dfs(1,0);
        printf("%I64d\n",1LL * n * (n - 1) * (n - 2) / 6LL - dp[1]);
    }
    return 0;
}

