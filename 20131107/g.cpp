#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int get_val(int n,int m)
{
	if(n % m == 0) return 0;
	while(n < m) n *= 10;
	return n / m;
}

int main()
{
	int dp[35][35];
	int a[35];
	int t,n;
	scanf("%d",&t);
	while(t --) {
		scanf("%d",&n);
		for(int i = 1; i < n; i ++)
			scanf("%d",&a[i]);
//		cout << "enter" << endl;
		for(int mod = 1; mod < n; mod ++) {
//			cout << "omg " << mod << endl; 
			memset(dp,0,sizeof(dp));
			dp[0][0] = 1;
			for(int i = 1; i < n; i ++) {
				for(int j = 0; j <= n; j ++)
					dp[i][j] = dp[i - 1][j];
				for(int j = 1; j <= n; j ++)
					dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * a[i]) % mod;
			}
			int ans = get_val(dp[n - 1][n - mod],mod);
			printf("%d ",ans);
		}
		printf("%d\n",get_val(1,n));
	}
	return 0;
}
