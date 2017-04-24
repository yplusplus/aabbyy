#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
long long fac[N * N];
const long long mod = 1000000007;
long long c[N][N];

void init()
{
	memset(c,0,sizeof(c));
	for(int i = 0; i < N; i ++) {
		c[i][i] = c[i][0] = 1;
		for(int j = 1; j < i; j ++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}

long long pow(long long a,long long b)
{
	long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return ans;
}

long long com(long long n,long long m)
{
	return fac[n] * pow(fac[m],mod - 2) % mod * pow(fac[n - m],mod - 2) % mod;
}

int main()
{
	fac[0] = 1;
	for(int i = 1; i < N * N; i ++)
		fac[i] = fac[i - 1] * i % mod;
	init();
	int n,m;
	cin >> n >> m;
	int r = n * n / 2;
	long long ans = 0;
	for(int i = 0; i <= n / 2 && i <= m; i ++) {
		for(int j = 0; j <= n / 2 && i + j <= m; j ++) {
			long long tmp = c[n / 2][i] * pow(3,i) % mod * c[n / 2][j] % mod * pow(3,j) % mod;
			if(r - n < m - i - j) continue;
			tmp = tmp * com(r - n,m - i - j) % mod * pow(4,m - i - j) % mod;
			ans = (ans + tmp) % mod;
	//		cout << i << " " << j << " " << tmp << endl;
		}
	}
	for(int i = 0; i <= n / 2 && i <= m; i ++) {
		long long tmp = c[n / 2][i];
		if(r - n / 2 < m - i) continue;
		tmp = tmp * com(r - n / 2,m - i) % mod * 2 % mod * pow(2,m - i) % mod ;
		ans = (ans - tmp) % mod;
		if(ans < 0) ans += mod;
	}
	cout << ans << endl;
	return 0;
}

