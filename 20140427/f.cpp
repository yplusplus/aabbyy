#include <bits/stdc++.h>
using namespace std;

const int oo = -1000000000;
const int N = 100010;
char s[N];
int pos,n;
int dp[N][4];

void dfs()
{
	if(pos > n) return;
	if(s[pos] == 'g') {
		dp[pos][3] = oo;
		dp[pos][1] = dp[pos][2] = 1;
		dp[pos][0] = 0;
		return;
	}
	int root = pos;
	int left = ++ pos;
	dfs();
	int right = ++ pos;
	dfs();
	if(s[root] == 'S') {
		dp[root][0] = max(dp[left][0] + dp[right][0],dp[left][1] + dp[right][2] - 1);
		dp[root][1] = max(dp[left][0] + dp[right][1],dp[left][1] + dp[right][3] - 1);
		dp[root][2] = max(dp[left][2] + dp[right][0],dp[left][3] + dp[right][2] - 1);
		dp[root][3] = max(dp[left][2] + dp[right][1],dp[left][3] + dp[right][3] - 1);
	}
	else {
		dp[root][0] = dp[left][0] + dp[right][0];
		dp[root][1] = dp[left][1] + dp[right][1] - 1;
		dp[root][2] = dp[left][2] + dp[right][2] - 1;
		dp[root][3] = dp[left][3] + dp[right][3] - 2;
	}
	for(int i = 0; i < 4; i ++) dp[root][i] = max(dp[root][i],oo);
}

int main()
{
	freopen("independent.in","r",stdin);
	freopen("independent.out","w",stdout);
	int ans = 0;
	scanf("%s",s + 1);
	n = strlen(s + 1);
	while(++ pos <= n) {
		int now = pos;
		dfs();
		int tmp = 0;
		for(int i = 0; i < 4; i ++)
			tmp = max(tmp,dp[now][i]);
		ans += tmp;
	}
	cout << ans << endl;
	return 0;
}
