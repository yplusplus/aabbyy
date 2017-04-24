#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510;
int visit[N][N],a[N],b[N];

int main()
{
	int t,n,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= m; i ++)
			scanf("%d",&a[i]);
		for(int i = 1; i <= m; i ++)
			scanf("%d",&b[i]);
		for(int i = 1; i <= m; i ++)
			visit[a[i]][b[i]] = visit[b[i]][a[i]] = 1;
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = i + 1; j <= n; j ++) 
				ans += visit[i][j];
		printf("%.3lf\n",1.0 * ans / n);
	}
	return 0;
}



