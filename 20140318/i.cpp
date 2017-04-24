#include <bits/stdc++.h>
using namespace std;

const int size = 25;
struct bignum
{
	long long a[size];
	bignum() {
		memset(a,0,sizeof(a));
	}
	bool operator <= (bignum &p) {
		int i = 0;
		for(i = size - 1; i >= 0; i --) {
			if(p.a[i] != a[i]) break;
		}
		if(i == -1) return true;
		return a[i] < p.a[i];
	}
	bool operator == (bignum &p) {
		for(int i = 0; i < size; i ++)
			if(a[i] != p.a[i]) return false;
		return true;
	}
	bignum operator + (bignum &p) {
		bignum c;
		for(int i = 0; i < size; i ++) {
			c.a[i] = a[i] + p.a[i];
		}
		for(int i = 0; i < size; i ++)
			if(c.a[i] >= 10) {
				c.a[i + 1] ++;
				c.a[i] -= 10;
			}
		return c;
	}
	bignum operator + (int x) {
		bignum c;
		c.a[0] = a[0] + x;
		for(int i = 1; i < size; i ++) c.a[i] = a[i];
		for(int i = 0; i < size; i ++) {
			if(c.a[i] >= 10) {
				c.a[i + 1] ++;
				c.a[i] -= 10;
			}
		}
		return c;
	}
	bignum operator - (int x) {
		bignum c;
		c.a[0] = a[0] - x;
		for(int i = 1; i < size; i ++) c.a[i] = a[i];
		for(int i = 0; i < size; i ++)
			if(c.a[i] < 0) {
				c.a[i] += 10;
				c.a[i + 1] --;
			}
		return c;
	}
	bignum operator - (bignum &p) {
		bignum c;
		for(int i = 0; i < size; i ++) c.a[i] = a[i] - p.a[i];
		for(int i = 0; i < size; i ++)
			if(c.a[i] < 0) {
				c.a[i] += 10;
				c.a[i + 1] --;
			}
		return c;
	}
	bignum init(long long x) {
		bignum c;
		c.a[0] = x;
		for(int i = 0; i < size; i ++) {
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
		}
		return c;
	}
	bignum operator * (long long x) {
		bignum c;
		for(int i = 0; i < size; i ++) c.a[i] = a[i] * x;
		for(int i = 0; i < size; i ++)
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
		return c;
	}
	bignum operator * (bignum p) {
		bignum c;
		for(int i = 0; i < size; i ++)
			for(int j = 0; i + j < size; j ++)
				c.a[i + j] += a[i] * p.a[j];
		for(int i = 0; i < size; i ++)
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
	}
	void output() {
		int i;
		for(i = size - 1; i >= 0; i --)
			if(a[i]) break;
		if(i == -1) i ++;
		//cout << "length = : " << i << endl;
		for(i; i >= 0; i --)
			printf("%lld",a[i]);
		printf("\n");
	}
}dp[210],p2[110];

void get_ans(bignum kth)
{
	int len;
	for(len = 1; ; len ++) {
		if(kth <= dp[len]) break;
		else kth = kth - dp[len];
	}
	if(len == 1) {
		cout << "a";
		return;
	}
	int i;
	for(i = len; i >= 1; i --) {
		if(kth <= p2[len - i]) break;
	}
	for(int j = 0; j < i; j ++)
		printf("a");
	if(i == 0) {
		printf("bb");
		kth = kth - p2[len - 1];
		len -= 2;
		if(!len) return;
	}
	len -= i;
	bool flag = false;
	if(i) flag = true;
	while(len) {
		if(len == 1) {
			if(kth.a[0] == 1) printf("a");
			else printf("b");
			break;
		}
		if(kth <= p2[len - 1]) flag = true,printf("a"),len --;
		else {
			if(flag) {
				printf("b"), kth = kth - p2[len - 1],len --;
			}
			else {
				printf("bb");
				kth = kth - p2[len - 1];
				len -= 2;
			}
		}
	}
}

int main()
{
	dp[0].a[0] = 1;
	dp[1].a[0] = 1;
	p2[0].a[0] = 1;
	for(int i = 1; i < 70; i ++)
		p2[i] = p2[i - 1] * 2;
	for(int i = 2; i < 110; i ++) {
		dp[i] = dp[i - 1] + dp[i - 2];
		dp[i] = dp[i] + dp[i - 2];
		//dp[i].output();
	}
	long long n,m;
	int cas = 0;
	while(scanf("%lld%lld",&n,&m) != EOF) {
		if(!n && !m) break;
		int len;
		bignum lt;
		lt = lt.init(m - 1);
		lt = lt * n;
		lt = lt + 1;
		printf("Case %d: ",++ cas);
		get_ans(lt);
		printf(" ");
		bignum rt;
		rt = rt.init(m);
		rt = rt * n;
		get_ans(rt);
		printf("\n");
	}
	return 0;
}
