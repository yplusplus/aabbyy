#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
const int N = 110;
struct edge
{
	int v,c,t,h,next;
}e[N * N];

int head[N],cnt;

void addedge(int u,int v,int c,int t,int h)
{
	e[cnt].v = v;
	e[cnt].c = c;
	e[cnt].t = t;
	e[cnt].h = h;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

struct point
{
	int v,cost,dis;
	point() {}
	point(int v,int cost,int dis):v(v),cost(cost),dis(dis) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.cost != q.cost) return p.cost > q.cost;
		return p.dis > q.dis;
	}
};
priority_queue<point> q;
int n,m,st,ed;
int money,maxtime;
struct path
{
	int v,cost,id;
	path() {}
	path(int v,int cost,int id):v(v),cost(cost),id(id) {}
}pre[N][N];
int dp[N][N];

bool check(int mid)
{
	while(!q.empty()) q.pop();
	if(st == ed) return true;
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < N; j ++)
			dp[i][j] = oo;
	dp[st][0] = 0;
	q.push(point(st,0,0));
	while(!q.empty()) {
		point u = q.top();
		q.pop();
		for(int i = head[u.v]; i != -1; i = e[i].next) {
			if(e[i].c + u.cost > n) continue;
			if(e[i].h > mid) continue;
			if(dp[e[i].v][e[i].c + u.cost] > dp[u.v][u.cost] + e[i].t) {
				dp[e[i].v][e[i].c + u.cost] = dp[u.v][u.cost] + e[i].t;
				q.push(point(e[i].v,e[i].c + u.cost,dp[e[i].v][e[i].c + u.cost]));
				pre[e[i].v][e[i].c + u.cost] = path(u.v,u.cost,i + 1);
			}
		}
	}
	for(int i = 0; i <= n && i <= money; i ++)
		if(dp[ed][i] <= maxtime) return true;
	return false;
}

int anss[N];

void get_ans(int des,int cost)
{
	if(des != st) {
		get_ans(pre[des][cost].v,pre[des][cost].cost);
		anss[++ cnt] = pre[des][cost].id;
	}
}

int main()
{
	cnt = 0;
	memset(head,-1,sizeof(head));
	int u,v,c,t,h;
	scanf("%d%d%d%d",&n,&m,&st,&ed);
	scanf("%d%d",&money,&maxtime);
	while(m --) {
		scanf("%d%d%d%d%d",&u,&v,&c,&t,&h);
		addedge(u,v,c,t,h);
	}
	int lt = 0,rt = 10000000,mid,ans = -1;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(check(mid)) ans = mid,rt = mid - 1;
		else lt = mid + 1;
	}
	if(ans == -1) cout << -1 << endl;
	else {
		cout << ans << endl;
		check(ans);
		cnt = 0;
		for(int i = 0; i <= n && i <= money; i ++)
			if(dp[ed][i] <= maxtime) {
				get_ans(ed,i);
				break;
			}
		printf("%d\n",cnt);
		for(int i = 1; i <= cnt; i ++) {
			printf("%d",anss[i]);
			if(i == cnt) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}
