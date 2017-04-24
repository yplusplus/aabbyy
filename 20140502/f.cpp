#include <bits/stdc++.h>
using namespace std;

const int N = 65;
const long long inf = 1LL << 62;
int n;
string str;
int cnt[30];
long long dp[30][N][2];
long long c[N][N];
int main() {
	for (int i = 0; i < N; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++) {
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	}
	while (cin >> n) {
		cin >> str;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < str.length(); i++) {
			cnt[str[i] - 'A']++;
		}
		memset(dp, 0, sizeof(dp));
		vector<int> letter;
		for (int i = 0; i < 26; i++) {
			if (cnt[i]) {
				letter.push_back(cnt[i]);
			}
		}
		for (int i = 0; i <= letter.size(); i++) {
			for (int j = 0; j <= n; j++) {
				dp[i][j][0] = inf;
				dp[i][j][1] = -inf;
			}
		}
		dp[0][0][0] = dp[0][0][1] = 1;
		for (int i = 0; i < letter.size(); i++) {
			for (int j = 0; j <= n; j++) {
				if (dp[i][j][0] == inf) continue;
				for (int k = letter[i]; k <= n - j; k++) {
					dp[i + 1][j + k][0] = min(dp[i + 1][j + k][0], dp[i][j][0] * c[k][letter[i]]);
					dp[i + 1][j + k][1] = max(dp[i + 1][j + k][1], dp[i][j][1] * c[k][letter[i]]);
				}
			}
		}
		long long t = c[n][str.length()];
		//cout << t << endl;
		long long d;
	   	d = __gcd(dp[letter.size()][n][1], t);
		cout << dp[letter.size()][n][1] / d << "/" << t / d << endl;
		d = __gcd(dp[letter.size()][n][0], t);
		cout << dp[letter.size()][n][0] / d << "/" << t / d << endl;
		cout << endl;
	}
	return 0;
}
