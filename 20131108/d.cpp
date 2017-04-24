#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
const int mod = 1000000007;
int dp[N * 2][N * 2];
int f[N],ff[N];
int a[N];

void cal(int n,int m,int &K)
{
	if(!m) {
		f[0] = 1;
		K = 0;
		return;
	}
	for(int i = 0; i <= K; i ++) {
		ff[i] = f[i];
		f[i] = 0;
	}
	for(int i = 0; i <= K; i ++) {
		if(ff[i]) {
			for(int j = 0; j <= n && j <= m - i; j ++) {
		
					int x = n - j;
					f[i + j] = (f[i + j] + 1LL * ff[i] * dp[x + i + j][i + j] % mod * dp[m - i][j] % mod) % mod;
			
			}
		}
	}
	int tmp = K;
	for(int i = 0; i <= K + n; i ++) {
		if(f[i]) tmp = i;
	}
	K = tmp;
}

int main()
{
	memset(dp,0,sizeof(dp));
	for(int i = 0; i < N * 2; i ++) {
		dp[i][0] = dp[i][i] = 1;
		for(int j = 1; j < i; j ++) {
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
		}
	}

	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		for(int i = 1; i <= n; i ++)
			scanf("%d",&a[i]);
		sort(a + 1,a + n + 1);
		int i = n;
		memset(f,0,sizeof(f));
		memset(ff,0,sizeof(ff));
		int tot = 0;
		int K = 0;
		while(i >= 1) {
			int j = i;
			while(j && a[j] == a[i]) j --;
			cal(i - j,tot,K);
			tot += i - j;
			i = j;
		}
		int ans = 0;
		for(int i = 0; i <= m; i ++)
			ans = (ans + f[i]) % mod;
		printf("%d\n",ans);
	}
	return 0;
}
