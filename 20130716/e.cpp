#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int t,n,m,r;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d%d",&n,&m,&r);
		long long ans = n + 2LL * m;
		if(!n) {
			printf("Case #%d: %d\n",cas,1);
			continue;
		}
		if(ans + 1 >= 5) ans += 5LL * r;
		printf("Case #%d: %lld\n",cas,ans + 1);
	}
	return 0;
}


