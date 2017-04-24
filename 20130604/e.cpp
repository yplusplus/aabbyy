#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int num[55];
int factor(int n)
{
	memset(num,0,sizeof(num));
	int cnt = 0;
	for(long long i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		while(n % i == 0) n /= i,num[cnt] ++;
		cnt ++;
	}
	if(n > 1) num[cnt ++] = 1;
	return cnt;
}

int cal(int n)
{
	int ans = 3;
	if(n == 1) return 6;
	ans += 3 * (2 * n - 1);
	return ans;
}

int dp[3][35];

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		int n,m;
		scanf("%d%d",&n,&m);
		if(m % n) {
			printf("0\n");
			continue;
		}
		if(n == m) {
			printf("1\n");
			continue;
		}
		int tot = factor(m / n);
		int ans = 1;
		for(int i = 0; i < tot; i ++) {
			ans = ans * cal(num[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

