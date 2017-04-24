#include <bits/stdc++.h>
using namespace std;

long long dp[25][1 << 8][1 << 8];
int n,m;

void dfs(int c,int st1,int st2,int st3,int r,long long val)
{
	if(c >= m) {
		if(st1 == (1 << m) - 1) {
			if(r == n || st2) dp[r + 1][st2][st3] += val;
		}
		return;
	}
	if(st1 & (1 << c)) dfs(c + 1,st1,st2,st3,r,val);
	else {
		dfs(c + 1,st1 | (1 << c),st2 | (1 << c),st3,r,val);
		if(!(st1 & (1 << (c + 1)))) {
			if(st3 & (1 << c)) st3 ^= (1 << c);
			dfs(c + 2,st1 | (1 << c) | (1 << (c + 1)),st2,st3,r,val);
		}
	}
}

void cal(int n,int m)
{
	dp[1][0][(1 << (m - 1)) - 1] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < (1 << m); j ++)
			for(int k = 0; k < (1 << m); k ++)
				dfs(0,j,0,k,i,dp[i][j][k]);
	cout << dp[n + 1][0][0] << endl;
}

int main()
{	
	freopen("solid.in","r",stdin);
	freopen("solid.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n < m) swap(n,m);
	cal(n,m);
	return 0;
}
