#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long N = 50010;

struct edge
{
	long long v,next;
}e[N * 2];

long long head[N],cnt;

void addedge(long long u,long long v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

long long val[N],flag[N],n,m,ans;
long long dp[N][5][2],fa[N][3];

void dfs1(long long u,long long pre)
{
	if(flag[u]) {
		for(long long i = 1; i <= m; i ++) {
			dp[u][i][1] = val[u];
		}
	}
	else {
		for(long long i = 0; i <= m; i ++)
			dp[u][i][0] = val[u];
	}
	ans = max(ans,val[u]);
	for(long long i = head[u]; i != -1; i = e[i].next) {
		if(e[i].v == pre) continue;
		long long v = e[i].v;
		dfs1(v,u);
		for(long long j = m; j >= flag[u]; j --) {
			for(long long k = 0; k <= m; k ++) {
				if(j + k > m) continue;
				if(j + k < m) {
				        ans = max(ans,dp[u][j][0] + dp[v][k][0]);
				        ans = max(ans,dp[u][j][1] + dp[v][k][0]);
				        ans = max(ans,dp[u][j][0] + dp[v][k][1]);
				        ans = max(ans,dp[u][j][1] + dp[v][k][1]);
				}
				else {
				        ans = max(ans,dp[u][j][1] + dp[v][k][1]);
				        if(j) ans = max(ans,dp[u][j][1] + dp[v][k][0]);
				        if(k) ans = max(ans,dp[u][j][0] + dp[v][k][1]);
				}
			}
		}
		if(flag[u]) {
			for(long long j = m; j >= 1; j --) {
				if(dp[u][j][0] < max(dp[v][j - 1][0],dp[v][j - 1][1]) + val[u]) {
				        dp[u][j][0] = dp[u][j][0];
				        dp[u][j][0] = max(dp[v][j - 1][0],dp[v][j - 1][1]) + val[u];
				}
			}
			for(long long j = m; j >= 2; j --) {
				if(dp[u][j][1] < dp[v][j - 1][1] + val[u]) {
					dp[u][j][1] = dp[u][j][1];
					dp[u][j][1] = dp[v][j - 1][1] + val[u];
				}
			}
		}
		else {
			for(long long j = m; j >= 0; j --) {
				if(j == m) continue;
				if(dp[u][j][0] < max(dp[v][j][0],dp[v][j][1]) + val[u]) {
					dp[u][j][0] = dp[u][j][0];
					dp[u][j][0] = max(dp[v][j][0],dp[v][j][1]) + val[u];
				}
			}
			for(long long j = m; j >= 0; j --) {
				if(dp[u][j][1] < dp[v][j][1] + val[u]) {
					dp[u][j][1] = dp[u][j][1];
					dp[u][j][1] = dp[v][j][1] + val[u];
				}
			}
		}	
	}
}

int main()
{
	long long t,x,y;
	scanf("%I64d",&t);
	while(t --) {
		scanf("%I64d%I64d",&n,&m);
		for(long long i = 0; i < n; i ++) {
			scanf("%I64d%I64d",&val[i],&flag[i]);
		}
		cnt = 0;
		memset(head,-1,sizeof(head));
		for(long long i = 1; i < n; i ++) {
			scanf("%I64d%I64d",&x,&y);
			addedge(x,y);
			addedge(y,x);
		}
		memset(dp,0,sizeof(dp));
		memset(fa,0,sizeof(fa));
		ans = 0;
		dfs1(0,0);
		for(int i = 0; i < n; i ++)
			for(int j = 0; j <= m; j ++)
				for(int k = 0; k < 2; k ++)
					ans = max(ans,dp[i][j][k]);
//		dfs2(0,0);
		printf("%I64d\n",ans);
	}
	return 0;
}

