#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("ghanophobia.in","r",stdin);
	int n,x,y;
	scanf("%d",&n);
	for(int cas = 1; cas <= n; cas ++) {
		scanf("%d:%d",&x,&y);
		printf("Case %d: ",cas);
		if(x - y > 5) printf("YES\n");
		else if(x - y == 5) {
			if(y == 1) printf("PENALTIES\n");
			else if(y == 0) printf("YES\n");
			else printf("NO\n");
		}
		else printf("NO\n");
	}
	return 0;
}
