#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 10000007;
int c[20010][30];

void init()
{
	memset(c,0,sizeof(c));
	for(int i = 0; i < 20010; i ++) {
		c[i][0] = 1;
		if(i < 30) c[i][i] = 1;
		for(int j = 1; j < i && j < 30; j ++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}

int main()
{
	init();
	int a[25],b[25];
	int n,m,t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%d%d",&n,&m);
		for(int i = 0; i < n; i ++) {
			scanf("%d%d",&a[i],&b[i]);
			m -= a[i];
			b[i] -= a[i];
		}
		printf("Case #%d: ",cas);
		if(m < 0) {
			printf("0\n");
			continue;
		}
		int ans = 0;
		for(int i = 0; i < (1 << n); i ++) {
			int tmp = m;
			int flag = 1;
			for(int j = 0; j < n; j ++) {
				if(i & (1 << j)) {
					flag *= -1;
					tmp -= (b[j] + 1);
				}
			}
			if(tmp < 0) continue;
			ans = (ans + c[tmp + n - 1][n - 1] * flag) % mod;
		}
		if(ans < 0) ans += mod;
		printf("%d\n",ans);
	}
	return 0;
}

