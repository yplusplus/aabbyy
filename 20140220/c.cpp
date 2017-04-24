#include <bits/stdc++.h>
using namespace std;

struct point
{
	int a,b,x,y;
	void read() {
		scanf("%d%d%d%d",&a,&b,&x,&y);
	}
}a[25];

int dp[1 << 15],IV[1 << 15],TV[1 << 15];

void update(int &x,int y)
{
	if(x < y) x = y;
}

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) {
		for(int i = 0; i < n; i ++) a[i].read();
		memset(dp,0,sizeof(dp));
		memset(IV,0,sizeof(IV));
		memset(TV,0,sizeof(TV));
		for(int i = 1; i < (1 << n); i ++) {
			for(int j = 0; j < n; j ++) {
				if(i & (1 << j)) {
					TV[i] = TV[i ^ (1 << j)] + a[j].a * a[j].x;
					IV[i] = IV[i ^ (1 << j)] + a[j].b * a[j].y;
				}
			}
		}
		for(int i = 0; i < (1 << n); i ++) {
			for(int j = 0; j < n; j ++) {
				if(i & (1 << j)) continue;
				update(dp[i ^ (1 << j)],dp[i] + a[j].x * IV[i] + a[j].y * TV[i ^ (1 << j)]);
				update(dp[i ^ (1 << j)],dp[i] + a[j].y * TV[i] + a[j].x * IV[i ^ (1 << j)]);
			}
		}
		printf("%d\n",dp[(1 << n) - 1]);
	}
	return 0;
}

