#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int t,n,m;
	int a[110];
	long long dp[110][110];
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i ++)
			scanf("%d",&a[i]);
		sort(a + 1,a + n + 1);
		for(int i = 1; i <= n; i ++) {
			dp[1][i] = a[i] - a[1];
		}
		for(int i = 2; i <= m; i ++) {
			for(int j = i; j <= n; j ++) {
				if(i == j) dp[i][j] = dp[i - 1][j - 1];
				else {
					dp[i][j] = 1LL << 60;
					for(int k = i - 1; k < j; k ++)
						dp[i][j] = min(dp[i][j],dp[i - 1][k] + a[j] - a[k + 1]);
				}
			}
		}
		printf("Case #%d: %lld\n",cas,dp[m][n]);
	}
	return 0;
}

