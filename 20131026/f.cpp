#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
int a[N];
int lowbit(int x)
{
	return x & (-x);
}

void insert(int x)
{
	for(int i = x; i < N; i += lowbit(i))
		a[i] ++;
}

int query(int x)
{
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += a[i];
	return ans;
}

int ans[N];
int main()
{
	memset(a,0,sizeof(a));
	int n,m,r;
	scanf("%d%d",&n,&m);
	scanf("%d",&r);
	for(int i = 1; i <= n - m; i ++) {
	   ans[i] = 1;
	   insert(1);
	}
	int now = 2;
	for(int i = n - m + 1; i <= n; i ++) {
		int cc = query(now - 1);
		if(1LL * cc * 100 >= (i - 1) * r) {
			ans[i] = now;
			insert(now);
		}
		else {
			ans[i] = now + 1;
			insert(now + 1);
			++ now;
		}
	}
	long long sum = 0;
	for(int i = 1; i <= n; i ++) sum += ans[i];
	cout << sum << endl;
	for(int i = 1; i <= n; i ++) {
		printf("%d",ans[i]);
		if(i == n) printf("\n");
		else printf(" ");
	}
	return 0;
}
