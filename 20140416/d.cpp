#include <bits/stdc++.h>
using namespace std;

map<int,int> ma[10];
int rev[10][46];
int n,m;
long long dp[10][45];
int cc[15];

bool check(int x,int y)
{
	int a[10],b[10];
	int c1 = 0,c2 = 0;
	while(x) {
		a[c1 ++] = x & 7;
		x >>= 3;
	}
	while(y) {
		b[c2 ++] = y & 7;
		y >>= 3;
	}
	for(int i = 0; i < c2; i ++)
		if(a[i] > b[i]) return false;
	return true;
}

void dfs(int id,int left,int state,int canput)
{
	if(left == 0) {
		rev[id][cc[id]] = state;
		ma[id][state] = cc[id] ++;
		return;
	}
	for(int i = canput; i >= left; i --) {
		dfs(id,left - 1,(state << 3) + i,i - 1);
	}
}

int main()
{
	int a[10];
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
		scanf("%d",&m);
		memset(dp,0,sizeof(dp));
		int c[10];
		memset(cc,0,sizeof(cc));
		for(int i = 0; i < 10; i ++) ma[i].clear();
		for(int i = 1; i <= a[1]; i ++) {
			for(int j = n; j >= 1; j --) {
				if(a[j] >= i) {
					c[i] = j;
					break;
				}
			}
		}
		dfs(1,c[1],0,m);
		for(int i = 0; i < cc[1]; i ++) dp[1][i] = 1;
		for(int i = 2; i <= a[1]; i ++) {
			dfs(i,c[i],0,m);
			for(int j = 0; j < cc[i]; j ++) {
				for(int k = 0; k < cc[i - 1]; k ++) {
					if(check(rev[i - 1][k],rev[i][j])) dp[i][j] += dp[i - 1][k];
				}
			}
		}
		long long ans = 0;
		for(int i = 0; i < cc[a[1]]; i ++) ans += dp[a[1]][i];
		cout << ans << endl;
	}
	return 0;
}
