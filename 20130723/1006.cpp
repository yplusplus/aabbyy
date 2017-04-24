#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50010;

struct tree
{
	int lt,rt,sum[2];
}a[N * 4];

int c[N];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	a[step].sum[1] = a[step].sum[0] = 0;
	if(lt == rt) return;
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}


void query(int lt,int rt,int step,int sum[])
{
	if(a[step].lt == lt && a[step].rt == rt) {
		sum[0] = a[step].sum[0];
		sum[1] = a[step].sum[1];
		return;
	}
	if(rt <= a[2 * step].rt) query(lt,rt,2 * step,sum);
	else if(lt > a[2 * step].rt) query(lt,rt,2 * step + 1,sum);
	else {
		int sum1[2],sum2[2];
		query(lt,a[2 * step].rt,2 * step,sum1);
		query(a[2 * step + 1].lt,rt,2 * step + 1,sum2);
		sum[0] = sum1[0] + sum2[0];
		sum[1] = sum1[1] + sum2[1];
	}
}

void insert(int pos,int step,int id,int val)
{
	if(a[step].lt == a[step].rt) {
		a[step].sum[id] += val;
		return;
	}
	if(pos <= a[2 * step].rt) insert(pos,2 * step,id,val);
	else if(pos > a[2 * step].rt) insert(pos,2 * step + 1,id,val);
	else {
		insert(pos,2 * step,id,val);
		insert(pos,2 * step + 1,id,val);
	}
	for(int i = 0; i < 2; i ++)
		a[step].sum[i] = a[2 * step].sum[i] + a[2 * step + 1].sum[i];
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
	w[u] = ++ e_num;
	if(son[u]) dfs(son[u],tp);
	for(int i = head[u]; i != -1; i = e[i].next)
		if(e[i].v != fa[u] && e[i].v != son[u])
			dfs(e[i].v,e[i].v);
}

int ansx[N],ansy[N];
struct point
{
	int x,y,id;
	friend bool operator < (const point &p,const point &q) {
		return p.y < q.y;
	}
}ak[N],bk[N];

int sonc[N][2];
int find(int x,int y,int id)
{
	int tot = 0;
	int tx = x,ty = y;
	int fx = top[x],fy = top[y];
	int sum[2],tsum[2];
	sum[0] = sum[1] = 0;
	while(fx != fy) {
		if(dep[fx] < dep[fy]) swap(fx,fy),swap(x,y);
		query(w[fx],w[x],1,tsum);
		sum[0] += tsum[0];
		sum[1] += tsum[1];
		x = fa[fx];
		fx = top[x];
	}
	if(dep[x] > dep[y]) swap(x,y);
	query(w[x],w[y],1,tsum);
	sum[0] += tsum[0];
	sum[1] += tsum[1];
	ansy[id] = 3 * sum[0];
	ansx[id] = sum[1];
	ansy[id] += 3 * sum[1];
	tot = sum[0] + sum[1];
	ansy[id] += dep[ty] - tot;
	return tot;
}

int find2(int x,int y,int id)
{
	int tot = 0;
	int tx = x,ty = y;
	int fx = top[x],fy = top[y];
	int sum[2],tsum[2];
	sum[0] = sum[1] = 0;
	while(fx != fy) {
		if(dep[fx] < dep[fy]) swap(fx,fy),swap(x,y);
		query(w[fx],w[x],1,tsum);
		sum[0] += tsum[0];
		sum[1] += tsum[1];
		x = fa[fx];
		fx = top[x];
	}
	if(dep[x] > dep[y]) swap(x,y);
	query(w[x],w[y],1,tsum);
	sum[0] += tsum[0];
	sum[1] += tsum[1];
	tot = sum[0] + sum[1];
	return tot;
}

int main()
{
	int n,m,r,t;
	int x,y,z;
	scanf("%d",&t);
	while(t --) {
		scanf("%d",&n);
		init();
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&bk[i].y);
			bk[i].x = i;
		}
		scanf("%d",&m);
		memset(sonc,0,sizeof(sonc));
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			addedge(x,y);
			addedge(x,z);
			sonc[x][0] = y;
			sonc[x][1] = z;
		}
		dfs(1);
		dfs(1,1);
		init(1,e_num,1);
		scanf("%d",&m);
		for(int i = 1; i <= m; i ++) {
			scanf("%d%d",&ak[i].x,&ak[i].y);
			ak[i].id = i;
		}
		sort(ak + 1,ak + m + 1);
		sort(bk + 1,bk + n + 1);
		for(int i = 1, j = 1; i <= m; i ++) {
		       while(j <= n && bk[j].y <= ak[i].y) {
			       if(sonc[bk[j].x][0]) {
				       insert(w[sonc[bk[j].x][0]],1,0,1);
				       insert(w[sonc[bk[j].x][1]],1,1,1);
			       }
			       j ++;
		       }
		       if(ak[i].x == 1) {
			       ansx[ak[i].id] = ansy[ak[i].id] = 0;
		       }
		       else find(1,ak[i].x,ak[i].id);
		}
		int i = 1,j;
		init(1,n,1);
		while(i <= m) {
			j = i;
			while(j <= m && ak[j].y == ak[i].y) j ++;
			int lt = 1,rt = n,mid;
			int tx = -1,ty = -1;
			while(lt <= rt) {
				mid = (lt + rt) / 2;
				if(bk[mid].y >= ak[i].y) {
					tx = mid;
					rt = mid - 1;
				}
				else lt = mid + 1;
			}
			lt = 1,rt = n;
			while(lt <= rt) {
				mid = (lt + rt) / 2;
				if(bk[mid].y <= ak[i].y) {
					ty = mid;
					lt = mid + 1;
				}
				else rt = mid - 1;
			}
			if(tx == -1 || ty == -1 || bk[tx].y != ak[i].y) {
				i = j;
				continue;
			}
			for(int k = tx; k <= ty; k ++) {
			       if(sonc[bk[k].x][0]) {
				       insert(w[sonc[bk[k].x][0]],1,0,1);
				       insert(w[sonc[bk[k].x][1]],1,1,1);
			       }
			}
			for(int k = i; k < j; k ++) {
				if(ak[k].x == 1) continue;
				int tot = find2(1,ak[k].x,ak[k].id);
				if(tot) ansx[ak[k].id] = -1;
			}
			for(int k = tx; k <= ty; k ++) {
			       if(sonc[bk[k].x][0]) {
				       insert(w[sonc[bk[k].x][0]],1,0,-1);
				       insert(w[sonc[bk[k].x][1]],1,1,-1);
			       }
			}
			i = j;
		}		
		for(int i = 1; i <= m; i ++)
			if(ansx[i] == -1) printf("0\n");
			else printf("%d %d\n",ansx[i],ansy[i]);
	}
	return 0;
}


