#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const long long oo = 1LL << 60;
long long dp[N][10010];
long long cost[N * N];
long long a[N * N],g[N];
int q[N * N];

int main()
{
	bool flag = false;
	int n,m,A,B;
	while(scanf("%d%d%d%d",&n,&m,&A,&B) != EOF) {
		long long ave = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%lld",&a[i]);
			ave += a[i];
		}
		for(int i = 1; i <= m; i ++)
			scanf("%lld",&g[i]);
		ave /= n;
		if(flag) printf("\n");
		flag = true;
		cost[0] = 0;
		for(int i = 1; i <= n; i ++) {
			cost[i] = cost[i - 1] + (a[i] - ave) * (a[i] - ave);
		}
		for(int i = 0; i < N; i ++)
			for(int j = 0; j <= n; j ++)
				dp[i][j] = oo;
		dp[1][0] = 0;
		for(int i = A; i <= B; i ++) dp[1][i] = cost[i] * g[1];
		for(int i = B + 1; i <= n; i ++) dp[1][i] = oo;
		for(int i = 2; i <= m; i ++) {
			if((i - 1) * A > n) break;
			int top = 0,tail = 0;
			for(int j = i * A; j <= min(i * B,n); j ++) {
				while(top < tail && j - q[top] > B) top ++;
				while(top < tail) {
					int k = q[tail - 1];
					if(dp[i - 1][k] +g[i] * (cost[j - A] - cost[k]) >= dp[i - 1][j - A]) tail --;
					else break;
				}
				q[tail ++] = j - A;
				dp[i][j] = dp[i - 1][q[top]] + g[i] * (cost[j] - cost[q[top]]);
			}
		}
		long long ans = oo,idx,idy;
		for(int i = 1; i <= m; i ++) {
			if(dp[i][n] < ans) {
				ans = dp[i][n];
				idx = i;
			}
		}
		if(ans == oo) printf("No solution.\n");
		else {
			idy = oo;
			if(idx == 1) idy = n;
			else {
				for(int i = 0; i < n; i ++)
					if(n - i >= A && n - i <= B && n - i < idy) {
						if(dp[idx - 1][i] != oo && dp[idx - 1][i] + g[idx] * (cost[n] - cost[i]) == dp[idx][n])
							idy = n - i;
					}
			}
			printf("%lld %lld %lld\n",ans,idx,idy);
		}
	}
	return 0;
}
