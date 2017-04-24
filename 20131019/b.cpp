#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct edge
{
	int u,v,dis;
	edge () {}
	edge(int u,int v,int dis):u(u),v(v),dis(dis) {}
	friend bool operator < (const edge &p,const edge &q) {
		return p.dis < q.dis;
	}
}a[110 * 110];

int pre[110];
int c[110][110];
int find(int x)
{
	if(pre[x] == -1) return x;
	return pre[x] = find(pre[x]);
}

void kruskal(int m)
{
	memset(pre,-1,sizeof(pre));
	int ans = 0;
	sort(a + 1,a + m + 1);
	for(int i = 1; i <= m; i ++) {
		int x = find(a[i].u);
		int y = find(a[i].v);
		if(x == y) continue;
		pre[x] = y;
		ans += a[i].dis;
	}
	printf("%d\n",ans);
}

int visit[110];

int main()
{
	int n,m,r;
	scanf("%d%d",&n,&m);
	int cc = 0;
	memset(visit,0,sizeof(visit));
	while(m --) {
		scanf("%d",&r);
		visit[r] = 1;
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%d",&c[i][j]);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(visit[i] && visit[j]) continue;
			else if(visit[i]) {
				a[++ cc] = edge(n + 1,j,c[i][j]);
			}
			else if(visit[j]) {
				a[++ cc] = edge(n + 1,i,c[i][j]);
			}
			else a[++ cc] = edge(i,j,c[i][j]);
	kruskal(cc);
	return 0;
}

