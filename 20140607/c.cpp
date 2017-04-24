#include <bits/stdc++.h>
using namespace std;

const int N = 25;
const int oo = 500000000;
int dp[2][1 << 18][18];
int f[N][N];
int bits[1 << 18];
int dis[18][1 << 18][18];
//int maps[18][1 << 18][18];
void update(int &x,int y)
{
	x = min(x,y);
}

int main()
{
	int cas = 0;
	for(int i = 1; i < (1 << 18); i ++)
		bits[i] = bits[i >> 1] + (i & 1);
	int n,m,x,y,z;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++) {
				f[i][j] = oo;
			}
			f[i][i] = 0;
		}
		while(m --) {
			scanf("%d%d%d",&x,&y,&z);
			if(f[x][y] > z) f[x][y] = f[y][x] = z;
		}
		for(int k = 0; k < n; k ++)
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < n; j ++)
					f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
		for(int i = 0; i < (1 << (n - 2)); i ++)
			for(int j = 0; j < n - 2; j ++)
				dp[0][i][j] = dp[1][i][j] = oo;
		for(int i = 0; i < n - 2; i ++) dp[0][1 << i][i] = f[0][i + 1];
		for(int i = 1; i < (1 << (n - 2)); i ++) {
			if(bits[i] >= (n - 2) / 2) continue;
			for(int j = 0; j < n - 2; j ++) {
				if(dp[0][i][j] == oo) continue;
				for(int k = 0; k < n - 2; k ++) {
					if(!(i & (1 << k))) update(dp[0][i | (1 << k)][k],dp[0][i][j] + f[j + 1][k + 1]);
				}
			}
		}
		for(int i = 0; i < n - 2; i ++) dp[1][1 << i][i] = f[n - 1][i + 1];
		for(int i = 0; i < (1 << (n - 2)); i ++) {
			if(bits[i] >= (n - 2) / 2) continue;
			for(int j = 0; j < n - 2; j ++) {
				if(dp[1][i][j] == oo) continue;
				for(int k = 0; k < n - 2; k ++) {
					if(!(i & (1 << k))) update(dp[1][i | (1 << k)][k],dp[1][i][j] + f[j + 1][k + 1]);
				}
			}
		}
		int ans = oo;
		cout << "Case " << ++cas << ": ";
		if(n == 3) {
			cout << 2 * (f[0][1] + f[1][2]) << endl;
			continue;
		}
		for(int i = 0; i < n - 2; i ++)
			for(int j = 0; j < (1 << (n - 2)); j ++)
				for(int k = 0; k < n - 2; k ++)
					dis[i][j][k] = oo;
		for(int i = 0; i < n - 2; i ++) {
			dis[i][1 << i][i] = 0;
			for(int j = 0; j < (1 << (n - 2)); j ++)
				for(int k = 0; k < n - 2; k ++)
					if(dis[i][j][k] == oo) continue;
					else {
						for(int r = 0; r < n - 2; r ++) {
							if(j & (1 << r)) continue;
							update(dis[i][j | (1 << r)][r],dis[i][j][k] + f[k + 1][r + 1]);
						}
					}
		}
		for(int i = 0; i < (1 << (n - 2)); i ++) {
			if(bits[i] != (n - 2) / 2) continue;
			int mask = ((1 << (n - 2)) - 1) ^ i;
			int a[2][N];
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < n; k ++)
					a[j][k] = oo;
			for(int j = 0; j < n - 2; j ++) {
				if(i & (1 << j)) {
					for(int k = 0; k < n - 2; k ++) {
						if(mask & (1 << k)) {
							update(a[0][j],dis[j][mask | (1 << j)][k] + f[k + 1][n - 1]);
						}
					}
				}
			}
			for(int j = 0; j < n - 2; j ++) {
				if(i & (1 << j)) {
					for(int k = 0; k < n - 2; k ++) {
						if(mask & (1 << k)) {
							update(a[1][j],dis[j][mask | (1 << j)][k] + f[k + 1][0]);
						}
					}
				}
			}
			for(int j = 0; j < n - 2; j ++) {
				for(int k = 0; k < n - 2; k ++) {
					if(i & (1 << j) && (i & (1 << k))) {
						update(ans,dp[0][i][j] + dp[1][i][k] + a[0][j] + a[1][k]);
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
