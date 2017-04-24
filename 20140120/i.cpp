#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int n,m;
	int flag[1010],x;
	memset(flag,0,sizeof(flag));
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; i ++) {
		scanf("%d",&x);
		flag[x] = 1;
	}
	int ans = 0;
	for(int i = 2; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++)
			if(flag[1] + flag[i] + flag[j]) {
				int left = m - flag[1] - flag[i] - flag[j];
				if(left < (n - 3) / 3) continue;
				ans ++;
			}
	cout << ans << endl;
	return 0;
}
