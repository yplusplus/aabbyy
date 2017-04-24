#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510;
int dp[N][N];
char s[N][N];

int main()
{
	int t;
	scanf("%d",&t);
	int n,m;
	while(t --) {
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i] + 1);
		int ans = 1;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(i == 1 || j == 1) dp[i][j] = 1;
				else {
					int x = dp[i - 1][j - 1];
					int y = 0;
					for(int k = 1; k <= x + 1 && j - k >= 1 && i - k >= 1; k ++) {
						if(s[i][j - k] != s[i - k][j]) break;
						y = k;
					}
					dp[i][j] = y + 1;
					ans = max(ans,dp[i][j]);
				}
		for(int i = 1; i <= n; i ++)
			for(int j = m; j >= 1; j --) {
				if(i == 1 || j == m) dp[i][j] = 1;
				else {
					int x = dp[i - 1][j + 1];
					int y = 0;
					for(int k = 1; k <= x + 1 && j + k <= m && i - k >= 1; k ++) {
						if(s[i][j + k] != s[i - k][j]) break;
						y = k;
					}
					dp[i][j] = y + 1;
					ans = max(ans,dp[i][j]);
				}
			}
		for(int i = n; i >= 1; i --)
			for(int j = 1; j <= m; j ++)
				if(i == n || j == 1) dp[i][j] = 1;
				else {
					int x = dp[i + 1][j - 1];
					int y = 0;
					for(int k = 1; k <= x + 1 && j - k >= 1 && i + k <= n; k ++) {
						if(s[i][j - k] != s[i + k][j]) break;
						y = k;
					}
					dp[i][j] = y + 1;
					ans = max(ans,dp[i][j]);
				}
		for(int i = n; i >= 1; i --)
			for(int j = 1; j <= m; j ++)
				if(i == n || j == m) dp[i][j] = 1;
				else {
					int x = dp[i + 1][j + 1];
					int y = 0;
					for(int k = 1; k <= x + 1 && j + k <= m && i + k <= n; k ++) {
						if(s[i][j + k] != s[i + k][j]) break;
						y = k;
					}
					dp[i][j] = y + 1;
					ans = max(ans,dp[i][j]);
				}
		ans = ans * (ans + 1) / 2;
		printf("%d\n",ans);
	}
	return 0;
}

/*
1
4 4
abab
dacb
adab
cabb
*/

