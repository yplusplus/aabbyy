#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50010;
int dp[50010],f[50010];

int main()
{
	int v,n;
	int w1,v1,w2,v2,r;
	while(scanf("%d%d",&v,&n) != EOF) {
		v /= 100;
		memset(dp,0,sizeof(dp));
		while(n --) {
			scanf("%d%d%d%d%d",&w1,&v1,&w2,&v2,&r);
			w1 /= 100;
			w2 /= 100;
			if(r == 1) {
				int w = w1 + w2;
				int vv = v1 + v2;
				for(int i = v; i >= w; i --)
					if(dp[i] < dp[i - w] + vv) dp[i] = dp[i - w] + vv;
			}
			else if(r == 2) {
				for(int i = 0; i <= v; i ++)
					f[i] = dp[i];
				for(int i = v; i >= w1; i --)
					if(dp[i] < f[i - w1] + v1) dp[i] = f[i - w1] + v1;
				for(int i = v; i >= w2; i --)
					if(dp[i] < f[i - w2] + v2) dp[i] = f[i - w2] + v2;
			}
			else {
				for(int i = 0; i <= v; i ++) f[i] = dp[i];
				for(int i = v; i >= w1; i --)
					if(dp[i] < f[i - w1] + v1) dp[i] = f[i - w1] + v1;
				int w = w1 + w2;
				int vv = v1 + v2;
				for(int i = v; i >= w; i --)
					if(dp[i] < f[i - w] + vv) dp[i] = f[i - w] + vv;
			}
		}
		printf("%d\n",dp[v]);
	}
	return 0;
}

