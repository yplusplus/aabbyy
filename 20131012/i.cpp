#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int t,n;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d",&n);
		printf("Case #%d: %.2lf\n",cas,1.0 * n * (n - 1) / 4);
	}
	return 0;
}

