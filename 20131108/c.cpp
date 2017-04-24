#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool dp[1 << 16];
int f[1 << 16];
int sum[1 << 16];
int rev[1 << 16];
int lowbit(int x)
{
	return x & (-x);
}

int main()
{
	for(int i = 0; i < 16; i ++)
		rev[1 << i] = i;
	int a[20];
	int n;
	while(scanf("%d",&n) != EOF) {
		for(int i = 0; i < n; i ++)
			scanf("%d",&a[i]);
		sort(a,a + n);
		for(int i = 1; i < n; i ++)
			a[i - 1] = a[i];
		n --;
		if(n < 4) {
			printf("-1\n");
			continue;
		}
		memset(f,0,sizeof(f));
		sum[0] = 0;
		for(int i = 1; i < (1 << n); i ++) {
			sum[i] = sum[i ^ lowbit(i)] + a[rev[lowbit(i)]];
		}
		for(int i = 1; i < (1 << n); i ++) {
			if(sum[i] % 2 == 0) {
				bool flag = false;
				for(int j = (i - 1) & i; j; j = (j - 1) & i)
					if(sum[j] * 2 == sum[i]) {
						flag = true;
						break;
					}
				if(!flag) continue;
				int x = sum[i] / 2;
				int mask = ((1 << n) - 1) ^ i;
				for(int j = mask; ; j = (j - 1) & mask) {
					f[j ^ i] = max(f[j ^ i],x);
					if(!j) break;
				}
//				cout << i << " " << x << endl;
			}
		}
		int ans = 0;
		for(int i = 1; i < (1 << n); i ++)
			ans = max(ans,f[i] * f[((1 << n) - 1) ^ i]);
		if(ans == 0) ans = -1;
		printf("%d\n",ans);
	}
	return 0;
}
