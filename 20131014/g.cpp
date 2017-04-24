#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int fx[10][110][110],fy[10][110][110];
int cd[4010];
int visit[110][110];

void solve(int x,int y,int r)
{
	int tx = x,ty = y;
	for(int i = 1; i <= r; i ++) {
		tx = fx[cd[i]][x][y];
		ty = fy[cd[i]][x][y];
		x = tx,y = ty;
	}
	visit[x][y] = 1;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= 4; i ++) {
		for(int j = 1; j <= n; j ++) {
			for(int k = 1; k <= m; k ++) {
				scanf("%d%d",&fx[i][j][k],&fy[i][j][k]);
			}
		}
	}
	int r;
	scanf("%d",&r);
	for(int i = 1; i <= r; i ++)
		scanf("%d",&cd[i]);
	memset(visit,0,sizeof(visit));
	for(int i = 1; i <= n; i ++) 
		for(int j = 1; j <= m; j ++)
			solve(i,j,r);
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			ans += visit[i][j];
	printf("%d\n",ans);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(visit[i][j]) printf("%d %d\n",i,j);
	return 0;
}

