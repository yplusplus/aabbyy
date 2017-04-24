#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
double c[N][N];
double f[N];
double dp[N][N];
int visit[N][N];
double ff[N];

void init()
{
	memset(c,0,sizeof(c));
	for(int i = 0; i < N; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
}

double com(int n,int m)
{
	return c[n][m];
}

double fac[N];
double cal(int n,int m)
{
	if(visit[n][m]) return dp[n][m];
	if(!n) return 1;
	if(m == 1) return 0;
	visit[n][m] = 1;
	for(int j = 0; j * m <= n; j ++) {
		double tt = 1;
		for(int i = 0; i < j; i ++)
			tt = tt * com(n - i * m,m) * ff[m];
		tt /= fac[j];
		dp[n][m] += tt * cal(n - j * m,m - 1);
	}
	return dp[n][m];
}

int main()
{
	init();
	f[1] = 0;
	f[2] = 1;
	for(int i = 3; i < N; i ++)
		f[i] = (i - 1) * (f[i - 1] + f[i - 2]);
	double ans = 0;
	memset(visit,0,sizeof(visit));
	memset(dp,0,sizeof(dp));
	int n;
	cin >> n;
	ff[1] = 1;
	fac[0] = 1;
	for(int i = 1; i < N; i ++) fac[i] = fac[i - 1] * i;
	for(int i = 2; i < N;i  ++)
		ff[i] = ff[i - 1] * (i - 1);
	for(int i = 1; i <= n; i ++) {
		for(int loop = 2; loop * i <= n; loop ++) {
			double tmp = cal(n - i * loop,loop - 1);
			double tt = 1;
			for(int j = 0;j < i; j ++)
				tt = tt * com(n - j * loop,loop) * ff[loop];
			tt /= fac[i];
			ans += tmp * i * loop * tt / f[n];
			//cout << i << " " << loop << " "<< tmp << " " << i * loop << " " << tt << " " << ff[4] << " " << ans << endl;
		}
	}
	printf("%.20lf\n",ans);
	return 0;
}