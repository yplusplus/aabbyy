#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct point
{
	int x,y;
	friend bool operator < (const point &p,const point &q) {
		if(p.y != q.y) return p.y > q.y;
		return p.x < q.x;
	}
}a[110];

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) scanf("%d",&a[i].x);
		for(int i = 1; i <= n; i ++) scanf("%d",&a[i].y);
		sort(a + 1,a + n + 1);
		int t = 0,ans = 0;
		for(int i = 1; i <= n; i ++) {
			ans = max(ans, t + a[i].x + a[i].y);
			t += a[i].x;
		}
		printf("%d\n",ans);
	}
	return 0;
}

