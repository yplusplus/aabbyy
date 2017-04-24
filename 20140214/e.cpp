#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct point
{
	int x1,y1,x2,y2,cd;
	void read() {
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&cd);
	}
	bool in(int x,int y) {
		return x >= x1 && x <= x2 && y >= y1 && y <= y2;
	}
}a[N];

int c[300][300];

int main()
{
	int n,m,r;
	while(scanf("%d%d",&m,&n) != EOF) {
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < m; j ++)
				scanf("%d",&c[j][i]);
		scanf("%d",&r);
		for(int i = 1; i <= r; i ++) {
			a[i].read();
		}
		int x,y;
		scanf("%d%d",&x,&y);
		for(int i = r; i >= 1; i --) {
			if(a[i].cd < 4) continue;
			if(a[i].cd == 4) {
				int newx = a[i].x1 + a[i].x2 - x,newy = y;
				if(a[i].in(newx,newy)) x = newx,y = newy;
			}
			else {
				int newx = x,newy = a[i].y1 + a[i].y2 - y;
				if(a[i].in(newx,newy)) x = newx,y = newy;
			}
		}
		int ans = c[x][y];
		for(int i = 1; i <= r; i ++)
			if(a[i].in(x,y)) {
				if(a[i].cd == 1) ans = -ans;
				else if(a[i].cd == 2) ans ++;
				else if(a[i].cd == 3) ans --;
				else if(a[i].cd == 4) {
					x = a[i].x1 + a[i].x2 - x;
				}
				else y = a[i].y1 + a[i].y2 - y;
			}

		printf("%d\n",ans);
	}
	return 0;
}
