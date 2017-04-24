#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000010;
int dp[N],c[N],a[N];

int main()
{
	int n,x;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&x);
			a[x] = i;
		}
		int cc = 0;
		int i = 1;
		while(i <= n) {
			int j = i + 1;
			while(j <= n & a[j - 1] < a[j]) j ++;
			c[++ cc] = j - i;
			i = j;
		}
		for(int i = 0; i <= cc; i ++) dp[i] = 0;
		for(int i = 2; i <= cc; i ++) {
			dp[i] = dp[i - 1] + 1;
			if(c[i - 1] == 1) dp[i] = min(dp[i - 2] + 1,dp[i]);
		}
		printf("%d\n",dp[cc]);
	}
	return 0;
}
