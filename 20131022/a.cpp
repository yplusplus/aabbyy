#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long mod = 1000000007;
struct matrix
{
	long long a[4][4];
	matrix () {
		memset(a,0,sizeof(a));
	}
	matrix operator * (const matrix &p) {
		matrix c;
		for(int i = 0; i < 4; i ++)
			for(int j = 0; j < 4; j ++)
				for(int k = 0; k < 4; k ++)
					c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
		return c;
	}
};

matrix pow(long long n,matrix t)
{
	if(n == 1) return t;
	if(n & 1LL) return pow(n / 2,t * t) * t;
	return pow(n / 2,t * t);
}

int main()
{
	long long n;
	cin >> n;
	matrix a;
	a.a[0][0] = a.a[0][3] = a.a[1][2] = a.a[3][3 ] = 2;
	a.a[0][1] = a.a[1][1] = a.a[2][2] = 4;
	a.a[0][2] = -2;
	if(n == 2) cout << 4 << endl;
	else {
		a = pow(n - 2,a);
		long long ans = a.a[0][0] * 4 + a.a[0][1] * 16 + a.a[0][2] * 16 + 4 * a.a[0][3];
		ans %= mod;
		if(ans < 0) ans += mod;
		cout << ans << endl;
	}
	return 0;
}

