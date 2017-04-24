#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct point
{
	int x,y;
	friend bool operator < (const point &p,const point &q) {
		if(p.x == q.x) return p.y < q.y;
		return p.x < q.x;
	}
}a[N];

int main()
{
	int n;
	bool flag = false;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++) {
			a[i].y = i;
			scanf("%d",&a[i].x);
		}
		if(flag) printf("\n");
		flag = true;
		sort(a + 1,a + n + 1);
		for(int i = 1; i <= n; i += 2)
			printf("%d %d\n",a[i].y,a[i + 1].y);
	}
	return 0;
}
