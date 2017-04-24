#include <bits/stdc++.h>
using namespace std;

const int N = 510;
double dp[N];
double a[15],cost[N];
int visit[N];
int n,m;

double dfs(int x)
{
	if(x > n) return 0;
	if(visit[x]) return dp[x];
	dp[x] = 0;
	visit[x] = 1;
	for(int i = 1; i <= m; i ++) {
		dp[x] += a[i] * dfs(x + i);
	}
	dp[x] += cost[x];
	//cout << x << " " << dp[x] << endl;
	return dp[x];
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= m; i ++) scanf("%lf",&a[i]);
		for(int i = 1; i <= n; i ++) {
			cost[i] = 0;
			double x,y;
			int q;
			scanf("%d",&q);
			while(q --) {
				scanf("%lf%lf",&x,&y);
				cost[i] += x * y;
			}
		}
		//for(int i = 1; i <= n; i ++) cout << cost[i] << " ";
		//cout << endl;
		memset(visit,0,sizeof(visit));
		printf("Case #%d: %.6lf\n",cas,dfs(1));
	}
	return 0;
}

