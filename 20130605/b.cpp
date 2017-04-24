#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5010;

struct edge
{
	int v,next;
}e[10010];

int head[N],cnt,root;
void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

void dummy(int n,int *a)
{
	for(int i = 0; i < n; i ++)
		printf("%d ",a[i]);
	printf("\n");
}

int maxn,tot;
void search(int n,int *dfn,int *low,int now,int &cnt,int *st,int &sp,int rt)
{
	int i, m; //a[N];
	dfn[st[sp ++] = now] = low[now] = ++ cnt;
	int sum = 0;
	for(i = head[now]; i != -1; i = e[i].next) {
		if(e[i].v == root) continue;
		if(!dfn[e[i].v]) {
			search(n,dfn,low,e[i].v,cnt,st,sp,rt);
			if(low[e[i].v] < low[now]) {
				low[now] = low[e[i].v];
			}
			if(low[e[i].v] >= dfn[now]) {
				for(st[sp] = -1/*,a[0] = now*/,m = 1; st[sp] != e[i].v;sp --,m ++);//a[m ++] = st[-- sp]);
				sum ++;
			}
		}
		else if(dfn[e[i].v] < low[now]) low[now] = dfn[e[i].v];
	}
	int tt = sum + tot - 1;
	if(now != rt) tt ++;
	maxn = max(maxn,tt);
}

void block(int n)
{
	int i,cnt,dfn[N],low[N],st[N],sp = 0;
	for(i = 0; i < n; dfn[i ++] = 0);
	for(cnt = i = 0; i < n; i ++)
		if(!dfn[i] && i != root)
			search(n,dfn,low,i,cnt,st,sp,i);
}

int visit[N];
void dfs(int u)
{
	visit[u] = root;
	for(int i = head[u]; i != -1; i = e[i].next)
		if(e[i].v != root && visit[e[i].v] != root)
			dfs(e[i].v);
}

int main()
{
	int n,m,x,y;
	while(scanf("%d%d",&n,&m) != EOF) {
		memset(head,-1,sizeof(head));
		cnt = 0;
		while(m --) {
			scanf("%d%d",&x,&y);
			addedge(x,y);
			addedge(y,x);
		}
		int ans = 0;
		memset(visit,-1,sizeof(visit));
		for(int i = 0; i < n; i ++) {
			root = i;
			maxn = 0;
			tot = 0;
			for(int j = 0; j < n; j ++) {
				if(j == root) continue;
				if(visit[j] == root) continue;
				tot ++;
				dfs(j);
			}
			block(n);
			ans = max(ans,maxn);
		}
		printf("%d\n",ans);
	}
	return 0;
}

