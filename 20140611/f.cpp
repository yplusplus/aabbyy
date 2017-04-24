#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int SIZE = 30;
const int mod = 1000000000;
struct bignum
{
	int a[SIZE];
	bignum() {
		memset(a,0,sizeof(a));
	}
	void operator += (const bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++)
			c.a[i] = a[i] + p.a[i];
		for(int i = 0; i < SIZE; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		for(int i = 0; i < SIZE; i ++)
			a[i] = c.a[i];
	}
	void output() {
		int i = SIZE - 1;
		for(i; i >= 0; i --) {
			if(a[i]) break;
		}
		if(i == -1) i ++;
		printf("%d",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%09d",a[i]);
		printf("\n");
	}
}dp[N][N][2][2];

int main()
{
	dp[1][0][1][1].a[0] = 1;
	dp[0][1][0][0].a[0] = 1;
	for(int i = 0; i < 505; i ++)
		for(int j = 0; j < 505; j ++)
			for(int k = 0; k < 2; k ++)
				for(int r = 0; r < 2; r ++)
					if(!k) dp[i + 1][j][1][r] += dp[i][j][k][r];
					else {
						dp[i + 1][j][1][r] += dp[i][j][k][r];
						dp[i][j + 1][0][r] += dp[i][j][k][r];
					}
	int n;
	int cas = 0;
	while(scanf("%d",&n) != EOF) {
		if(!n) break;
		printf("Case %d: ",++ cas);
		if(n < 4 || n & 1) {
			printf("0\n");
			continue;
		}
		int x = (n + 4) / 2;
		int y = (n - 4) / 2;
		bignum ans;
		for(int i = 0; i < 2; i ++)
			for(int j = 0; j < 2; j ++)
				if(!i && !j) continue;
				else ans += dp[x][y][i][j];
		ans.output();
	}
	return 0;
}

