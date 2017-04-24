#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int mod = 10003;
long long dp[N][N][N],c[N][N];

void add(long long &x,long long y)
{
	x = (x + y) % mod;
}

int main()
{
	freopen("rooks.in","r",stdin);
	freopen("rooks.out","w",stdout);
	for(int i = 0; i < N; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
	}
	int n,m,r;
	scanf("%d%d%d",&n,&m,&r);
	dp[0][m][0] = 1;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j <= m; j ++)
			for(int k = 0; k + j <= m; k ++) {
				if(!dp[i][j][k]) continue;
				if(j >= 2) add(dp[i + 1][j - 2][k + 2],dp[i][j][k] * c[j][2]);
				if(k >= 2) add(dp[i + 1][j][k - 2],dp[i][j][k] * c[k][2]);
				if(j && k) add(dp[i + 1][j - 1][k],dp[i][j][k] * j * k);
				add(dp[i + 1][j][k],dp[i][j][k]);
				if(j) add(dp[i + 1][j - 1][k + 1],dp[i][j][k] * j);
				if(k) add(dp[i + 1][j][k - 1],dp[i][j][k] * k);
			}
	long long ans = 0;
	for(int i = 0; i <= m; i ++)
		for(int j = 0; i + j <= m; j ++)
			if(j + (m - i - j) * 2 == r) add(ans,dp[n][i][j]);
	cout << ans << endl;
	return 0;
}
