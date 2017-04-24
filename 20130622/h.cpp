#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long dp[55][10];
char s[55];

int sure(char *str)
{
	int n = strlen(str + 1);
	for(int i = 2; i <= n; i ++) {
		int x = str[i] - '0' + str[i - 1] - '0';
		if(x / 2 == str[i] - '0' || (x + 1) / 2 == str[i] - '0') continue;
		return 0;
	}
	return 1;
}

int main()
{
	scanf("%s",s + 1);
	int n = strlen(s + 1);
	memset(dp,0,sizeof(dp));
	for(int i = 0; i < 10; i ++) dp[1][i] ++;
	for(int i = 1; i < n; i ++) {
		for(int j = 0; j < 10; j ++) {
			int x = j + (s[i + 1] - '0');
			dp[i + 1][x / 2] += dp[i][j];
			if(x & 1) dp[i + 1][(x + 1) / 2] += dp[i][j];
		}
	}
	long long ans = 0;
	for(int i = 0; i < 10; i ++)
		ans += dp[n][i];
	cout << ans - sure(s) << endl;
	return 0;
}


