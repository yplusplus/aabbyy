#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 4500;
const long long mod = 7340033;
long long fac[N],rev[N];
long long pow(long long a,long long b)
{
	long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

void init()
{
	fac[0] = rev[0] = 1;
	for(long long i = 1; i < N; i ++) {
		fac[i] = fac[i - 1] * i % mod;
		rev[i] = rev[i - 1] * pow(i,mod - 2) % mod;
	}
}

long long com(int n,int m)
{
	if(n < m) return 0;
	return fac[n] * rev[m] % mod * rev[n - m] % mod;
}

void add(long long &x,long long y)
{
	x += y;
	if(x >= mod) x %= mod;
}

long long dp[N];
int main()
{
	init();
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(n < m) {
			puts("0");
			continue;
		}
		memset(dp,0,sizeof(dp));
		dp[0] = 1;
		for(int i = m; i <= n; i ++)
			for(int j = i - m; j >= 0; j --)
				if(dp[j]) add(dp[i],dp[j] * com(i - j - 1,m - 1));
		printf("%d\n",(int)dp[n]);
	}
	return 0;
}
