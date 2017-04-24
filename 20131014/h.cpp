#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 55;

struct bignum
{
	long long a[33];
	bignum() {
		memset(a,0,sizeof(a));
	}

	bignum operator + (const bignum &p) {
		bignum c = *this;
		for(int i = 0; i < 33; i ++) {
			c.a[i] += p.a[i];
		}
		for(int i = 0; i < 32; i ++) {
			if(c.a[i] >= 10) {
				c.a[i] -= 10;
				c.a[i + 1] ++;
			}
		}
		return c;
	}

	void output() {
		int i = 32;
		for(i; i >= 0; i --)
			if(a[i]) break;
		for(i; i >= 0; i --)
			printf("%lld",a[i]);
		printf("\n");
	}

	bignum operator * (int x) {
		bignum c = *this;
		for(int i = 0; i < 33; i ++) c.a[i] *= x;
		for(int i = 0; i < 33; i ++) {
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
		}
		return c;
	}

	bignum operator / (int x) {
		bignum c;
		for(int i = 0; i < 33; i ++) c.a[i] = a[i];
		long long tmp = 0;
		for(int i = 32; i >= 0; i --) {
			long long p = (10 * tmp + c.a[i]) % x;
			c.a[i] = (10 * tmp + c.a[i]) / x;
			tmp = p;
		}
		return c;
	}

	bignum operator * (const bignum &p) {
		bignum c;
		for(int i = 0; i < 33; i ++)
			for(int j = 0; i + j < 33; j ++)
				c.a[i + j] += a[i] * p.a[j];
		for(int i = 0; i < 33; i ++)
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
		return c;
	}

	bool operator == (const bignum &p) {
		for(int i = 0; i < 33; i ++)
			if(a[i] != p.a[i]) return false;
		return true;
	}

	bignum operator + (long long x) {
		bignum c;
		for(int i = 0; i < 33; i ++) c.a[i] = a[i];
		c.a[0] += x;
		for(int i = 0; i < 33; i ++) {
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
		}
		return c;
	}

	bignum operator - (int x) {
		bignum c;
		for(int i = 0; i < 33; i ++) c.a[i] = a[i];
		c.a[0] -= x;
		for(int i = 0; i < 33; i ++) {
			if(c.a[i] < 0) {

				c.a[i + 1] --;
				c.a[i] += 10;
			}
		}
		return c;
	}

	bignum operator - (const bignum &p) {
		bignum c;
		for(int i = 0; i < 33; i ++)
			c.a[i] = a[i] - p.a[i];
		for(int i = 0; i < 32; i ++)
			if(c.a[i] < 0) {
				c.a[i + 1] -- ;
				c.a[i] += 10;
			}
		return c;
	}

	bool operator > (const bignum &p) {
		for(int i = 32; i >= 0; i --) {
			if(a[i] != p.a[i]) {
				if(a[i] > p.a[i]) return true;
				return false;
			}
		}
		return false;
	}

	bool operator < (const bignum &p) {
		for(int i = 32; i >= 0; i --) {
			if(a[i] != p.a[i]) {
				if(a[i] < p.a[i]) return true;
				return false;
			}
		}
		return false;
	}
};

bignum dp[N][N][N];
bignum f[N];
int visit[N][N][N];
bignum zero;
bignum one;
bignum cal(bignum n,bignum m,int mm)
{
	if(n < m) return zero;
	if(m == zero) return one;
	if(n == m) return one;
	bignum ans = one;
	for(int i = 1; i <= mm; i ++) {
		//bignum  d = __gcd(n - i + 1, i);
		//bignum x = n / d;
		//bignum y = i / d;
		//ans = ans / y * x;'
		bignum tmp = zero + i - 1;
		ans = ans * (n - tmp) / i;
	}
	return ans;
}

bignum dfs(int n,int m,int r)
{
	if(n < m * r + 1) return zero;
	if(n == 1) {
		if(!m) return one;
		return zero;
	}
	if(!m) return zero;
	if(visit[n][m][r]) return dp[n][m][r];
	visit[n][m][r] = 1;
	for(int p = 0; p * r < n && p <= m; p ++) {
		bignum tmp = f[r];
		bignum tt = dfs(n - r * p,m - p,r + 1);
		if(tt == zero) continue;
		dp[n][m][r] = dp[n][m][r] + cal(tmp + p - 1,zero + p,p) * tt;
//		if(n == 4 && m == 3 && r == 1) cout << p << " " << cal(tmp + p - 1,p) << " " << tt << endl;
	}
	return dp[n][m][r];
}

int main()
{
	one.a[0] = 1;
//	memset(dp,0,sizeof(dp));
	memset(visit,0,sizeof(visit));
	for(int i = 1; i <= 50; i ++) {
		for(int j = 0; j < i; j ++) { 
			f[i] = f[i] + dfs(i,j,1);
	//		if(i == 4 && j == 3) cout << i << " " << j << " "<< f[i] << endl;
		}
	//	cout << i << " ";
	//	f[i].output();
		//cout << i << " " << f[i] << endl;
	}
	int n;
	while(scanf("%d",&n) != EOF) f[n].output();//cout << f[n] << endl;
	return 0;
}

