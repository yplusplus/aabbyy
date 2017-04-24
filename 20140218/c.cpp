#include <bits/stdc++.h>
using namespace std;;

const double eps = 1e-8;
struct point
{
	double x,y;
	void read() {
		scanf("%lf%lf",&x,&y);
	}
}a[25];

double dis(point p,point q)
{
	return sqrt((p.x- q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

double dist[25][25];
double dp[25];

void update(double &x,double y,bool &flag)
{
	if(x > y) {
		flag = true;
		x = y;
	}
}

void spfa(int n,int m)
{
	for(int i = 1; i <= n; i ++) {
		dp[i] = 1e9;
	}
	queue<int> q;
	int visit[25];
	memset(visit,0,sizeof(visit));
	q.push(n);
	dp[n] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		visit[u] = 0;
		for(int i = 1; i <= n; i ++) {
			if(i == u) continue;
			if(dist[u][i] * 2 + eps > m) continue;
			if(m - 2 * dist[u][i] >= dp[u]) {
				bool flag = false;
				update(dp[i],dp[u] + dist[u][i],flag);
				if(!visit[i] && flag) {
					visit[i] = 1;
					q.push(i);
				}
			}
			else if(m > 3 * dist[i][u]) {
				bool flag = false;
				double left = dp[u] - (m - 2 * dist[u][i]);
				int x = ceil((left / (m - 3 * dist[u][i])) + eps);
				double tot = x * (m - 3 * dist[u][i]);
				left = dp[u] - x * (m - 3 * dist[i][u]);
				update(dp[i],dp[u] + 2 * dist[i][u] * x + dist[i][u],flag);
				if(!visit[i] && flag) {
					visit[i] = 1;
					q.push(i);
				}
			}
		}
	}
}

int main()
{
	int n,m;
	int cas = 0;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		for(int i = 1; i <= n; i ++) a[i].read();
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				dist[i][j] = dis(a[i],a[j]);
		spfa(n,m);
		int ans = ceil(dp[1] - 1e-8);
	    if(ans <= 1000000) printf("Trial %d: %d units of food\n",++ cas,ans);
		else printf("Trial %d: Impossible\n",++ cas);
		printf("\n");
	}
	return 0;
}
