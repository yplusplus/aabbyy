#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[1 << 20];

void solve(int lt,int rt)
{
	if(lt >= rt) return;
	int mid = (lt + rt) / 2;
	solve(lt,mid);
	solve(mid + 1,rt);
	int len = mid - lt + 1;
	for(int i = mid + 1; i <= rt; i ++)
		dp[i] += dp[i - len];
}

int main()
{
	int n,x,y;
	while(scanf("%d",&n),n > 0) {
		for(int i = 0; i < (1 << 20); i ++) dp[i] = 0;
		while(n --) {
			scanf("%d%d",&x,&y);
			dp[x] += y;
		}
		solve(0,(1 << 20) - 1);
		int ans = 0;
		for(int i = 0; i < (1 << 20); i ++) ans = max(ans,dp[i]);
		cout << ans << endl;
	}
	return 0;
}