#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n + m; i ++) {
		bool first = true;
		if(n >= i) printf("x%d",i),first = false;
		if(m >= i) {
			if(!first) printf("&");
			printf("y%d",i);
			first = false;
		}
		for(int j = 1; j < i && j <= n; j ++) {
			int k = i - j;
			if(!(k >= 1 && k <= m)) continue;
			if(!first) printf("&");
			printf("(x%d|y%d)",j,k);
			first = false;
		}
		printf("\n");
	};
	return 0;
}
