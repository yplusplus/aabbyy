#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int mod = 2011;
int a[20010];
int sum[20010];

int cal(int n)
{
	int x = n / 2010;
	if(n % 2010 == 0) return x * sum[2009] % mod;
	int y = n % 2010;
	y --;
	return (x * sum[2009] + sum[y]) % mod;
}

int main()
{
	int n;
	a[0] = 1;
	sum[0] = 1;
	for(int i = 1; i <= 2011; i ++) {
		a[i] = a[i - 1] * 6 % mod;
		sum[i] = (sum[i - 1] + a[i]) % mod;
	}
	while(scanf("%d",&n) != EOF) {
		if(!n) break;
		int ans1 = 1;
		int ans2 = cal(n);
		if(n > 1) ans1 = cal(n - 1) + 1;
		else ans1 = 1;
	        printf("%d %d\n",ans1 % mod,ans2);
	}
	return 0;
}	

