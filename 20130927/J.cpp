#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 1010000000;
const int N = 110;
struct edge
{
	int v,next;
}e[N * N * 100];

int head[N * 10],cnt;

void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int pre[N * 10],visit[N * 10];

int find(int u)
{
	for(int i = head[u]; i != -1; i = e[i].next) {
	   if(!visit[e[i].v]) {
		   visit[e[i].v] = 1;
		   int tmp = pre[e[i].v];
		   pre[e[i].v] = u;
		   if(tmp == -1 || find(tmp)) return 1;
		   pre[e[i].v] = tmp;
	   }
	}
	return 0;
}

struct point
{
	int x,y;
	friend bool operator < (const point &p,const point &q) {
		if(p.y != q.y) return p.y < q.y;
		return p.x < q.x;
	}
}a[1010];

int f[N][N];
int main()
{
	int t,n,m,r,x,y,z;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d%d",&n,&m,&r);
		memset(head,-1,sizeof(head));
		cnt = 0;
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++) {
				f[i][j] = oo;
			}
			f[i][i] = 0;
		}
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			f[x][y] = f[y][x] = min(z,f[x][y]);
		}
		for(int k = 0; k < n; k ++)
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < n; j ++)
					f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
		memset(pre,-1,sizeof(pre));
		for(int i = 0; i < r; i ++)
			scanf("%d%d",&a[i].x,&a[i].y);
		sort(a,a + r);
		for(int i = 0; i < r; i ++) {
			for(int j = i + 1; j < r; j ++) {
				if(a[i].y + f[a[i].x][a[j].x] <= a[j].y)
					addedge(i,j);
			}
		}
		int ans = r;
		for(int i = 0; i < r; i ++) {
			memset(visit,0,sizeof(visit));
			ans -= find(i);
		}
		printf("Case %d: %d\n",cas,ans - 1);
	}
	return 0;
}

