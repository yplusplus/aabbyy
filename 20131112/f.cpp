#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int visit[100010];
int main()
{
	int t,n,x;
	scanf("%d",&t);
	while(t --) {
		scanf("%d",&n);
		memset(visit,0,sizeof(visit));
		while(n --) {
			scanf("%d",&x);
			visit[x] = 1;
		}
		int ans = 0;
		scanf("%d",&n);
		while(n --) {
			scanf("%d",&x);
			visit[x] ++;
			if(visit[x] > 1) ans ++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

