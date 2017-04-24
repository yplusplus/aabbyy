#include <bits/stdc++.h>
using namespace std;

const int SIZE = 100;
const long long mod = 1000000;
const int N = 210;
struct bignum
{
	long long a[SIZE];
	bignum() {
		memset(a,0,sizeof(a));
	}

	bignum operator + (const bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++) 
			c.a[i] = a[i] + p.a[i];
		for(int i = 0; i < SIZE; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		return c;
	}

	bignum operator * (const bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++)
			for(int j = 0; i + j < SIZE; j ++)
				c.a[i + j] += a[i] * p.a[j];
		for(int i = 0; i < SIZE; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] += c.a[i] / mod;
				c.a[i] %= mod;
			}
		return c;
	}

	void output() {
		int i = SIZE - 1;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		printf("%d",(int)a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%06d",(int)a[i]);
		printf("\n");
	}
}c[N][N],f[N];
int dp[N];

void output(int n,int a[])
{
	if(n <= 2) {
		for(int i = 1; i <= n; i ++)
			printf("%d ",a[i]);
		return;
	}
	int mid = (n + 1) / 2;
	int b[N],c[N];
	for(int i = 1; i < mid; i ++) b[i] = a[i];
	b[mid] = a[n - 1];
	output(mid,b);
	int cc = 0;
	for(int i = mid; i <= n; i ++) {
		if(i == n - 1) continue;
		c[++ cc] = a[i];
	}
	output(cc,c);
}

int main()
{
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	for(int i = 0; i < N; i ++) {
		c[i][0].a[0] = c[i][i].a[0] = 1;
		for(int j = 1; j < i; j ++) {
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
		}
	}
	f[0].a[0] = 1;
	dp[1] = 0,f[1].a[0] = 1;
	dp[2] = 1,f[2].a[0] = 2;
	for(int i = 3; i < N; i ++) {
		int mid = (i + 1) / 2;
		dp[i] = dp[mid] + dp[i - mid] + (i - 1);
		f[i] = (f[mid] * f[i - mid]) * c[i - 2][mid - 1];
		f[i] = f[i] + f[i];
	}
	int n;
	scanf("%d",&n);
	cout << dp[n] << endl;
	int a[N];
	for(int i = 1; i <= n; i ++) a[i] = i;
	output(n,a);
	printf("\n");
	f[n].output();
	return 0;
}
