#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
double dp[2][5010][2];

void add(double &x,double y)
{
	if(x < 0) x = y;
	else x += y;
}

int main()
{
//	cout << (1 << 24) << endl;
//	cout << sizeof(dp) / 4 << endl;
	int n,s;
	cin >> n >> s;
	int x = s - 2 * n;
	int y = 3 * n - s;
	n = x + y;
	int m = x;
	memset(dp,-1,sizeof(dp));
	if(y) dp[n & 1][m][0] = 0;
	if(x) dp[n & 1][m][1] = 0;
	//cout << x << " " << y << endl;
	for(int i = n; i >= 1; i --) {
		int flag = i & 1;
		for(int j = 0; j <= m; j ++)
			dp[flag ^ 1][j][0] = dp[flag ^ 1][j][1] = -1;
		for(int j = m; j >= 0; j --) {
			if(dp[flag][j][0] >= -eps) {
				if(y - (i - j) + 1) {
					add(dp[flag ^ 1][j][0],(dp[flag][j][0] + 0) * (y - (i - j) + 1) / (n - i + 1));
					add(dp[flag ^ 1][j][1],(dp[flag][j][0] + 1) * (y - (i - j) + 1) / (n - i + 1));
				}
				//if(y - (i - j) + 1) add(dp[i - 1][j][1],(dp[i][j][0] + 1) * (y - (i - j) + 1) / (n - i + 1));
			}
			if(dp[flag][j][1] >= -eps) {
				//if(m - j + 1) add(dp[i - 1][j - 1][0],(dp[i][j][1] + 1) * (m - j + 1) / (n - i + 1));
				if(m - j + 1) {
					if(j) add(dp[flag ^ 1][j - 1][1],(dp[flag][j][1] + 0) * (m - j + 1) / (n - i + 1));
					if(j) add(dp[flag ^ 1][j - 1][0],(dp[flag][j][1] + 1) * (m - j + 1) / (n - i + 1));
				}
			}
		}
	}
	/*
	for(int i = 0; i < n; i ++)
		for(int j = 0; j <= m; j ++)
			printf("%d %d : %lf %lf\n",i,j,dp[i][j][0],dp[i][j][1]);*/
	printf("%.20lf\n",dp[0][0][1]);
	return 0;
}
