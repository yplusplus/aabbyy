#include <bits/stdc++.h>
using namespace std;

long long c[110][110][110];
int a[110][110];
long long sum[110][110];
const long long MOD = 1000000007LL;

int main()
{
	freopen("treasures.in", "r", stdin);
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		int n,m,s,x,y;
		scanf("%d%d%d%d%d",&n,&m,&s,&x,&y);

		int sx = x, sy = y;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				scanf("%d",&a[i][j]);
		memset(c[s],0,sizeof(c[s]));
		c[s][x][y] = 1;
		while(s > 1) {
			memset(sum,0,sizeof(sum));
			for(int i = 1; i <= n; i ++) {
				for(int j = 1; j <= m; j ++) {
					sum[i][j] = sum[i][j - 1] + c[s][i][j];
					c[s - 1][i][j] = 0;
					//c[s - 1][i][j] = c[s][i][j];
				}
			}
			int y1,y2;
			for(int i = 1; i <= n; i ++) {
				for(int j = 1; j <= m; j ++) {
					for(int k = 0; k < s && i + k <= n; k ++) {
						x = i + k,y2 = (s - 1) - k + j,y1 = j - ((s - 1) - k);
						if(y2 > m) y2 = m;
						if(y1 < 1) y1 = 1;
						c[s - 1][i][j] += sum[x][y2] - sum[x][y1 - 1];
					}
					for(int k = 1; k < s && i - k > 0; k ++) {
						x = i - k;
						y2 = (s - 1) - k + j;
						y1 = j - ((s - 1) - k);
						if(y2 > m) y2 = m;
						if(y1 < 1) y1 = 1;
						c[s - 1][i][j] += sum[x][y2] - sum[x][y1 - 1];
					}
				}
			}
			for(int i = 1; i <= n; i ++)
				for(int j = 1; j <= m; j ++)
					c[s - 1][i][j] %= MOD;
			s --;
		}
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				//if (i == sx && j == sy) c[1][i][j]--;
				ans = (ans + 1LL * c[1][i][j] * a[i][j]) % MOD;
			}
		}
		if(ans < 0) ans += MOD;
		printf("Case %d: %I64d\n", cas, ans);
	}	
	return 0;
}
