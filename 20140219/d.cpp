#include <bits/stdc++.h>
using namespace std;

struct point
{
	char s[35];
	int cost,x1,y1,x2,y2;
	void read() {
		scanf("%s%d%d%d%d",s,&x1,&y1,&x2,&y2);
		cost = 0;
	}
	friend bool operator < (const point &p,const point &q) {
		if(p.cost != q.cost) return p.cost < q.cost;
		return strcmp(p.s,q.s) < 0;
	}
}c[35];

int dir[4][2] = {0,1,0,-1,1,0,-1,0};
int visit[12][12],a[12][12],b[12][12],f[12][12],T[12][12];

void cal(int x1,int y1,int x2,int y2)
{
	memset(a,0,sizeof(a));
	memset(f,-1,sizeof(f));
	for(int i = x1; i <= x2; i ++)
		for(int j = y1; j <= y2; j ++)
			a[i][j] = 1000000,f[i][j] = 0;
	int times = 0;
	while(1) {
		bool flag = true;
		for(int i = 1; i <= 10 && flag; i ++)
			for(int j = 1; j <= 10 && flag; j ++)
				if(visit[i][j] && !a[i][j]) {
					flag = false;
					break;
				}
		if(flag) break;
		++ times;
		for(int i = 1; i <= 10; i ++)
			for(int j = 1; j <= 10; j ++)
				b[i][j] = a[i][j];
		for(int i = 1; i <= 10; i ++)
			for(int j = 1; j <= 10;  j ++)
				if(visit[i][j]) {
					int tmp = a[i][j] / 1000;
					for(int k = 0; k < 4; k ++) {
						int tx = i + dir[k][0];
						int ty = j + dir[k][1];
						if(!visit[tx][ty]) continue;
						b[tx][ty] += tmp;
						b[i][j] -= tmp;
					}
				}
		for(int i = 1; i <= 10; i ++)
			for(int j = 1; j <= 10; j ++) {
				a[i][j] = b[i][j];
				if(a[i][j] && visit[i][j] && f[i][j] == -1) f[i][j] = times;
			}
	}
}

int main()
{
	int cas = 0;
	int n;
	while(scanf("%d",&n) != EOF) {
		if(!n) break;
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= n; i ++) {
			c[i].read();
			for(int j = c[i].x1; j <= c[i].x2; j ++)
				for(int k = c[i].y1; k <= c[i].y2; k ++)
					visit[j][k] = 1;
		}
		memset(T,0,sizeof(T));
		for(int i = 1; i <= n; i ++) {
			cal(c[i].x1,c[i].y1,c[i].x2,c[i].y2);
			for(int j = 1; j <= 10; j ++)
				for(int k = 1; k <= 10; k ++)
					if(visit[j][k]) T[j][k] = max(T[j][k],f[j][k]);
		}
		for(int i = 1; i <= n; i ++)
			for(int j = c[i].x1; j <= c[i].x2; j ++)
				for(int k = c[i].y1; k <= c[i].y2; k ++)
					c[i].cost = max(c[i].cost,T[j][k]);
		sort(c + 1,c + n + 1);
		printf("Case Number %d\n",++ cas);
		for(int i = 1; i <= n; i ++)
			printf("   %s   %d\n",c[i].s,c[i].cost);
	}
	return 0;
}

