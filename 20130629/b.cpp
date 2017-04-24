#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[4][410];

int cal(int a,int b,int c)
{
	memset(dp,0,sizeof(dp));
	dp[0][200] = 1;
	for(int i = 0; i <= 400; i ++) {
		if(dp[0][i]) {
			dp[1][i + a] = 1;
		}
		if(dp[0][i]) {
			dp[1][i - a] = 1;
		}
		dp[1][i] |= dp[0][i];
	}
	for(int i = 0; i <= 400; i ++) {
		if(dp[1][i]) {
			dp[2][i + b] = 1;
		}
		if(dp[1][i]) {
			dp[2][i - b] = 1;
		}
		dp[2][i] |= dp[1][i];
	}
	for(int i = 0; i <= 400; i ++) {
		if(dp[2][i]) {
			dp[3][i + c] = 1;
		}
		if(dp[2][i]) {
			dp[3][i - c] = 1;
		}
		dp[3][i] |= dp[2][i];
	}
	int ans = 0;
	for(int i = 201; i <= 400; i ++)
		ans += dp[3][i];
	return ans;
}

int main()
{
	int t,n,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		int ans = 0;
		for(int i = 1; i < n; i ++) {
			int x = cal(i,n - i,m);
			ans = max(ans,x);
		}
		for(int i = 1; i < m; i ++) {
			int x = cal(n,i,m - i);
			ans = max(ans,x);
		}
		printf("%d\n",ans);
	}
	return 0;
}


