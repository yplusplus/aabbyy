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
int son[N];
void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int visit[N];
double ans;
void dfs(int u,int pre,int x)
{
	ans += 1.0 * x / (x + 1);
	for(int i = head[u]; i != -1; i = e[i].next)
		if(e[i].v != pre) dfs(e[i].v,u,x + visit[u]);
}

int main()
{
	int t,n,x,y,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d",&n);
		memset(visit,0,sizeof(visit));
		memset(head,-1,sizeof(head));
		cnt = 0;
		for(int i = 1; i < n; i ++) {
			scanf("%d%d",&x,&y);
			addedge(x,y);
			addedge(y,x);
		}
		scanf("%d",&m);
		ans = 0;
		while(m --) {
			scanf("%d",&x);
			if(visit[x]) continue;
			visit[x] = 1;
		}
		dfs(1,0,0);
		printf("%.10lf\n",ans);
	}
	return 0;
}

