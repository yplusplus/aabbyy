#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

double dp[210][210];
int visit[210][210];

double c[210][210];

void init()
{
	memset(c,0,sizeof(c));
	for(int i = 0; i < 210; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
}

double dfs(int n,int m)
{
	if(!m) return n;
	if(n <= 2 * m) return 0;
	if(visit[n][m]) return dp[n][m];
	int r = n - m;
	double maxn = 0;
	for(int i = 0; i <= r; i ++) {
		double sum = 0;
		for(int j = 0; j <= m && j <= i; j ++) {
			sum += c[m][j] * c[r - m][i - j] / c[r][i] * dfs(r - i,m - j);
		}
		maxn = max(maxn,sum);
	}
	visit[n][m] = 1;
	return dp[n][m] = maxn;
}

int main()
{
	init();
	memset(visit,0,sizeof(visit));
	int n,m;
	scanf("%d%d",&n,&m);
	memset(dp,0,sizeof(dp));
	printf("%.20lf\n",dfs(n,m));
	return 0;
}
