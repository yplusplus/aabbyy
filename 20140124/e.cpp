#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[1010][12],f[1010][10][2];
char s[1010][35];
int nxt[1010];
int pos[1010];
int n,m,A,B,K;

void update(int &x,int y)
{
	if(x == -1 || x > y) x = y;
}

int dfs(int level,int left)
{
	if(level > n) return 0;
	if(dp[level][left] != -1) return dp[level][left];
	int cost = 0;
	if(s[level][pos[level]] == 'G') cost = A;
	update(dp[level][left],cost + dfs(level + 1,left));
	if(left == 0) update(dp[level][left],dfs(nxt[level],left) + B);
	else {
		int maxn = max(dfs(nxt[level],left) + B,dfs(level + 1,left - 1) + B);
		update(dp[level][left],maxn);
	}
	return dp[level][left];
}

int main()
{
	while(scanf("%d%d%d%d%d",&n,&m,&A,&B,&K) != EOF) {
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i] + 1);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(s[i][j] != '.') pos[i] = j;
		for(int i = 1; i <= n; i ++) {
			nxt[i] = n + 1;
			for(int j = i + 1; j <= n; j ++) {
				if(pos[i] == pos[j]) {
					nxt[i] = j;
					break;
				}
			}
		}
		/*
		for(int i = 1; i <= n; i ++) cout << pos[i] << " ";
		cout << endl;
		*/
		memset(dp,-1,sizeof(dp));
		cout << dfs(1,K) << endl;
	}
	return 0;
}
