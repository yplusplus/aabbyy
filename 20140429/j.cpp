#include <bits/stdc++.h>
using namespace std;

const int mod = 100000;
const int N = 255;
struct bignum
{
	int a[N];
	bignum() {
		memset(a,0,sizeof(a));
	}
	void output() {
		int i = N - 1;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		if(i == -1) i ++;
		printf("%d",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%05d",a[i]);
		printf("\n");
	}

	bignum operator + (const bignum &p) {
		bignum c;
		for(int i = 0; i < N; i ++)
			c.a[i] = a[i] + p.a[i];
		for(int i = 0; i < N; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		return c;
	}
}p2[1 << 12];

bignum ans[2222];

int main()
{
	p2[0].a[0] = 1;
	for(int i = 1; i < (1 << 12); i ++)
		p2[i] = p2[i - 1] + p2[i - 1];
	ans[1].a[0] = 1;
	ans[2].a[0] = 4;
	ans[3].a[0] = 8;
	ans[4].a[0] = 12;
	int left = 2,x = 2,p = 2;
	for(int i = 5; i < 2001; i ++) {
		ans[i] = ans[i - 1] + p2[(i + 1) / 2];
	}
	int n;
	while(scanf("%d",&n) != EOF) {
		ans[n].output();
	}
	return 0;
}
