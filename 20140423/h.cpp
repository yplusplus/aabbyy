#include <bits/stdc++.h>
using namespace std;

const long long mod = 100000000;
const int N = 110;

struct bignum
{
	long long a[250];
	int len;
	bignum() {
		memset(a,0,sizeof(a));
		len = 0;
	}
	
	bignum operator + (const bignum &p) {
		int tlen = len;
		len = max(len,p.len);
		bignum c;
		for(int i = 0; i < len; i ++) 
			c.a[i] = a[i] + p.a[i];
		for(int i = 0; i < len; i ++) {
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		}
		if(c.a[len]) len ++;
		c.len = len;
		len = tlen;
		return c;
	}

	bignum operator * (const bignum &p) {
		bignum c;
		int tlen = len;
		for(int i = 0; i < len; i ++)
			for(int j = 0; j < p.len; j ++)
				c.a[i + j] += a[i] * p.a[j];
		len = p.len + len;
		for(int i = 0; i < len + 10 && i < 250; i ++) {
			if(c.a[i] >= mod) {
				c.a[i + 1] += c.a[i] / mod;
				c.a[i] %= mod;
			}
		}
		len = min(len + 10,249);
		while(len && !c.a[len - 1]) len --;
		c.len = len;
		len = tlen;
		return c;
	}

	bignum operator * (int x) {
		bignum c;
		int tlen = len;
		for(int i = 0; i < len; i ++) c.a[i] = a[i] * 2;
		for(int i = 0; i < len + 10; i ++) {
			if(c.a[i] >= mod) {
				c.a[i + 1] += c.a[i] / mod;
				c.a[i] %= mod;
			}
		}
		len += 10;
		while(len && !c.a[len - 1]) len --;
		c.len = len;
		len = tlen;
		return c;
	}

	bignum operator - (const bignum &p) {
		bignum c;
		int tlen = len;
		for(int i = 0; i < len; i ++) c.a[i] = a[i] - p.a[i];
		for(int i = 0; i < len; i ++) {
			if(c.a[i] < 0) {
				c.a[i] += mod;
				c.a[i + 1] --;
			}
		}
		while(len && !c.a[len - 1]) len --;
		c.len = len;
		len = tlen;
		return c;
	}

	void output() {
		int i = 249;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		if(i == -1) i ++;
		printf("%I64d",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%08I64d",a[i]);
		printf("\n");
	}

	void set() {
		len = 1,a[0] = 1;
	}
}f[N],c[N][N],p2[N * N];

int main()
{
	freopen("trains.in","r",stdin);
	freopen("trains.out","w",stdout);
	for(int i = 0; i <= 100; i ++) {
		c[i][0].set();
		c[i][i].set();
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	int n;
	scanf("%d",&n);
	f[2].set();
	f[3].set();
	f[3].a[0] = 4;
	p2[0].set();
	for(int i = 1; i <= n * (n - 1) / 2; i ++)
		p2[i] = p2[i - 1] * 2;
	for(int i = 4; i <= n; i ++) {
		f[i] = p2[i * (i - 1) / 2];
		//f[i].output();
		for(int j = 2; j < i; j ++) {
			bignum tmp = c[i][j] * f[j];
			f[i] = f[i] - tmp;
		//	f[i].output();
		//	tmp.output();
		}
		bignum tmp;
		tmp.set();
		f[i] = f[i] - tmp;
	}
	f[n].output();
	return 0;
}
