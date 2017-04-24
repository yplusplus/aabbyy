#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
struct point
{
	long long x,y;
	int id;
	friend bool operator < (const point &p,const point &q) {
		if(p.x != q.x) return p.x > q.x;
		return p.y > q.y;
	}
	point() {}
	point(long long x,long long y,int id):x(x),y(y),id(id) {}
}a[N];

int main()
{
	int c[6][6];
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		int n;
		scanf("%d",&n);
		int cnt = 0;
		for(int k = 1; k <= n; k ++) {
			for(int i = 1; i <= 4; i ++) {
				for(int j = 1; j <= 4; j ++) {
					scanf("%d",&c[i][j]);
				}
			}
			int x1 = c[1][2],x2 = c[2][1];
			if(x1 < x2) swap(x1,x2);
			int y1 = c[3][4],y2 = c[4][3];
			if(y1 > y2) swap(y1,y2);
			int x = max(x1,y1),y = max(x2,y2);
			if(x < y) swap(x,y);
			a[++ cnt] = point(x,y,k);
			x1 = c[1][3],x2 = c[3][1];
			y1 = c[2][4],y2 = c[4][2];
			if(x1 < x2) swap(x1,x2);
			if(y1 > y2) swap(y1,y2);
			x = max(x1,y1),y = max(x2,y2);
			if(x < y) swap(x,y);
			a[++ cnt] = point(x,y,k);
			x1 = c[1][4],x2 = c[4][1];
			y1 = c[2][3],y2 = c[3][2];
			if(x1 < x2) swap(x1,x2);
			if(y1 > y2) swap(y1,y2);
			x = max(x1,y1),y = max(x2,y2);
			if(x < y) swap(x,y);
			a[++ cnt] = point(x,y,k);
		}
		sort(a + 1,a + cnt + 1);
		n = min(cnt,6);
		a[0] = point(0,0,0);
		long long ans = 0;
		for(int i = 1; i <= n; i ++) {
			for(int j = 0; j <= n; j ++) {
				if(i == j) continue;
				if(a[i].id == a[j].id) continue;
				for(int k = 1; k <= n; k ++) {
					if(i == k) continue;
					if(j && j == k) continue;
					for(int r = 0; r <= n; r ++) {
						if(a[k].id == a[r].id) continue;
						if(k == r) continue;
						if(r == i) continue;
						if(r && r == j) continue;
						for(int p = 1; p <= n; p ++) {
							if(p == i) continue;
							if(p == j) continue;
							if(p == k) continue;
							if(p == r) continue;
							for(int q = 0; q <= n; q ++) {
								if(a[p].id == a[q].id) continue;
								if(q == p) continue;
								if(q == i) continue;
								if(q && q == j) continue;
								if(q == k) continue;
								if(q && q == r) continue;
								long long sum = 0;
								sum += max(a[i].x,a[j].y) + max(a[i].y,a[j].x);
								sum += max(a[k].x,a[r].y) + max(a[k].y,a[r].x);
								sum += max(a[p].x,a[q].y) + max(a[p].y,a[q].x);
								ans = max(ans,sum);
							}
						}
					}
				}
			}
		}
		printf("Case #%d: %lld\n",cas,ans);
	}
	return 0;
}
