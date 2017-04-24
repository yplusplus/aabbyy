#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long oo = 1LL << 60;
const int N = 1010;
long long dp[N][N],cost[N][N];
int s[N][N];
long long X[N],Y[N];
int n,m;

void get_cost()
{
	for(int i = 0; i <= n + 5; i ++)
		for(int j = 0; j <= n + 5; j ++)
			cost[i][j] = 0;
	for(int i = 1; i <= n; i ++) {
		long long sum = Y[i];
		for(int j = i + 1; j <= n; j ++) {
			cost[i][j] = cost[i][j - 1] + (X[j] - X[j - 1]) * sum;
			sum += Y[j];
		}
	}
}

int main()
{
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n; i ++)
			scanf("%lld%lld",&X[i],&Y[i]);
		get_cost();
		for(int i = 1; i <= n; i ++) {
			s[1][i] = 0;
			dp[1][i] = cost[1][i];
		}
		for(int i = 2; i <= m; i ++) {
			for(int j = n; j >= 1; j --) {
				dp[i][j] = oo;
				int st,ed;
				st = s[i - 1][j],ed = s[i][j + 1];
				if(j == n) st = i - 1,ed = j;
				for(int k = st; k <= ed; k ++)
					if(dp[i][j] > dp[i - 1][k] + cost[k + 1][j]) {
						dp[i][j] = dp[i - 1][k] + cost[k + 1][j];
						s[i][j] = k;
					}
			}
		}
		printf("%lld\n",dp[m][n]);
	}
	return 0;
}


