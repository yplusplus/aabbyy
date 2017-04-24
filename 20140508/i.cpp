#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000000;
struct bignum
{
	int a[20];
	void init() {
		memset(a,0,sizeof(a));
	}

	void operator += (const bignum &p) {
		for(int i = 0; i < 20; i ++) a[i] += p.a[i];
		for(int i = 0; i < 20; i ++)
			if(a[i] >= mod) {
				a[i + 1] ++;
				a[i] -= mod;
			}
	}

	void output() {
		int i = 19;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		printf("%d",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%09d",a[i]);
		printf("\n");
	}

	void set() {
		memset(a,0,sizeof(a));
		a[0] = 1;
	}
}dp[2][1510];

int main()
{
	freopen("sweets.in","r",stdin);
	freopen("sweets.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++) dp[1][i].set();
	for(int i = 2; i <= m; i ++) {
		int flag = i & 1;
		for(int j = 0; j <= n; j ++) dp[flag][j].init();
		for(int j = i; j <= n; j ++) {
			//dp[i][j] = dp[i][j - i] + dp[i - 1][j - 1];
			dp[flag][j] += dp[flag][j - i];
			dp[flag][j] += dp[flag ^ 1][j - 1];
		}
	}
	dp[m & 1][n].output();
	return 0;
}
