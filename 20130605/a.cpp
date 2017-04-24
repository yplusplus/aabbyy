#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int n,a[210],m,b[210],visit[210];
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++)
			scanf("%d",&a[i]);
		scanf("%d",&m);
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= m; i ++) {
			scanf("%d",&b[i]);
			visit[b[i]] = 1;
		}
		sort(a + 1,a + n + 1);
		if(a[n] == 0) {
			printf("0.00\n");
			continue;
		}
		if(n == m) {
			printf("inf\n");
			continue;
		}
		double A = 0,B = 0;
		m = 0;
		for(int i = 1; i <= n; i ++) {
			if(visit[i]) m ++,B += a[i];
			else A += a[i];
		}
		double ans = (A + B) * 1.0 / n / (1 - 1.0 * m / n);
		printf("%.2lf\n",ans);
	}
	return 0;
}

