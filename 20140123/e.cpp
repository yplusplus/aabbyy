#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int a[N][N];
char s[N][N];
int dp[1 << N];
int pre[1 << N];
const int oo = 1000000000;

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) {
		if(n == 0) break;
		for(int i = 0; i < n; i ++) scanf("%s",s[i]);
		for(int i = 0; i < (1 << n); i ++) {
			dp[i] = oo,pre[i] = -1;
		}
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				a[i][j] = s[i][j] - '0';
		dp[(1 << n) - 1] = 0;
		int re[25];
		for(int i = (1 << n) - 1; i >= 0; i --) {
			int tot = 0;
			for(int j = 0; j < n; j ++) {
				if(i & (1 << j)) re[tot ++] = j;
			}
			for(int j = 0; j < tot; j ++) {
				int cost = 0;
				for(int k = 0; k < tot; k ++) {
					if(j == k) continue;
					if(a[re[j]][re[k]]) cost ++;
				}
				if(dp[i ^ (1 << re[j])] > cost + dp[i]) {
					dp[i ^ (1 << re[j])] = cost + dp[i];
					pre[i ^ (1 << re[j])] = re[j];
				}
				else if(dp[i ^ (1 << re[j])] == cost + dp[i]) {
					if(re[j] < pre[i ^ (1 << re[j])]) pre[i ^ (1 << re[j])] = re[j];
				}
			}
		}
		int state = 0,tot = 0;
		while(pre[state] != -1) {
			re[tot ++] = pre[state];
			state ^= (1 << pre[state]);
		}
		for(int i = 0; i < n; i ++) {
			printf("%d",re[i]);
			if(i == n - 1) printf("\n");
			else printf(" ");
		}
		printf("%d\n",dp[0]);
	}
	return 0;
}

