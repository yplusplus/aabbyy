#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 410;
double dp[N][N];
int visit[N];

void solve(int n)
{
	if(n == 2) {
		dp[2][0] = 1;
		return;
	}
	if(visit[n]) return;
	visit[n] = 1;
	double sum[N];
	for(int i = 2; i < n; i ++) {
		solve(i);
		solve(n - i + 1);
		for(int k = 0; k <= n - i - 1; k ++) {
			if(k == 0) sum[k] = dp[n - i + 1][k];
			else sum[k] = sum[k - 1] + dp[n - i + 1][k];
		}
		for(int j = 0; j <= i - 2; j ++) {
			dp[n][j + 1] += 1.0 / (n - 2) * dp[i][j] * sum[min(n - i - 1,j)];
		}
		
		for(int j = 0; j <= i - 2; j ++)
			if(j == 0) sum[j] = dp[i][j];
			else sum[j] = sum[j - 1] + dp[i][j];
		for(int k = 1; k <= n - i - 1; k ++)
			dp[n][k + 1] += 1.0 / (n - 2) * dp[n - i + 1][k] * sum[min(k - 1,i - 2)];
		/*
		for(int j = 0; j <= i - 2; j ++)
			for(int k = 0; k <= n - i - 1; k ++)
				dp[n][max(j,k) + 1] += 1.0 / (n - 2) * dp[i][j] * dp[n - i + 1][k];*/
	}

	return;
}

int main()
{
	memset(dp,0,sizeof(dp));
	memset(visit,0,sizeof(visit));
	int n;
	scanf("%d",&n);
	solve(n);
	double ans = 0;
	for(int i = 1; i <= n - 2; i ++)
		ans += dp[n][i] * i * 10;
	printf("%.20lf\n",ans);
	return 0;
}

