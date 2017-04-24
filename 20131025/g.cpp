#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
char s[N], t[N];
int dp[N][2][2];
pair<int, int>  pre[N][2][2];
char sdigit[N], tdigit[N];
bool check(int a, int b, int c) {
	return a ^ b ^ c == 0;
}

int main() {
	while (~scanf("%s%s", s, t)) {
		int n = strlen(s);
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		int ans = 0, aend = -1, bend = -1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					if (dp[i][j][k] == 0) continue;
					for (int a = 0; a < 2; a++) {
						if (s[i] != '?' && s[i] - '0' != a) continue;
						for (int b = 0; b < 2; b++) {
							if (t[i] != '?' && t[i] - '0' != b) continue;
							if (check(j, a, b)) {
								dp[i + 1][a][b] += dp[i][j][k];
								pre[i + 1][a][b] = make_pair(j, k);
								if (dp[i + 1][a][b] > 2) dp[i + 1][a][b] = 2;
								if (i + 1 == n) {
									aend = a, bend = b;
									ans += dp[i][j][k];
								}
							}
						}
					}
				}
			}
		}
		if (ans == 0) puts("Impossible");
		else if (ans >= 2) puts("Ambiguity");
		else {
			for (int i = n - 1; i >= 0; i--) {
				sdigit[i] = aend + '0';
				tdigit[i] = bend + '0';
				int aa = pre[i + 1][aend][bend].first;
				int bb = pre[i + 1][aend][bend].second;
				aend = aa, bend = bb;
			}
			sdigit[n] = tdigit[n] = 0;
			puts(sdigit);
			puts(tdigit);
		}
	}
	return 0;
}

