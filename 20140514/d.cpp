#include <bits/stdc++.h>
using namespace std;

long long dp[35][35][35][35];

void add(long long &x,long long y)
{
	x += y;
}

long long cal(int n)
{
	dp[0][0][0][0] = 1;
	for(int i = 0; i <= n; i ++) {
		for(int j = 0; j <= n; j ++) {
			for(int k = 0; k <= n; k ++) {
				for(int r = 0; r <= n; r ++) {
					if(!dp[i][j][k][r]) continue;
					for(int kk = k; i + kk <= n; kk ++) {
						if(k == kk) {
							for(int rr = r; j + rr <= n; rr ++) {
								if(kk == 0 && rr == 0) continue;
								add(dp[i + kk][j + rr][kk][rr],dp[i][j][k][r]);
							}
						}
						else {
							for(int rr = 0; j + rr <= n; rr ++) {
								if(kk == n && rr == n) continue;
								add(dp[i + kk][j + rr][kk][rr],dp[i][j][k][r]);
							}
						}
					}
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= n; j ++) {
			ans += dp[n][n][i][j];
			//if(dp[n][n][i][j]) cout << n << " " << i << " " << j << endl;
		}
	return ans;
}

int main()
{
	freopen("false.in","r",stdin);
	freopen("false.out","w",stdout);
	long long n;
	cin >> n;
	long long ans = -1;
	for(long long i = 2; i <= 1000000; i ++) {
		if(n % i) continue;
		int cnt = 0;
		while(n % i == 0) n /= i,cnt ++;
		ans = cnt;
		break;
	}
	if(ans == -1) cout << 1 << endl;
	else cout << cal(ans) << endl;
	return 0;
}
