#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

const int N = 410;
stack<int> sta;
int low[N],dfn[N],bel[N],c1,c2,cnt,head[N],instack[N];

struct edge
{
	int v,next;
}e[1000010];

void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

void init()
{
	memset(low,0,sizeof(low));
	memset(head,-1,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(instack,0,sizeof(instack));
	c1 = c2 = cnt = 0;
	while(!sta.empty()) sta.pop();
}

void tarjan(int u)
{
	low[u] = dfn[u] = ++ c1;
	sta.push(u);
	instack[u] = 1;
	for(int i = head[u]; i != -1; i = e[i].next)
		if(!dfn[e[i].v]) {
			tarjan(e[i].v);
			if(low[e[i].v] < low[u]) low[u] = low[e[i].v];
		}
		else if(instack[e[i].v] && dfn[e[i].v] < low[u]) low[u] = low[e[i].v];
	if(dfn[u] == low[u]) {
		int v;
		++ c2;
		do {
			v = sta.top();
			sta.pop();
			bel[v] = c2;
			instack[v] = 0;
		}while(v != u);
	}
}

struct point
{
	int x,y,z;
	void read() {
		scanf("%d%d%d",&x,&y,&z);
	}
}a[N],b[N];

double sqr(int x)
{
	return 1.0 * x * x;
}

double dist(point p,point q)
{
	return sqrt(sqr(p.x - q.x) + sqr(p.y - q.y) + sqr(p.z - q.z));
}

int n;
bool check(double mid)
{
	init();
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++) {
			if(i == j) continue;
			if(dist(a[i],a[j]) <= 2 * mid) addedge(i,j + n);
			if(dist(a[i],b[j]) <= 2 * mid) addedge(i,j);		
			if(dist(b[i],a[j]) <= 2 * mid) addedge(i + n,j + n);
			if(dist(b[i],b[j]) <= 2 * mid) addedge(i + n,j);
		}
	}
	for(int i = 1; i <= 2 * n; i ++)
		if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; i ++)
		if(bel[i] == bel[i + n]) return false;
	return true;
}

int main()
{
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) {
			a[i].read();
			b[i].read();
		}
		double lt = 0,rt = 100000,mid,ans = 0;
		while(lt + 1e-8 <= rt) {
			mid = (lt + rt) / 2;
			if(check(mid)) ans = mid,lt = mid;
			else rt = mid;
		}
		printf("%.3lf\n",ans - 0.000499999);
	}
	return 0;
}




