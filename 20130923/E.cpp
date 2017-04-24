#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
const int N = 50010;
int dp[155][N];
int aa[N * 2];

int pow(int a,int b)
{
	int ans = 1;
	while(b) {
		if(b & 1) ans = ans * 1LL * a % mod;
		a = 1LL * a * a % mod;
		b /= 2;
	}
	return ans;
}

void solve(int n,int m)
{
	int x,y,z;
	while(m --) {
		scanf("%d%d%d",&x,&y,&z);
		int ans = 1;
		if(x > z) z += n;
		else if((z - x) % y) z += n;
		while(x <= z) {
			ans = ans * 1LL * aa[x] % mod;
			x += y;
		}
		printf("%d\n",ans);
	}
}

void init(int n)
{
	for(int i = 1; i <= 150; i ++) {
		for(int j = n; j >= 1; j --) {
			if(i + j > n) dp[i][j] = aa[j];
			else dp[i][j] = aa[j] * 1LL * dp[i][i + j] % mod;
		}
	}
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n; i ++) {
			scanf("%d",&aa[i]);
			aa[i + n] = aa[i];
		}
		if(n <= 300) {
			solve(n,m);
			continue;
		}
		init(n);
		int a,b,c;
		while(m --) {
			scanf("%d%d%d",&a,&b,&c);
			int ans = 1;
			if(b > 150) {
				if(a > c) c += n;
				else if((c - a) % b) c += n;
				while(a <= c) {
					ans = 1LL * ans * aa[a] % mod;
					a += b;
				}
			}
			else {
				if(a <= c && (c - a) % b == 0) {
					ans = dp[b][a];
					if(c + b <= n) ans = 1LL * ans * pow(dp[b][c + b],mod - 2) % mod;
				}
				else {
					ans = dp[b][a];
					a = b - (n - a) % b;
					//if(!a) a = b;
					ans = 1LL * ans * dp[b][a] % mod;
					if(c + b <= n) ans = 1LL * ans * pow(dp[b][c + b],mod - 2) % mod;
				}

			}
			printf("%d\n",ans);
		}
	}
	return 0;
}