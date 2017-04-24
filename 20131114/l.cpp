#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int pri[110];

bool isprime(int n)
{
	for(int i = 2; i * i <= n; i ++)
		if(n % i == 0) return false;
	return true;
}

int f[110];

void factor(int n,int flag)
{
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		while(n % i == 0) {
			n /= i;
			f[i] += flag;
		}
	}
	if(n > 1) f[n] += flag;
}

int main()
{
	int tot = 0;
	for(int i = 2; i < 110; i ++)
		if(isprime(i)) pri[tot ++] = i;
	memset(f,0,sizeof(f));
	int n;
	scanf("%d",&n);
	for(int i = 2; i <= n; i ++) {
		factor(i,1);
	}
	int c[4];
	int x;
	memset(c,0,sizeof(c));
	while(n --) {
		cin >> x;
		c[x] ++;
	}
	for(int i = 1; i <= 3; i ++) 
		for(int j = 2; j <= c[i];j ++)
			factor(j,-1);
	long long ans = 1;
	bool flag = false;
	for(int i = 2; i <= 100; i ++) {
		while(f[i] --) {
			ans = ans * i;
			if(ans >= 6) flag = true;
		}
	}
	if(flag) printf("Yes\n");
	else printf("No\n");
	return 0;
}
