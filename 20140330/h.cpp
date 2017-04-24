#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int dp[N][N * 2][N];
int si[N],pi[N],mi[N];
int pre_pi[N][N][N],pre_mi[N][N][N],pre[N][N][N];

void output(int n,int pi,int mi)
{
	if(!n) return;
	output(n - 1,pre_pi[n][pi][mi],pre_mi[n][pi][mi]);
	if(pre[n][pi][mi] == 1) printf("E");
	else printf("D");
}

int main()
{
	int n,h,s,p,m;
	while(scanf("%d%d%d%d%d",&n,&h,&s,&p,&m) != EOF) {
		memset(dp,0,sizeof(dp));
		for(int i = 1; i <= n; i ++) scanf("%d%d%d",&si[i],&pi[i],&mi[i]);
		dp[0][p][m] = h;
		for(int i = 0; i < n; i ++) {
			for(int j = p; j <= p + i; j ++) {
				for(int k = 0; k <= m; k ++) {
					if(dp[i][j][k] == 0) continue;
					//enchant
					if(pi[i + 1] <= j && k >= mi[i + 1]) {
						if(dp[i + 1][j + 1][k - mi[i + 1]] < dp[i][j][k]) {
							dp[i + 1][j + 1][k - mi[i + 1]] = dp[i][j][k];
							pre[i + 1][j + 1][k - mi[i + 1]] = 1;
							pre_pi[i + 1][j + 1][k - mi[i + 1]] = j;
							pre_mi[i + 1][j + 1][k - mi[i + 1]] = k;
						}
					}
					//defeat
					int nows = s + i - (j - p);
					int lost = max(0,2 * si[i + 1] - nows);
					if(nows >= si[i + 1] && dp[i][j][k] > lost && dp[i + 1][j][k] < dp[i][j][k] - lost) {
						dp[i + 1][j][k] = dp[i][j][k] - lost;
						pre[i + 1][j][k] = 2;
						pre_pi[i + 1][j][k] = j;
						pre_mi[i + 1][j][k] = k;
					}
				}
			}
		}
		bool flag = false;
		for(int i = 0; i <= p + n && !flag; i ++)
			for(int j = 0; j <= m && !flag; j ++)
				if(dp[n][i][j]) {
					output(n,i,j);
					printf("\n");
					flag = true;
				}
		if(!flag) printf("UNLUCKY\n");
	}
	return 0;
}
