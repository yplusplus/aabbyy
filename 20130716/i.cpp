#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long mod = 1000000007;
const int N = 1010;
long long dp[N][N];

int main()
{
	memset(dp,0,sizeof(dp));
	dp[1][0] = 1;
	dp[2][0] = 2;
	for(int i = 3; i <= 1000; i ++) {
		for(int j = 0; j < i; j ++) {
			dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j + 1)) % mod;
			if(j) dp[i][j] = (dp[i][j] + 2LL * dp[i - 1][j - 1]) % mod;
			if(j >= 2) dp[i][j] = (dp[i][j] + (i - j - 1) * dp[i - 1][j - 2]) % mod;
		}
	}
	int t,n,m;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		printf("Case #%d: %lld\n",cas,dp[n][m]);
	}
	return 0;
}

