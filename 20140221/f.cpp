#include <bits/stdc++.h>
using namespace std;

struct point
{
	int n,ip,mx;
	void read() {
		scanf("%d%d%d",&n,&ip,&mx);
	}
}a[110];

int dp[110][110];
int pre[110][110];
int cost[110][110];

int main()
{
	int m,n;
	int cas = 0;
	while(scanf("%d%d",&m,&n) != EOF) {
		if(!n && !m) break;
		for(int i = 1; i <= n; i ++) a[i].read();
		memset(pre,-1,sizeof(pre));
		memset(dp,0,sizeof(dp));
		for(int i = n; i >= 1; i --) {
			for(int j = 0; j <= m; j ++) {
				for(int k = 0; k <= j; k ++) {
					double p1 = a[i].ip / 100.0 + k / (10.1 + k) * a[i].mx / 100.0;
					int tmp = ceil(a[i].n * p1 + 1e-8 - 0.5);
					if(dp[i][j] < dp[i + 1][j - k] + tmp) {
						dp[i][j] = dp[i + 1][j - k] + tmp;
						pre[i][j] = j - k;
					}
					else if(dp[i][j] == dp[i + 1][j - k] + tmp)
						pre[i][j] = j - k;
				}
			}
		}
		printf("Case %d: %d\n",++ cas,dp[1][m]);
		int now = 1,tot = m;
		while(now <= n) {
			if(now > 1) printf( " ");
			printf("%d:%d",now - 1,tot - pre[now][tot]);
			tot = pre[now][tot];
			now ++;
		}
		printf("\n");
	}
	return 0;
}
