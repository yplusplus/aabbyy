#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
const int N = 110;
int f[N][N];
int a[N][N];
int dp[N][N][4];

void update(int &x,int y)
{
	x = max(x,y);
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++)
				f[i][j] = oo;
			f[i][i] = 0;
		}
		for(int i = 0; i < n; i ++) {
			scanf("%d%d%d",&a[i][1],&a[i][2],&a[i][3]);
			int x,y,z;
			scanf("%d",&x);
			while(x --) {
				scanf("%d%d",&y,&z);
				f[i][y] = z;
			}
		}
		for(int k = 0; k < n; k ++)
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < n; j ++)
					f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
		for(int i = 0; i <= m; i ++)
			for(int j = 0; j <= n; j ++)
				for(int k = 0; k < 4; k ++)
					dp[i][j][k] = -oo;
		for(int i = 0; i < n; i ++) {
			f[i][i] = oo;
			for(int j = 0; j < n; j ++)
				if(i == j) continue;
				else f[i][i] = min(f[i][i],f[i][j] + f[j][i]);
		}
		dp[1][0][1] = 0;
	//	cout << m << " " << f[0][0] << " " << a[1][0] << endl;
		for(int i = 1; i < m; i ++) {
			for(int j = 0; j < n; j ++) {
				for(int k = 1; k < 4; k ++) {
					int cost = dp[i][j][k] + a[j][k];
					update(dp[i + 1][j][min(3,k + 1)],cost);
					for(int r = 0; r < n; r ++) {
						if(cost >= f[j][r] && cost >= 0) update(dp[i + 1][r][1],cost - f[j][r]);
					}
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++) {
			for(int j = 1; j <= 3; j ++) {
				ans = max(ans,dp[m][i][j]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
