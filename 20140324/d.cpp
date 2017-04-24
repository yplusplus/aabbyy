#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const long long mod = 1000000007;
long long dp[N][N];

int main()
{
	freopen("rooks.in","r",stdin);
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		set<int> sx,sy;
		int x,y;
		int n,m,r;
		scanf("%d%d%d",&n,&m,&r);
		memset(dp,0,sizeof(dp));
		dp[0][0] = 1;
		while(r --) {
			scanf("%d%d",&x,&y);
			sx.insert(x);
			sy.insert(y);
		}
		int row = sx.size(),col = sy.size();
		if(row < col) {
			swap(row,col);
			swap(n,m);
		}
		for(int i = 1; i <= row; i ++) {
			for(int j = 0; j <= col; j ++) {
				dp[i][j] = (dp[i - 1][j] * (m - col + j));
				if(j) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * (col - (j - 1)));
				dp[i][j] %= mod;
			}
		}
		printf("Case %d: %d %I64d\n",cas,row,dp[row][col]);
	}
	return 0;
}
