#include <bits/stdc++.h>
using namespace std;

struct bignum
{
	int a[110];
	void init(int x) {
		memset(a,0,sizeof(a));
		a[0] = x;
	}
	void shift() {
		for(int i = 0; i < 110; i ++)
			a[i] *= 2;
		for(int i = 0; i < 110; i ++)
			if(a[i]) {
				a[i + 1] += a[i] / 10;
				a[i] %= 10;
			}
	}
	void add() {
		a[0] ++;
		for(int i = 0; i < 110; i ++)
			if(a[i] >= 10) {
				a[i + 1] += 10;
				a[i] -= 10;
			}
	}
	void output() {
		int i = 109;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		if(i < 0) i ++;
		for(i; i >= 0; i --)
			printf("%d",a[i]);
		printf("\n");
	}
};

int decode(int a[],char *s)
{
	int n = strlen(s);
	int c[110];
	for(int i = 0; i < n; i ++) {
		c[i] = s[n - i - 1] - '0';
	}
	int len = 0;
	while(n) {
		int tmp = 0;
		for(int i = n - 1; i >= 0; i --) {
			int x = (10 * tmp + c[i]) % 2;
			c[i] = (10 * tmp + c[i]) / 2;
			tmp = x;
		}
		while(n > 0 && !c[n - 1]) n --;
		a[len ++] = tmp;
	//	cout << tmp;
	}
	//cout << endl;
	return len;
}
int main()
{
	int cas = 0;
	int a[410],b[410];
	char s[110],str[110];
	while(scanf("%s%s",s,str) != EOF) {
		if(strcmp(s,"0") == 0 && strcmp(str,"0") == 0) break;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		if(cas) printf("\n");
		int len1 = decode(a,s);
		int len2 = decode(b,str);
		int len = max(len1,len2);
		reverse(a,a + len);
		reverse(b,b + len);
	//	cout << "len = " << len << endl;
		for(int i = 0; i < len; i ++) a[i] ^= b[i];
		int cost[10];
		cost[0] = cost[1] = 0;
		bignum ans[2];
		for(int i = 0; i < 2; i ++) {
			int pre = a[0] ^ i;
			int next = i;
			ans[i].init(i);
			cost[i] = i;
			for(int j = 1; j < len; j ++) {
				ans[i].shift();
				if(pre) {
					ans[i].add();
					cost[i] ++;
					pre = a[j] ^ next ^ 1;
					next = 1;
				}
				else {
					pre = a[j] ^ next;
					next = 0;
				}
			}
			if(pre) cost[i] = 1000000000;
		}
		printf("Case Number %d: ",++ cas);
		if(min(cost[0],cost[1]) > len * len) printf("impossible\n");
		else if(cost[0] <= cost[1]) ans[0].output();
		else ans[1].output();
	}
	return 0;
}
