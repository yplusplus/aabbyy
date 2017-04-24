#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
const int N = 1010;
int n,a[5][N];
int dp[N][8];

void dfs(int r,int st1,int st2,int val,int x,int y)
{
	if(r >= 3) {
		dp[x + 1][st2] = max(dp[x + 1][st2],dp[x][y] + val);
		return;
	}
	dfs(r + 1,st1,st2,val,x,y);
	if(!(st1 & (1 << r))) {
		if(r + 1 < 3 && !(st1 & (1 << (r + 1)))) {
			dfs(r + 2,st1 | (1 << r) | (1 << (r + 1)),st2,val + a[r][x] * a[r + 1][x],x,y);
		}
		dfs(r + 1,st1 | (1 << r),st2 | (1 << r),val + a[r][x] * a[r][x + 1],x,y);
	}
}

int main()
{
	int cas = 0;
	while(scanf("%d",&n) != EOF) {
		if(!n) break;
		for(int i = 0; i < 3; i ++)
			for(int j = 1; j <= n; j ++)
				scanf("%d",&a[i][j]);
		for(int i = 0; i <= n + 1; i ++)
			for(int j = 0; j < 8; j ++)
				dp[i][j] = -oo;
		dp[1][0] = 0;
		for(int i = 1; i <= n; i ++) {
			for(int j = 0; j < 8; j ++) {
				if(dp[i][j] < 0) continue;
				dfs(0,j,0,0,i,j);
			}
		}
		printf("Case %d: %d\n",++ cas,dp[n + 1][0]);
	}
	return 0;
}
