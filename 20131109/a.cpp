#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 210;
char s[N][N];
int a[N][N];

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
}c[55];

int map[N][N];
int bit[1 << 15];
int main()
{
	memset(bit,0,sizeof(bit));
	for(int i = 0; i < (1 << 15); i ++)
		for(int j = 0; j < 15; j ++)
			if(i & (1 << j)) bit[i] ++;
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		for(int i = 1; i <= n; i ++)
			scanf("%s",s[i] + 1);
		for(int i = 0; i <= n + 5; i ++) {
			for(int j = 0; j <= m + 5; j ++) {
				a[i][j] = 0;
				map[i][j] = -1;
			}
		}
		int ct = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(s[i][j] == '#') a[i][j] = 1;
				else {
					map[i][j] = ct;
					c[ct ++] = point(i,j);
				}
		int ans = 255;
		int visit[25];
		int times = 0;
		memset(visit,0,sizeof(visit));
		for(int i = 0; i < ct; i ++) {
			int x = c[i].x;
			int y = c[i].y;
			int dirx,diry;
			for(int k = 0; k < 4; k ++) {
				if(k == 0) dirx = -1,diry = 1;
				if(k == 1) dirx = 1,diry = -1;
				if(k == 2) dirx = 1,diry = 1;
				if(k == 3) dirx = -1,diry = -1;
				x = c[i].x;
				y = c[i].y;
				if(!a[x][y] && !a[x + dirx][y] && !a[x][y + diry]) {
					times = 1;
					memset(visit,0,sizeof(visit));
					for(int j = 0; j < (1 << ct); j ++) {
						if(bit[(1 << i) ^ j] >= ans) continue;
						if(j & (1 << i)) continue;
						++ times;
						x = c[i].x;
						y = c[i].y;
						visit[map[x][y]] = times;
						if(x + dirx >= 1 && x + dirx <= n) visit[map[x + dirx][y]] = times;
						if(y + diry >= 1 && y + diry <= m) visit[map[x][y + diry]] = times;
						bool flag = true;
						for(int r = 0; r < ct; r ++) {
							if(!(j & (1 << r))) continue;
							x = c[r].x;
							y = c[r].y;
							if(!a[x][y] && !a[x - 1][y] && !a[x][y + 1]) {
								visit[map[x][y]] = times;
								if(x) visit[map[x - 1][y]] = times;
								if(y + 1 <= m) visit[map[x][y + 1]] = times;
							}
							else {
								flag = false;
								break;
							}
						}
						if(!flag) continue;
						for(int r = 0; r < ct; r ++)
							if(visit[r] != times) flag = false;
						if(!flag) continue;
						ans = min(ans,bit[(1 << i) ^ j]);
					}
				}
			}
		}
		if(ans > ct) ans = -1;
		if(ct == 0) ans = 0;
		printf("%d\n",ans);
	}
	return 0;
}



