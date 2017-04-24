#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long dp[22][22][22][3];
int m;

long long cal(long long n)
{
	if(n < 10) return 0;
	int bit[25],len = 0;
	while(n) {
		bit[++ len] = n % 10;
		n /= 10;
	}
	reverse(bit + 1,bit + len + 1);
	memset(dp,0,sizeof(dp));
	for(int i = 1; i <= 9; i ++) {
		if(i < bit[1]) dp[1][i % m][m][0] ++;
		else if(i == bit[1]) dp[1][i % m][m][1] ++;
		else dp[1][i % m][m][2] ++;
	}
	for(int i = 1; i < len; i ++) {
		for(int j = 0; j < m; j ++) {
			for(int k = 0; k <= m; k ++) {
				if(!dp[i][j][k][0] && !dp[i][j][k][1] && !dp[i][j][k][2]) continue;
				if(k == m) {
					for(int r = 0; r < 10; r ++) {
						dp[i + 1][j][r % m][0] += dp[i][j][k][0];
						dp[i + 1][j][r % m][2] += dp[i][j][k][2];
						if(r == bit[i + 1]) {
							dp[i + 1][j][r % m][1] += dp[i][j][k][1];
						}
						else if(r > bit[i + 1]) {
							dp[i + 1][j][r % m][2] += dp[i][j][k][1];
						}
						else dp[i + 1][j][r % m][0] += dp[i][j][k][1];
					}
					for(int r = 0; r < 10; r ++) {
						dp[i + 1][(10 * j + r) % m][k][0] += dp[i][j][k][0];
						dp[i + 1][(10 * j + r) % m][k][2] += dp[i][j][k][2];
						if(r == bit[i + 1]) {
							dp[i + 1][(10 * j + r) % m][k][1] += dp[i][j][k][1];
						}
						else if(r > bit[i + 1]) {
							dp[i + 1][(10 * j + r) % m][k][2] += dp[i][j][k][1];
						}
						else dp[i + 1][(10 * j + r) % m][k][0] += dp[i][j][k][1];
					}
				}
				else {
					for(int r = 0; r < 10; r ++) {
						dp[i + 1][j][(10 * k + r) % m][0] += dp[i][j][k][0];
						dp[i + 1][j][(10 * k + r) % m][2] += dp[i][j][k][2];
						if(r == bit[i + 1]) {
							dp[i + 1][j][(10 * k + r) % m][1] += dp[i][j][k][1];
						}
						else if(r > bit[i + 1]) {
							dp[i + 1][j][(10 * k + r) % m][2] += dp[i][j][k][1];
						}
						else {
							dp[i + 1][j][(10 * k + r) % m][0] += dp[i][j][k][1];
						}
					}
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 2; i <= len; i ++) {
		for(int j = 0; j < m; j ++) {
			for(int k = 0; k < m; k ++) {
				for(int r = 0; r < 3; r ++) {
					if(i == len && r == 2) continue;
					if((j + k) % m == 0) ans += dp[i][j][k][r];
				}
			}
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	long long A,B;
	while(cin >> A >> B >> m) {
		cout << cal(B) - cal(A - 1) << endl;
	}
	return 0;
}