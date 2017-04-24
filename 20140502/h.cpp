#include <bits/stdc++.h>
using namespace std;

const int N = 66;
int n;
const int mod = 1000000000;
struct bignum {
	int a[15];
	bignum() {
		memset(a,0,sizeof(a));
	}
	void operator += (const bignum &p) {
		for(int i = 0; i < 15; i ++) a[i] += p.a[i];
		for(int i = 0; i < 15; i ++)
			if(a[i] >= mod) {
				a[i + 1] ++;
				a[i] -= mod;
			}
	}
	void output() {
		int i = 14;
		for(i; i >= 0; i --)
			if(a[i]) break;
		if(i == -1) i ++;
		printf("%d",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%09d",a[i]);
		printf("\n");
	}

} dp[N][N][N];

int main() {
	dp[0][0][0].a[0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			for (int k = 0; k <= j; k++) {
				if (i + 1 < N) dp[i + 1][j][k] += dp[i][j][k];
				if (j + 1 < N) dp[i][j + 1][k] += dp[i][j][k];
				if (k + 1 < N) dp[i][j][k + 1] += dp[i][j][k];
			}
		}
	}
	while (cin >> n) {
		dp[n][n][n].output();
		puts("");
	}
	return 0;
}
