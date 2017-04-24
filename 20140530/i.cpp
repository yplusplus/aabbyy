#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int N = 110;
const int mod = 1000000007;
long long dp[N][N][N],c[N][N],P[N][N];

void init()
{
	memset(c,0,sizeof(c));
	memset(P,0,sizeof(P));
	for(int i = 0; i < N; i ++) {
		P[i][0] = 1;
		for(int j = 1; j <= 4 && j <= i; j ++) {
			P[i][j] = P[i][j - 1] * (i - j + 1) % mod;
		}
	}
	for(int i = 0; i < N; i ++) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j ++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}

void add(long long &x,long long y)
{
	x += y;
	if(x >= mod) x %= mod;
}

void solve()
{
	memset(dp,0,sizeof(dp));
	dp[0][0][0] = 1;
	int n;
	scanf("%d",&n);
	int v = 0,x;
	//dp[i][j][k] j meishoudaoliwu
	//k meisongchuliwu
	for(int i = 0; i < n; i ++) {
		scanf("%d",&x);
		for(int j = 0; j <= v; j ++) {
			for(int k = 0; k <= v; k ++) {
				if(!dp[i][j][k]) continue;
				for(int r = 0; r <= x; r ++) {
					for(int p = 0; p <= x; p ++) {
						if(j + x - r - p >= 0 && k + x - r - p >= 0) add(dp[i + 1][j + x - p - r][k + x - r - p],dp[i][j][k] * c[x][r] * c[x][p] % mod * P[k][r] % mod * P[j][p]);
					}
				}
			}
		}
		v += x;
	}
	printf("%d\n",(int)dp[n][0][0]);
}

int main()
{
	init();
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case #%d: ",cas);
		solve();
	}
	return 0;
}
