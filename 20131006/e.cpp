#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
int dp[410][1 << 11];
bool flag[1 << 11];

void add(int &x,int y)
{
	x += y;
	if(x >= mod) x -= mod;
}

bool check(int state,int m)
{
	for(int i = 0; i < m; i ++) {
		int x = (state & (1 << i)) != 0;
		int y = (state & (1 << (m - i - 1))) != 0;
		if(x != y) return false;
	}
	return true;
}

int main()
{
	int t,n,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		if(m == 1) {
			printf("0\n");
			continue;
		}
		if(n < m) {
			printf("%d\n",(1 << n));
			continue;
		}
		if(n == m) {
			int ans = 0;
			for(int i = 0; i < (1 << m); i ++)
				if(!check(i,m)) ans ++;
			printf("%d\n",ans);
			continue;
		}
		memset(flag,true,sizeof(flag));
		for(int i = 0; i < (1 << (m + 1)); i ++) {
			if(check(i,m)) flag[i] = false;
			if(check(i >> 1,m)) flag[i] = false;
			if(check(i,m + 1)) flag[i] = false;
		}
		for(int i = 0; i <= n; i ++)
			for(int j = 0; j < (1 << (m + 1)); j ++)
				dp[i][j] = 0;
		for(int i = 0; i < (1 << (m + 1)); i ++)
				if(flag[i]) dp[m + 1][i] = 1;
		int state,tt = (1 << m) - 1;
		for(int i = m + 1; i < n; i ++)
			for(int j = 0; j < (1 << (m + 1)); j ++)
				if(dp[i][j]) {
					state = ((j & tt) << 1);
					if(flag[state]) {
						add(dp[i + 1][state],dp[i][j]);
					}
					state |= 1;
					if(flag[state]) {
						add(dp[i + 1][state],dp[i][j]);
					}
				}
		int ans = 0;
		for(int i = 0; i < (1 << (m + 1)); i ++)
			add(ans,dp[n][i]);
		printf("%d\n",ans);
	}
	return 0;
}

