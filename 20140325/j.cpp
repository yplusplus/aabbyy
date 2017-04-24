#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
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

int dp[N][2],fa[N];

void dfs(int u,int pre)
{
	dp[u][0] = dp[u][1] = 0;
	for(int i = head[u]; i != -1; i = e[i].next)
		if(e[i].v != pre) {
			dfs(e[i].v,u);
			if(dp[e[i].v][0] + 1 > dp[u][0]) {
				dp[u][1] = dp[u][0];
				dp[u][0] = dp[e[i].v][0] + 1;
			}
			else dp[u][1] = max(dp[u][1],dp[e[i].v][0] + 1);
		}
}

void dfs2(int u,int pre)
{
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v == pre) continue;
		int v = e[i].v;
		fa[v] = fa[u] + 1;
		if(dp[e[i].v][0] + 1 == dp[u][0])
			fa[v] = max(fa[v],dp[u][1] + 1);
		else fa[v] = max(fa[v],dp[u][0] + 1);
		dfs2(v,u);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		int n,x,y;
		scanf("%d",&n);
		cnt = 0;
		memset(head,-1,sizeof(head));
		memset(fa,0,sizeof(fa));
		for(int i = 1; i < n; i ++) {
			scanf("%d%d",&x,&y);
			addedge(x,y);
			addedge(y,x);
		}
		dfs(0,-1);
		dfs2(0,-1);
		int ans = 0x7fffffff;
		for(int i = 0; i < n; i ++) 
			ans = min(ans,max(dp[i][0],fa[i]));
		printf("%d\n",ans);
	}
	return 0;
}
