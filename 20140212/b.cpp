#include <bits/stdc++.h>
using namespace std;

const int N = 510;
int a[N][N];
int sum[N][N];
int ans[N][N];

int get_sum(int x1,int y1,int x2,int y2)
{
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

int main()
{
	int n,m,p,q;
	while(scanf("%d%d",&n,&m) != EOF) {
		int mx = 0,mix = 255;
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= m; j ++) {
				scanf("%d",&a[i][j]);
			}
		}
		scanf("%d%d",&p,&q);
		int lenx = p / 2,leny = q / 2;
		int mid = p * q / 2 + 1;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(i - lenx >= 1 && i + lenx <= n && j - leny >= 1 && j + leny <= m) {
					ans[i][j] = -1;
					mx = max(mx,a[i][j]);
					mix = min(mix,a[i][j]);
				}
				else ans[i][j] = a[i][j];
		for(int k = mix; k <= mx; k ++) {
			for(int j = 0; j <= n; j ++) sum[j][0] = 0;
			for(int j = 0; j <= m; j ++) sum[0][j] = 0;
			for(int i = 1; i <= n; i ++)
				for(int j = 1; j <= m; j ++)
					if(a[i][j] <= k) sum[i][j] = 1;
					else sum[i][j] = 0;
			for(int i = 1; i <= n; i ++)
				for(int j = 1; j <= m; j ++)
					sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + sum[i][j];
			for(int i = 1; i + p - 1 <= n; i ++)
				for(int j = 1; j + q - 1 <= m; j ++)
					if(ans[i + lenx][j + leny] == -1 && get_sum(i,j,i + p - 1,j + q - 1) >= mid)
						ans[i + lenx][j + leny] = k;
		}
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= m; j ++) {
				printf("%d",ans[i][j]);
				if(j == m) printf("\n");
				else printf(" ");
			}
		}
		printf("\n");
	}
		
	return 0;
}
