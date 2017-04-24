#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
int pri[90010];
int a[90010];

void prime()
{
	memset(a,0,sizeof(a));
	for(int i = 2; i <= 300; i ++)
		if(!a[i])
			for(int j = i * i; j <= 90000; j += i)
				a[j] = 1;
	for(int i = 0, j = 2; j <= 90000; j ++)
		if(!a[j]) pri[++ i] = j;
}

double dp[150][N];
int pre[150][N];
int tot = 0;
void output(int r,int n)
{
	if(n == 0) return;
	if(r == 0) {
		a[++ tot] = n;
		return;
	}
	if(pre[r][n] == n) {
		output(r - 1,n);
		return;
	}
	a[++ tot] = n - pre[r][n];
	output(r - 1,pre[r][n]);
}

void solve(int n,int m)
{
	if(n == 2) {
		printf("%d %d\n",m,m);
		return;
	}
	if(n == 3) {
		printf("%d %d\n",2 * m,m);
		return;
	}
	if(n == 4) {
		printf("%d %d\n",2 * m,2 * m);
		return;
	}
	prime();
	for(int i = 0; i <= 150; i ++)
		for(int j = 0; j <= n; j ++)
			dp[i][j] = -1,pre[i][j] = -1;
	for(int i = 0; i <= n; i ++) dp[0][i] = 0;
	for(int i = 1; i <= 150; i ++) {
		double x = log(1.0 * pri[i]);
	    for(int j = n; j >= 0; j --) { 
			dp[i][j] = dp[i - 1][j];
			pre[i][j] = j;
		}
		for(int j = n; j >= pri[i]; j --) {
			double y;
			int k;
			for(y = x,k = pri[i]; k <= j; k *= pri[i],y += x)
				if(dp[i][j] < dp[i - 1][j - k] + y) {
					dp[i][j] = dp[i - 1][j - k] + y;
					pre[i][j] = j - k;
				}
		}
	}	
	output(150,n);
	for(int i = 1; i <= tot; i ++) {
		printf("%d",a[i] * m);
		if(i == tot) printf("\n");
		else printf(" ");
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		solve(i,n / i);
		return 0;
	}
	return 0;
}
