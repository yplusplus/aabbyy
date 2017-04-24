#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 110;
int dp[N][N][1 << 8];
int b[N],c[N],d[N];
int a[N],mm[N],r[N];
int X,Y;
priority_queue<int> q;

int main()
{
	int n,m,x;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 0; i < n; i ++)
			scanf("%d%d%d",&b[i],&c[i],&d[i]);
		memset(r,0,sizeof(r));
		for(int i = 1; i <= m; i ++) {
			scanf("%d%d",&a[i],&mm[i]);
			for(int j = 1; j <= mm[i]; j ++) {
				scanf("%d",&x);
				x --;
				r[i] |= (1 << x);
			}
		}
		scanf("%d%d",&X,&Y);
		for(int i = 0; i <= m; i ++)
			for(int j = 0; j <= Y; j ++)
				for(int k = 0; k < (1 << n); k ++)
					dp[i][j][k] = -1000000000;
		dp[0][0][0] = 0;
		for(int i = 1; i <= m; i ++) {
			for(int j = 0; j <= Y; j ++)
				for(int k = 0; k < (1 << n); k ++) 
					dp[i][j][k] = dp[i - 1][j][k];
			for(int j = 0; j < Y; j ++)
				for(int k = 0; k < (1 << n); k ++) {
					dp[i][j + 1][k | r[i]] = max(dp[i][j + 1][k | r[i]],dp[i - 1][j][k] + a[i]);
//					dp[i][j + 1][k] = max(dp[i][j + 1][k],dp[i - 1][j][k] + a[i]);
				}
		}
		int state[1 << 7];
		for(int i = 0; i < (1 << n); i ++) state[i] = -1000000000;
		for(int i = 0; i <= Y; i ++)
			for(int j = 0; j < (1 << n); j ++)
				state[j] = max(state[j],dp[m][i][j]);
		int ans = 0;
		/*
		for(int i = 0; i < (1 << n); i ++)
			for(int j = 0; j < (1 << n); j ++)
				if((i & j) == j) state[j] = max(state[j],state[i]);*/
		for(int i = 0; i < (1 << n); i ++) {
			int sum = state[i],tot;
			for(int j = 0; j < n; j ++)
				if(i & (1 << j)) sum += c[j];
			for(int j = 0; j < (1 << n); j ++) {
				int tt = X;
				tot = sum;
				bool flag = true;
				for(int k = 0; k < n; k ++) {
					if(!(j & (1 << k))) continue;
					int bound = b[k];
					if(i & (1 << k)) bound --;
					if(tt < bound) {
						flag = false;
						break;
					}
					for(int p = 1; p <= bound; p ++) {
						tt --;
						tot += c[k];
					}
					tot += d[k];
				}
				if(!flag) continue;
				while(!q.empty()) q.pop();
				for(int k = 0; k < n; k ++) {
					if(j & (1 << k)) {
					//	if(i & (1 << k)) q.push(c[k]);
						continue;
					}
					int bound = b[k];
					if(i & (1 << k)) bound --;
					for(int p = 1; p <= bound; p ++) q.push(c[k]);
				}
				while(tt && !q.empty()) {
					tt --;
					tot += q.top();
					q.pop();
				}
				ans = max(ans,tot);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

