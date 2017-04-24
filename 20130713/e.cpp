#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[110],pre[110];

int main()
{
	int n;
	scanf("%d",&n);
	a[0] = 0;
	for(int i = 1; i <= n; i ++)
		scanf("%d",&a[i]);
	memset(pre,0,sizeof(pre));
	sort(a + 1,a + n + 1);
	for(int i = 1; i <= n; i ++) {
		pre[i] = pre[i - 1] + a[i];
	}
	printf("%d\n",pre[n] + a[n]);
	return 0;
}


