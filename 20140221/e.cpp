#include <bits/stdc++.h>
using namespace std;

int dir[8][2] = {0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,-1,-1,1};
int a[2][110][110];

int main()
{
	int cas = 0;
	int m,n;
	while(scanf("%d%d",&m,&n) != EOF) {
		if(!m && !n) break;
		memset(a,0,sizeof(a));
		int r,x,y;
		scanf("%d",&r);
		while(r --) {
			scanf("%d%d",&x,&y);
			a[0][x][y] = 1;
		}
		scanf("%d",&r);
		for(int k = 0; k < r; k ++) {
			int flag = k & 1;
			for(int i = 0; i < m; i ++) {
				for(int j = 0; j < n; j ++) {
					int tot = 0;
						for(int p = 0; p < 8; p ++) {
							int x = i + dir[p][0];
							int y = j + dir[p][1];
							if(x < 0) {
								x = 0;
								y = j + (n / 2) + dir[p][1];
								y %= n;
							}
							else if(x == m) {
								x = m - 1;
								y = j + (n / 2) + dir[p][1];
								y %= n;
							}
							if(y < 0) y += n;
							else if(y == n) y = 0;
							tot += a[flag][x][y];
						}
					if(!a[flag][i][j] && tot == 3) a[flag ^ 1][i][j] = 1;
					else if(a[flag][i][j] && (tot < 2 || tot > 3)) a[flag ^ 1][i][j] = 0;
					else a[flag ^ 1][i][j] = a[flag][i][j];
					
				}
			}
		}
		int stx = -1,sty = -1,edx = -1,edy = -1;
		int tot = 0;
		for(int i = 0; i < m; i ++)
			for(int j = 0; j < n; j ++) {
				if(a[r & 1][i][j]) {
					tot ++;
					if(stx == -1) stx = i,sty = j;
					edx = i,edy = j;
				}
			}
		printf("Case %d: %d %d %d %d %d\n",++ cas,tot,stx,sty,edx,edy);
	}
	return 0;
}
