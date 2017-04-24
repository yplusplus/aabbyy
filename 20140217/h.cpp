#include <bits/stdc++.h>
using namespace std;

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
};

int solve(int n,point a[])
{
	stack<int> stk[15];
	for(int i = n; i >= 1; i --) stk[1].push(i);
	int ans = 0;
	int pre = 0;
	while(1) {
		for(int i = 2; i <= 3; i ++) if(stk[i].size() == n) return ans;
		for(int i = 1; i <= 6; i ++) {
		//	cout << i << " " << a[i].x << " " << a[i].y << endl;
			int x = a[i].x,y = a[i].y;
			if(stk[x].empty()) continue;
			if(stk[x].top() == pre) continue;
		//	cout << "enter " << i << endl;
			if(stk[y].empty() || stk[y].top() > stk[x].top()) {
				ans ++;
				pre = stk[x].top();
				stk[y].push(stk[x].top());
				stk[x].pop();
				break;
				//cout << ans << " " << x << " " << y << endl;
			}
		}
	}

}

int main()
{
//	freopen("out", "w", stdout);
/*
	point b[15];
	int a[10];
	int tot = 0;
	for(int i = 1; i <= 6; i ++) a[i] = i;
	for(int i = 1; i <= 3; i ++)
		for(int j = 1; j <= 3; j ++)
			if(i == j) continue;
			else b[++ tot] = point(i,j);
	do {
		for(int i = 1; i <= 6; i ++)
			printf("%d->%d\n",b[a[i]].x,b[a[i]].y);
		for(int i = 1; i <= 5; i ++) {
			point c[15];
			for(int j = 1; j <= 6; j ++)
				c[j] = b[a[j]];
			cout << i << " : " << solve(i,c) << endl;
		}
		printf("\n\n");
	}while(next_permutation(a + 1, a + 7));
	return 0;
	*/
	int n;
	while(scanf("%d",&n) != EOF) {
		point a[15];
		for(int i = 1; i <= 6; i ++) {
			char s[5];
			scanf("%s",s);
			a[i].x = s[0] - 'A' + 1;
			a[i].y = s[1] - 'A' + 1;
		}
		if(n == 1) {
			printf("1\n");
			continue;
		}
	//	for(int i = 1; i <= 6; i ++)
	//		cout << a[i].x << " " << a[i].y << endl;
		long long ans = 1;
		int x = solve(2,a);
		int y = solve(3,a);
		//cout << x << " " << y << endl;
		if(y == 3 * x) {
			ans = 1;
			for(int i = 2; i <= n; i ++)
				ans = ans * 3;
		}
		else if(y == 2 * x + 1) {
			for(int i = 2; i <= n; i ++)
				ans = 2 * ans + 1;
		}
		else if(y == 3 * x + 2) {
			for(int i = 2; i <= n; i ++)
				ans = 3 * ans + 2;
		}
		printf("%lld\n",ans);
	}
	return 0;

}
