#include <bits/stdc++.h>
using namespace std;

int K;
const long long mod = 20140518;

struct matrix
{
	long long a[11][11];
	matrix() {
		memset(a,0,sizeof(a));
	}
	matrix operator * (const matrix &p) {
		matrix c;
		for(int i = 1; i <= K; i ++)
			for(int j = 1; j <= K; j ++)
				for(int k = 1; k <= K; k ++) {
					c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
				}
		return c;
	}
};

matrix pow(matrix t,long long n)
{
	if(n == 1) return t;
	if(n & 1LL) return pow(t * t,n / 2) * t;
	return pow(t * t,n / 2);
}

matrix build()
{
	matrix a;
	for(int i = 1; i <= K; i ++) {
		for(int j = i; j <= K; j ++) {
			a.a[i][j] = 1;
		}
		if(i > 1) a.a[i][i - 1] = K + 2 - i;
	}
	return a;
}

int main()
{
	long long n;
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		cin >> n >> K;
		printf("Case #%d: ",cas);
		if(n == 1) {
			cout << K + 1 << endl;
			continue;
		}
		matrix a = build();
		a = pow(a,n - 1);
		long long ans = 0;
		for(int i = 1; i <= K; i ++)
			ans += a.a[i][1] * (K + 1) % mod;
		cout << ans % mod << endl;
	}
	return 0;
}
