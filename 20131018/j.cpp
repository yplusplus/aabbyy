#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1010;
const int oo = 1000000000;
struct edge
{
	int v,next;
}e[N * N];

int head[N],cnt;

void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int pre[N],visit[N];
int f[N / 10][N / 10];

int find(int u)
{
	for(int i = head[u]; i != -1; i = e[i].next)
		if(!visit[e[i].v]) {
			visit[e[i].v] = 1;
			int tmp = pre[e[i].v];
			pre[e[i].v] = u;
			if(tmp == -1 || find(tmp)) return 1;
			pre[e[i].v] = tmp;
		}
	return 0;
}

struct point
{
	int x,t;
	void read() {
		scanf("%d%d",&x,&t);
	}
	friend bool operator < (const point &p,const point &q) {
		return p.t < q.t;
	}
}a[N];

int main()
{
	int n,m,r;
	int x,y,z;
	while(scanf("%d%d%d",&n,&m,&r)) {
		if(!n && !m && !r) break;
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++)
				f[i][j] = oo;
			f[i][i] = 0;
		}
		cnt = 0;
		memset(head,-1,sizeof(head));
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			f[x][y] = f[y][x] = min(z,f[x][y]);
		}
		for(int k = 0; k < n; k ++)
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < n; j ++)
					f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
		for(int i = 0; i < r; i ++)
			a[i].read();
		sort(a,a + r);
		memset(pre,-1,sizeof(pre));
		int ans = r;
		for(int i = 0; i < r; i ++)
			for(int j = i + 1; j < r; j ++)
				if(f[a[i].x][a[j].x] + a[i].t <= a[j].t)
					addedge(i,j);
		for(int i = 0; i < r; i ++) {
			memset(visit,0,sizeof(visit));
			ans -= find(i);
		}
		printf("%d\n",ans);
	}
	return 0;
}

