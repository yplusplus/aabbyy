#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
int dp[110][1 << 10][110];
int f[110],fac[110],num[110],cnt,rev[110];
int c[110][110],match[110];

int pow(long long a,long long b)
{
	long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return ans;
}

void init()
{
	memset(c,0,sizeof(c));
	for(int i = 0; i < 110; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}

void factor(int n)
{
	cnt = 0;
	memset(num,0,sizeof(num));
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		while(n % i == 0) num[cnt] ++, n /= i;
		fac[cnt ++] = i;
	}
	if(n > 1) {
		num[cnt] = 1;
		fac[cnt ++] = n;
	}
}

void init_match(int n,int m)
{
	memset(match,0,sizeof(match));
	for(int i = 2; i <= n; i ++) {
		int state = 0,x = i;
		for(int j = 0; j < cnt; j ++) {
			int cc = 0;
			while(x % fac[j] == 0) x /= fac[j],cc ++;
			if(cc > num[j]) {
				state = -1;
				break;
			}
			if(cc == num[j]) state |= (1 << j);
		}
		if(m % i) state = -1;
		match[i] = state;
	}
}

void add(int &x,int y)
{
	x += y;
	if(x >= mod) x -= mod;
}

void solve(int n,int m)
{
	if(n == 1) {
		if(m != 1) {
			printf("0\n");
			return;
		}
		printf("1\n");
		return;
	}
	if(m == 1) {
		printf("1\n");
		return;
	}
	factor(m);
	if(fac[cnt - 1] > n) {
		printf("0\n");
		return;
	}
	init_match(n,m);
	memset(dp,0,sizeof(dp));
	dp[0][0][0] = 1;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < (1 << cnt); j ++)
			for(int k = 0; k <= i; k ++) {
				if(!dp[i][j][k]) continue;
				for(int r = k + 1; i + r <= n; r ++) {
					if(match[r] == -1) continue;
				//	cout << i << " " << j << " " << k << " : " << dp[i][j][k] << endl;
				//	cout << r << " : " << match[r] << endl;
				   for(int p = 1; p * r + i <= n; p ++) {
						int mul = 1;
				 		for(int q = 0; q < p; q ++) {
							mul = mul * 1LL * c[n - i - q * r][r] % mod;
							mul = mul * 1LL * f[r - 1] % mod;
						}
						mul = 1LL * mul * rev[p] % mod;
						add(dp[i + p * r][match[r] | j][r],1LL * dp[i][j][k] * mul % mod);
				   }		
				}
					//add(dp[i + r][match[r] | j][r],dp[i][j][k] * 1LL * c[n - i][r] % mod * f[r - 1] % mod);
			}
	/*
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < (1 << cnt); j ++) {
			if(!dp[i][j]) continue;
			for(int k = 1; i + k <= n; k ++) {
				if(match[k] == -1) continue;
				add(dp[i + k][match[k] | j],dp[i][j] * 1LL * c[n - i][k] % mod * f[k - 1] % mod);
			}
		}
		*/
	int ans = 0;
	for(int i = 1; i <= n; i ++) add(ans,dp[n][(1 << cnt) - 1][i]);
	cout << ans << endl;
}

int main()
{
	init();
	int t,n,m;
	f[0] = 1;
	rev[0] = 1;
	for(int i = 1; i < 110; i ++) {
		f[i] = 1LL * f[i - 1] * i % mod;
		rev[i] = 1LL * rev[i - 1] * pow(i,mod - 2) % mod;
	}
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		printf("Case %d: ",cas);
		solve(n,m);
	}
	return 0;
}