#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

double dp[110][110][110];
double f[110],a[110];

int main()
{
	int n;
	scanf("%d",&n);
	memset(dp,0,sizeof(dp));
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= n; j ++)
			for(int k = 0; k <= n; k ++)
				if(i == 0 && j == 0 && k == 0) dp[i][j][k] = 1;
				else {
					if(i) dp[i][j][k] += 1.0 / 3 * dp[i - 1][j][k];
					if(j) dp[i][j][k] += 1.0 / 3 * dp[i][j - 1][k];
					if(k) dp[i][j][k] += 1.0 / 3 * dp[i][j][k - 1];
				}
	memset(f,0,sizeof(f));
	memset(a,0,sizeof(a));
	f[1] = 0;
	for(int p = 2; p <= n; p ++) {
		double x = 0,y = 0;
		double sum = 1;
		memset(a,0,sizeof(a));
		for(int i = 1; i < p; i ++)
			for(int j = 1; j < p; j ++)
				if(i + j != p) continue;
				else a[i] += dp[i][j][0];
		for(int i = 1; i < p; i ++)
			for(int j = 1; j < p; j ++)
				if(i + j != p) continue;
				else a[i] += dp[0][i][j];
		for(int i = 1; i < p; i ++)
			for(int j = 1; j < p; j ++)
				if(i + j != p) continue;
				else a[i] += dp[j][0][i];

		for(int i = 1; i < p; i ++) {
			x += a[i];
			sum += a[i] * f[i];
		}
		f[p] = sum / x;
	}
	printf("%.20lf\n",f[n]);
	return 0;
}


