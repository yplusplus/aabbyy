#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	long long a[10010];
	int n = 3;
	for(int i = 0; i < n; i ++) cin >> a[i];
	int ans = 0;
	while(1) {
		sort(a,a + n);
		bool flag = false;
		for(int i = 1; i < n; i ++) {
			if(a[i] == a[i - 1]) {
				ans ++;
				flag = true;
				break;
			}
		}
		if(flag) break;
		long long mi = 1LL << 60;
		for(int i = 1; i < n; i ++) {
			mi = min(mi,a[i] - a[i - 1]);
		}
		a[n ++] = mi;
		ans ++;
	}
	printf("%d\n",ans);
	return 0;
}

