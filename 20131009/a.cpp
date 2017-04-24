#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int n, m;
const int N = 555;
int num[N][N];
int val[N][N];
int sum[N][N];
int dp[N][N];
int pre[N][N];

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n >> m) {
		memset(num, 0, sizeof(num));
		memset(sum, 0, sizeof(sum));
		memset(val, 0, sizeof(val));
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				cin >> num[i][j];
			}
			sum[i][n + 1] = 0;
			for (int j = n; j > i; j--) {
				sum[i][j] = sum[i][j + 1] + num[i][j];
				//cout << i << " " << j << " " << sum[i][j] << endl;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = i; k < j; k++) {
					val[i][j] += sum[k][j];
				}
				//cout << i << " " << j << " " << val[i][j] << endl;
			}
		}
		memset(dp, 0, sizeof(dp));
		//dp[0][1] = 0;
		for (int i = 1; i <= m; i++) {
			for (int j = i + 1; j <= n; j++) {
				int pos = i;
				for (int k = i; k < j; k++) {
					if (dp[i - 1][pos] + val[pos][j] < dp[i - 1][k] + val[k][j]) {
						pos = k;
					}
				}
				pre[i][j] = pos;
				dp[i][j] = dp[i - 1][pos] + val[pos][j];
			}
		}
		int pos = m + 1;
		for (int i = m + 1; i <= n; i++) {
			if (dp[m][pos] < dp[m][i]) pos = i;
		}
		cout << dp[m][pos] << endl;
		vector<int> vec;
		for (int i = m; i; i--) {
			vec.push_back(pos - 1);
			pos = pre[i][pos];
		}
		reverse(vec.begin(), vec.end());
		for (int i = 0; i < m; i++) {
			cout << vec[i];
			if (i == m - 1) cout << endl;
			else cout << " ";
		}
	}
	return 0;
}

