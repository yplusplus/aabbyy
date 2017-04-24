#include <bits/stdc++.h>
using namespace std;

const int N = 30000010;
int ans[N];

bool check(int x,int y,int t)
{
	return (x ^ y) == t;
}

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.x != q.x) return p.x < q.x;
		return p.y < q.y;
	}
}a[100010];
int main()
{
	int tot = 0;
	/*
	prime();
	for(int i = 3; i < N; i ++) {
		sum = 0;
		cal(i);
		ans[i] = ans[i - 1] + i;
	}
	*/
	for(int i = 3; i < N; i += 2) {
		int x = i - 1,t = 1;
		for(int j = i; j < N; j += i,x += (i - 1),t ++)
			if(check(j,x,t)) {
				ans[j] ++;
//				cout << j << " " << x << endl;
//				a[++ tot] = point(j,x);
			}
	}
//	sort(a + 1,a + tot + 1);
//	for(int i = 1; i <= tot; i ++) cout << a[i].x << " " << a[i].y << endl;
	for(int i = 1; i < N; i ++) ans[i] += ans[i - 1];
	int t,n;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d",&n);
		printf("Case %d: %d\n",cas,ans[n]);
	}
	return 0;
}
	
