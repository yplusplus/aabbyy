#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const int N = 110;
int dp[1010];
int B[N],times[N][15],base[2][3][110],pt[3][N],ptk[3][N];
int b[110],n;

int solve(int v)
{
	if(v < 0) return -1000000000;
	memset(dp,0,sizeof(dp));
	for(int i = 1; i <= n; i ++) {
		for(int j = v; j >= 0; j --) {
			int tmp = -1000000000;
			for(int k = 10; k >= b[i]; k --) {
				int need = times[i][k] - times[i][b[i]];
				if(k < 6) break;
				if(j >= need) tmp = max(tmp,dp[j - need] + k * 10 * B[i]);
			}
			dp[j] = tmp;
		}
	}
	return dp[v];
}

int main()
{
	int t,m;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		double sum = 0;
		memset(times,0,sizeof(times));
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&B[i]);
			sum += B[i];
			for(int j = 1; j <= 10; j ++) {
				scanf("%d",&times[i][j]);
				times[i][j] += times[i][j - 1];
			}
		}
		for(int i = 0; i < 2; i ++) {
			for(int j = 0; j < 3; j ++) {
				scanf("%d",&pt[i][j]);
				ptk[i][j] = j + 1;
				for(int k = 1; k <= n; k ++)
					scanf("%d",&base[i][j][k]);
			}
		}
		double ans = 0;
		for(int state = 0; state < 4; state ++) {
			if((state & 1) && (state & 2)) {
				for(int i = 0; i < 3; i ++) {
					for(int j = 0; j < 3; j ++) {
						memset(b,0,sizeof(b));
						for(int k = 1; k <= n; k ++)
							b[k] = max(b[k],max(base[0][i][k],base[1][j][k]));
						double tmp = 1.0 * solve(m - pt[0][i] - pt[1][j]) / sum + ptk[0][i] + ptk[1][j];
						ans = max(ans,tmp);
					}
				}
			}
			else if(state & 1) {
				for(int i = 0; i < 3; i ++) {
					for(int j = 1; j <= n; j ++)
						b[j] = base[0][i][j];
					double tmp = 1.0 * solve(m - pt[0][i]) / sum + ptk[0][i];
					ans = max(ans,tmp);
				}
			}
			else if(state & 2) {
				for(int i = 0; i < 3; i ++) {
					for(int j = 1; j <= n; j ++)
						b[j] = base[1][i][j];
					double tmp = 1.0 * solve(m - pt[1][i]) / sum + ptk[1][i];
					ans = max(ans,tmp);
				}
			}
			else {
				memset(b,0,sizeof(b));
				double tmp = 1.0 * solve(m) / sum;
				ans = max(ans,tmp);
			}
		}
		printf("Case #%d: ",cas);
		if(ans + eps >= 60) printf("%.2lf\n",ans);
		else printf("Impossible\n");
	}	
	return 0;
}


