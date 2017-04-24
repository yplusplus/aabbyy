#include <bits/stdc++.h>
using namespace std;

const int mod = 239;
int size;

struct matrix
{
	int a[32][32];
	matrix() {
		memset(a,0,sizeof(a));
	}
	matrix operator * (const matrix &p) {
		matrix c;
		for(int i = 0; i <= size; i ++)
			for(int j = 0; j <= size; j ++)
				for(int k = 0; k <= size; k ++)
					c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
		return c;
	}
}f[mod + 10];

matrix pow(long long n,matrix t)
{
	matrix b;
	for(int i = 0; i <= size; i ++) b.a[i][i] = 1;
	while(n) {
		if(n & 1LL) b = b * t;
		t = t * t;
		n >>= 1;
	}
	return b;
}

int main()
{
	freopen("peaks.in","r",stdin);
	freopen("peaks.out","w",stdout);
	/*
	int dp[15][15];
	memset(dp,0,sizeof(dp));
	dp[0][0] = 1;
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 3; j ++) {
			dp[i][j] += (dp[i - 1][j] * 2 * j) % mod;
			dp[i][j] += (dp[i - 1][j - 1] * (i - 2 * (j - 1))) % mod;
		}
	cout << dp[2][1] << endl;
	cout << dp[3][1] % mod << " " << dp[10][3] % mod << endl;*/
	//dp[i][j] = dp[i - 1][j] * (2 * j)
	//dp[i][j] = dp[i - 1][j - 1] * (i - 2 * j)	
	long long n,m;
	cin >> n >> m;
	for(int i = 1; i <= mod; i ++) {
		for(int j = 1; j <= m; j ++) {
			f[i].a[j][j] = 2 * j % mod;
			f[i].a[j][j - 1] = (i - 2 * (j - 1) + mod) % mod;
		}
	}
	size = m;
	for(int i = 0; i <= size; i ++) f[0].a[i][i] = 1;
	for(int i = 1; i <= mod; i ++)
		f[i] = f[i] * f[i - 1];
	long long times = n / mod;
	matrix a;
	for(int i = 0; i <= m; i ++) a.a[i][i] = 1;
	if(times) a = pow(times,f[mod]);
	a = f[n % mod] * a;
	long long ans = 0;
	ans += a.a[m][0];
	cout << ans % mod << endl;
	return 0;
}
