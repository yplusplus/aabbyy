#include <bits/stdc++.h>
using namespace std;

double dp[1010][1010];
double c[1010][1010];

double fun(int n,int m)
{
	if(m < 0) return 0;
	if(n < m) return 0;
	if(m == 0) {
		if(n <= 8) return 1;
		return 0;
	}
	double ans = 0;
	for(int i = 0; i <= 8 && i <= n; i ++)
		ans += dp[n - i][m];
	return ans;
}

int main()
{
	for(int i = 0; i < 1010; i ++) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	for(int i = 1; i <= 9; i ++) dp[i][1] = 1;
	for(int i = 1; i < 1000; i ++)
		for(int j = i; j <= 1000; j ++)
			for(int k = 1; k < 10; k ++)
				dp[j + k][i + 1] += dp[j][i];
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(m <= 8) {
			printf("0.000000%%\n");
			continue;
		}
		int r = n - m;
		double sum = fun(n - 1,r - 1);
		for(int i = 0; i <= 7; i ++)
			for(int j = 0; j <= 7; j ++)
				if(i + j <= 7) sum += fun(n - i - j - 3,r - 2);
		sum /= c[n][m];
		printf("%.6f%%\n",100 - sum * 100);
	}
	return 0;
}
