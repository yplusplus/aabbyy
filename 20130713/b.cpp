#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long f[100010];
char s[100010][10];
long long state[1 << 5];

int change(char c)
{
	if(isdigit(c)) return c - '0';
	return c - 'a' + 10;
}

int cbit(int state)
{
	int ans = 0;
	for(int i = 0; i < 4; i ++)
		if(state & (1 << i)) ans ++;
	return ans;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++)
		scanf("%s",s[i]);
	memset(state,0,sizeof(state));
	for(int i = 0; i < 16; i ++) {
		memset(f,0,sizeof(f));
		for(int j = 1; j <= n; j ++) {
			int x = 0;
			for(int k = 0; k < 4; k ++) {
				if(!(i & (1 << k))) continue;
				x = 16 * x + change(s[j][k]);
			}
			f[x] ++;
		}
		for(int j = 0; j < 65536; j ++) {
			state[i] += f[j] * (f[j] - 1) / 2LL;
		}
	}
	long long ff[25];
	for(int i = 15; i >= 0; i --) {
		long long ans = 0;
		for(int j = 0; j < 16; j ++) {
			if((j & i) == i) {
				if(cbit(j) % 2 == cbit(i) % 2) ans += state[j];
				else ans -= state[j];
			}
		}
		ff[i] = ans;
	}
	long long ans[15];
	memset(ans,0,sizeof(ans));
	for(int i = 0; i < 16; i ++) {
		ans[cbit(i)] += ff[i];
	}
	for(int i = 1; i <= 4; i ++) {
		printf("%I64d",ans[4 - i]);
		if(i == 4) printf("\n");
		else printf(" ");
	}
	return 0;
}




