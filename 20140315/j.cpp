#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int oo = 1010000000;
struct edge
{
	int v,f,p,next;
}e[N * 2];

int cnt,head[N];

void addedge(int u,int v,int f,int p)
{
	e[cnt].v = v;
	e[cnt].f = f;
	e[cnt].p = p;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int dis[N][2],fa[N],dp[N];

void dfs1(int u,int pre)
{
	dis[u][0] = dis[u][1] = 0;
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v == pre) continue;
		dfs1(e[i].v,u);
		if(dis[e[i].v][0] + e[i].f > dis[u][0]) {
			dis[u][1] = dis[u][0];
			dis[u][0] = dis[e[i].v][0] + e[i].f;
		}
		else if(dis[u][1] < dis[e[i].v][0] + e[i].f)
			dis[u][1] = dis[e[i].v][0] + e[i].f;
	}
}

void dfs2(int u,int pre)
{
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v == pre) continue;
		int x = e[i].v;
		fa[x] = fa[u] + e[i].f;
		if(dis[e[i].v][0] + e[i].f == dis[u][0])
			fa[x] = max(fa[x],dis[u][1] + e[i].f);
		else fa[x] = max(fa[x],dis[u][0] + e[i].f);
		dfs2(e[i].v,u);
	}
}

int path[N],tot;

void dfs3(int u,int pre)
{
	int sum = 0;
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v == pre) continue;
		if(dis[e[i].v][0] + e[i].f != dis[u][0]) continue;
		dfs3(e[i].v,u);
		//mx = max(mx,min(e[i].p,dp[e[i].v]));
		sum += min(e[i].p,dp[e[i].v]);
	}
	if(sum) dp[u] = sum;
}

void find_path(int u,int pre)
{
	for(int i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v == pre) continue;
		if(dis[e[i].v][0] + e[i].f != dis[u][0]) continue;
		if(e[i].p <= dp[e[i].v]) path[tot ++] = i / 2;
		else find_path(e[i].v,u);
	}
}

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		return p.y > q.y;
	}
}pt[N];

int pp[N];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	int x,y,f,p;
	scanf("%d",&n);
	cnt = 0;
	memset(head,-1,sizeof(head));
	for(int i = 1; i < n; i ++) {
		scanf("%d%d%d%d",&x,&y,&f,&p);
		addedge(x,y,f,p);
		addedge(y,x,f,p);
	}
	dfs1(1,0);
	dfs2(1,0);
	x = -1,y = -1;
	int maxn = 0x7fffffff;
	for(int i = 1; i <= n; i ++)
		if(maxn > max(fa[i],dis[i][0])) {
			maxn = max(fa[i],dis[i][0]);
			x = i,y = -1;
		}
		else if(maxn == max(fa[i],dis[i][0])) {
			y = i;
		}
	dfs1(x,y);
	if(y != -1) dfs1(y,x);
	fill(dp + 1,dp + n + 1,oo);
	dfs3(x,y);
	if(y != -1) {
		dfs3(y,x);
		dfs3(x,y);
		int ans = -1,id = -1;
		for(int i = head[x]; i != -1; i = e[i].next) {
			if(e[i].v == y) {
				ans = e[i].p;
				id = i / 2;
			}
		}
		if(ans <= min(dp[x],dp[y])) {
			printf("%d\n",ans);
			printf("1\n");
			printf("%d\n",id + 1);
			return 0;
		}
		tot = 0;
		if(dp[x] < min(ans,dp[y])) {
			find_path(x,y);
		}
		else find_path(y,x);

		printf("%d\n",min(ans,min(dp[x],dp[y])));
		printf("%d\n",tot);
		sort(path,path + tot);
		for(int i = 0; i < tot; i ++) {
			printf("%d",path[i] + 1);
			if(i == tot - 1) printf("\n");
			else printf(" ");
		}
	}
	else {
		int ct = 0;
		for(int i = head[x]; i != -1; i = e[i].next) {
			pt[++ ct] = point(e[i].v,dis[e[i].v][0] + e[i].f);
		}
		sort(pt + 1,pt + ct + 1);
		if(pt[1].y != pt[2].y) {
			int ans = 0;
			for(int i = head[x]; i != -1; i = e[i].next) {
				if(dis[e[i].v][0] + e[i].f == pt[1].y) {
					dfs3(e[i].v,x);
					ans = min(dp[e[i].v],e[i].p);
				}
			}
			int sum = 0;
			for(int i = head[x]; i != -1; i = e[i].next) {
				if(dis[e[i].v][0] + e[i].f == pt[2].y) {
					dfs3(e[i].v,x);
					sum += min(dp[e[i].v],e[i].p);
				}
			}
			int tt = 0;
			if(ans <= sum) {
				tot = 0;
				for(int i = head[x]; i != - 1; i = e[i].next) {
					if(e[i].v == pt[1].x) {
						if(e[i].p <= dp[e[i].v]) pp[++ tt] = i / 2;
						else {
							find_path(e[i].v,x);
							for(int j = 0; j < tot; j ++) {
								pp[++ tt] = path[j];
							}
						}
					}
				}
				//tt = 0;
				//for(int i = 0; i < tot; i ++) pp[++ tt] = path[i];
			}
			else {
				tt = 0;
				for(int i = head[x]; i != -1; i = e[i].next) {
					if(dis[e[i].v][0] + e[i].f == pt[2].y) {
						if(e[i].p <= dp[e[i].v]) pp[++ tt] = i / 2;
						else {
							tot = 0;
							find_path(e[i].v,x);
							for(int i = 0; i < tot; i ++) pp[++ tt] = path[i];
						}
					}
				}
			}
			sort(pp + 1,pp + tt + 1);
			printf("%d\n",min(ans,sum));
			printf("%d\n",tt);
			for(int i = 1; i <= tt; i ++) {
				printf("%d",pp[i] + 1);
				if(i == tt) printf("\n");
				else printf(" ");
			}
		}
		else {
			int sum = 0,mx = 0,mid = -1;
			for(int i = head[x]; i != -1; i = e[i].next)
				if(dis[e[i].v][0] + e[i].f == pt[1].y) {
					dfs3(e[i].v,x);
					sum += min(e[i].p,dp[e[i].v]);
					if(mx < min(e[i].p,dp[e[i].v])) {
						mx = min(e[i].p,dp[e[i].v]);
						mid = i;
					}
				}
			printf("%d\n",sum - mx);
			tot = 0;
			int tt = 0;
			for(int i = head[x]; i != -1; i = e[i].next)
				if(dis[e[i].v][0] + e[i].f == pt[1].y && i != mid) {
					if(e[i].p <= dp[e[i].v]) {
						pp[++ tt] = i / 2;
					}
					else {
						tot = 0;
						find_path(e[i].v,x);
						for(int j = 0; j < tot; j ++) pp[++ tt] = path[j];
					}
				}
			sort(pp + 1,pp + tt + 1);
			printf("%d\n",tt);
			for(int i = 1; i <= tt; i ++) {
				printf("%d",pp[i] + 1);
				if(i == tt) printf("\n");
				else printf(" ");
			}
		}
	}
	return 0;
}
