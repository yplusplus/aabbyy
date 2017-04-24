#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2010;
int Map[N];
vector<int> vv[N],mat[N];
int size[N],cc,C[N];

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
};
vector<point> v[N];
void dummy(int n,vector<int> a)
{
	++ cc;
	for(int i = 0; i < n; i ++) {
		Map[a[i]] = cc;
		C[a[i]] ++;
		vv[cc].push_back(a[i]);
	}
	size[cc] = n;
}

void search(int n,vector<int> mat[],int *dfn,int *low,int now,int &cnt,int *st,int &sp)
{
	int i,m;
	vector<int> a;
	dfn[st[sp ++] = now] = low[now] = ++ cnt;
	for(int j = 0; j < mat[now].size(); j ++) {
		i = mat[now][j];
		if(!dfn[i]) {
			search(n,mat,dfn,low,i,cnt,st,sp);
			if(low[i] < low[now]) low[now] = low[i];
			if(low[i] >= dfn[now]) {
				a.clear();
				for(st[sp] = -1,a.push_back(now),m = 1; st[sp] != i;a.push_back(st[-- sp]),m ++);
				dummy(m,a);
			}
		}
		else if(dfn[i] < low[now]) low[now] = dfn[i];
	}
}

int dfn[N],low[N],st[N],visit[N];

void block(int n,vector<int> mat[])
{
	int i,cnt,sp = 0;
	for(i = 0; i < n; dfn[i ++] = 0);
	for(cnt = i = 0; i < n; i ++)
		if(!dfn[i]) search(n,mat,dfn,low,i,cnt,st,sp);
}


int g[1010][1010];

void read(int &x)
{
	char c;
	while(1) {
		c = getchar();
		if(isdigit(c)) break;
	}
	x = c - '0';
	while(1) {
		c = getchar();
		if(isdigit(c)) x = 10 * x + (c - '0');
		else return;
	}
}

int dis[N][N];

void dfs(int u,int fa,int id,int dist)
{
	if(fa == 0) dis[id][u] = 0;
	else dis[id][u] = dist;
	visit[u] = 1;
	for(int i = 0; i < v[u].size(); i ++) {
		if(!visit[v[u][i].x]) {
			dfs(v[u][i].x,u,id,min(dist,v[u][i].y));
		}
	}
}

int min_dis[N];
int main()
{
	int t,n,m,x,y;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		for(int i = 0; i < N; i ++) {
			C[i] = Map[i]= -1;
			mat[i].clear();
			vv[i].clear();
			v[i].clear();
		}
		for(int i = 0; i < m; i ++) {
			read(x);
			read(y);
			mat[x].push_back(y);
			mat[y].push_back(x);
		}
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				scanf("%d",&g[i][j]);
		cc = 0;
		block(n,mat);
		int tmp = cc;
		for(int i = 0; i < n; i ++)
			if(C[i] > 0 || C[i] == -1) {
				size[++ cc] = -1;
				Map[i] = cc;
			}
		for(int i = 1; i <= cc; i ++) {
			for(int j = 1; j <= cc; j ++)
				dis[i][j] = -1;
		}
		for(int i = 1; i <= tmp; i ++) {
			int cost = 0x7fffffff;
			for(int j = 0; j < vv[i].size(); j ++)
				for(int k = 0; k < vv[i].size(); k ++)
					if(vv[i][j] != vv[i][k]) cost = min(cost,g[vv[i][j]][vv[i][k]]);
			min_dis[i] = cost;
			for(int j = 0; j < vv[i].size(); j ++) {
				if(C[vv[i][j]] > 0) {
					v[i].push_back(point(Map[vv[i][j]],cost));
					v[Map[vv[i][j]]].push_back(point(i,cost));
				}
			}
		}
		for(int i = 1; i <= cc; i ++) {
			memset(visit,0,sizeof(visit));
			dfs(i,0,i,0x7fffffff);
		}
		bool flag = true;
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++) {
				if(i == j) continue;
				int cost;
				if(Map[i] == Map[j]) cost = min_dis[Map[i]];
				else cost = dis[Map[i]][Map[j]];
				if(g[i][j] != cost) {
				//	printf("%d %d %d\n",i,j,dis[Map[i]][Map[j]]);
					flag = false;
				}
			}
		printf("Case #%d: ",cas);
		if(flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

