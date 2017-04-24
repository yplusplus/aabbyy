#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 110;
int pre[N],ind[N],flag[N],c[N];

int find(int x)
{
	if(pre[x] == -1) return x;
	return pre[x] = find(pre[x]);
}

int main()
{
	int a[110][110];
	int n,m,x;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n; i ++) {
			flag[i] = 0;
			ind[i] = 0;
			pre[i] = -1;
			c[i] = 1;
		}
		memset(a,0,sizeof(a));
		bool f = true,ff = false;
		int tot = n;
		for(int i = 1; i <= m; i ++) {
			scanf("%d",&x);
			if(a[i][x] || a[x][i]) continue;
			a[x][i] = a[i][x] = 1;
			ind[i] ++,ind[x] ++;
			if(ind[i] > 2) f = false;
			if(ind[x] > 2) f = false;
			int fx = find(i);
			int fy = find(x);
			if(fx == fy) {
				flag[fx] = 1;
				ff = true;
				continue;
			}
			pre[fx] = fy;
			c[fy] += c[fx];
			tot --;
		}
		if(!f) {
			printf("0\n");
			continue;
		}
		if(ff && tot > 1) {
			printf("0\n");
			continue;
		}
		int mod = 1000000007;
		int ans = 1;
		for(int i = 1; i < tot; i ++)
			ans = 1LL * ans * i % mod;
		for(int i = 1; i <= n; i ++)
			if(pre[i] == -1 && c[i] > 1) ans = ans * 2 % mod;
		if(n == 2) ans = 1;
		printf("%d\n",ans);
	}
	return 0;
}
