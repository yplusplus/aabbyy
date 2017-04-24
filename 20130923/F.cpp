#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50010;
struct tree
{
	int lt,rt,flag;
}a[N * 4];

int c[N];
void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].flag = 0;
	if(lt == rt) {
		a[step].flag = c[lt];
		return;
	}
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void down(int step)
{
	a[step * 2].flag += a[step].flag;
	a[step * 2 + 1].flag += a[step].flag;
	a[step].flag = 0;
}

int query(int pos,int step)
{
	if(a[step].lt == a[step].rt) return a[step].flag;
	if(a[step].flag) down(step);
	if(pos <= a[2 * step].rt) return query(pos,2 * step);
	else return query(pos,2 * step + 1);
}

void insert(int lt,int rt,int step,int val)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		a[step].flag += val;
		return;
	}
	if(a[step].flag) down(step);
	if(rt <= a[2 * step].rt) insert(lt,rt,2 * step,val);
	else if(lt > a[2 * step].rt) insert(lt,rt,2 * step + 1,val);
	else {
		insert(lt,a[2 * step].rt,2 * step,val);
		insert(a[2 * step + 1].lt,rt,2 * step + 1,val);
	}
}

int fa[N],top[N],size[N],son[N],w[N],dep[N],e_num;

struct edge
{
	int v,next;
}e[N * 2];

int cnt,head[N];

void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

void init()
{
	cnt = e_num = 0;
	memset(head,-1,sizeof(head));
	memset(fa,0,sizeof(fa));
	memset(size,0,sizeof(size));
	memset(top,0,sizeof(top));
	memset(son,0,sizeof(son));
	memset(dep,0,sizeof(dep));
}

void dfs(int u)
{
	size[u] = 1;
	son[u] = 0;
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v != fa[u]) {
			fa[e[i].v] = u;
			dep[e[i].v] = dep[u] + 1;
			dfs(e[i].v);
			if(size[son[u]] < size[e[i].v]) son[u] = e[i].v;
			size[u] += size[e[i].v];
		}
	}
}

void dfs(int u,int tp)
{
	top[u] = tp;
	w[u] = ++e_num;
	if(son[u]) dfs(son[u],tp);
	for(int i = head[u]; i != -1; i = e[i].next)
		if(e[i].v != fa[u] && e[i].v != son[u])
			dfs(e[i].v,e[i].v);
}

void find(int x,int y,int val)
{
	int fx = top[x],fy = top[y];
	while(fx != fy) {
		if(dep[fx] < dep[fy]) swap(fx,fy),swap(x,y);
		insert(w[fx],w[x],1,val);
		x = fa[fx];
		fx = top[x];
	}
	if(dep[x] > dep[y]) swap(x,y);
	insert(w[x],w[y],1,val);
}

int b[N];
int main()
{
	int n,m,r;
	int x,y,z;
	char cd[15];
	while(scanf("%d%d%d",&n,&m,&r) != EOF) {
		init();
		for(int i = 1; i <= n; i ++) scanf("%d",&b[i]);
		while(m --) {
			scanf("%d%d",&x,&y);
			addedge(x,y);
			addedge(y,x);
		}
		dfs(1);
		dfs(1,1);
		for(int i = 1; i <= n; i ++) c[w[i]] = b[i];
		init(1,e_num,1);
		while(r --) {
			scanf("%s",cd);
			if(cd[0] == 'Q') {
				scanf("%d",&x);
				printf("%d\n",query(w[x],1));
			}
			else {
				scanf("%d%d%d",&x,&y,&z);
				if(cd[0] == 'D') z *= (-1);
				find(x,y,z);
			}
		}
	}
	return 0;
}