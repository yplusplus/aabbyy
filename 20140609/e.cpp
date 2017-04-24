#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int eps = 1002;
int sum[N][N];
struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
	void read() {
		scanf("%d%d",&x,&y);
	}
}a[500010];

int get_S(int x1,int y1,int x2,int y2)
{
	return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
}

int x,y;
bool check(int tx,int ty)
{
	return tx >= 1 && tx <= x && ty >= 1 && ty <= y;
}

int main()
{
	int n,d,r;
	int cas = 0;
	while(scanf("%d%d%d%d",&x,&y,&n,&r) != EOF) {
		if(!x && !y && !n && !r) break;
		memset(sum,0,sizeof(sum));
		for(int i = 1; i <= n; i ++) {
			a[i].read();
			sum[a[i].x + a[i].y][a[i].y - a[i].x + eps] ++;
		}
		for(int i = 1; i < N; i ++)
			for(int j = 1; j < N; j ++)
				sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
		printf("Case %d:\n",++ cas);
		while(r --) {
			scanf("%d",&d);
			int tot = -1,ansx = -1,ansy = -1;
			for(int j = 1; j <= y; j ++) {
				for(int i = 1; i <= x; i ++) {
					int x1 = i + j - d,x2 = i + j + d;
					int y1 = j - i + eps - d,y2 = j - i + eps + d;
					x1 = max(x1,1),x2 = min(x2,N - 1);
					y1 = max(y1,1),y2 = min(y2,N - 1);
					if(get_S(x1,y1,x2,y2) > tot) {
						tot = get_S(x1,y1,x2,y2);
						ansx = i,ansy = j;
					}
					else if(get_S(x1,y1,x2,y2) == tot) {
						if(ansy > j || (ansy == j && ansx > i)) {
							ansx = i,ansy = j;
						}
					}
				}
			}
			printf("%d (%d,%d)\n",tot,ansx,ansy);
		}
	}
	return 0;
}
