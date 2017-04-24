#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 1000000;
const int N = 1111;
int dp[N][N];
char str[N];

int add(int a, int b) { return (a + b) % MOD; }

int main() {
	while (~scanf("%s", str)) {
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		int n = strlen(str);
		for (int i = 0; i < n; i++) {
			char ch = str[i];
			for (int five = 0; five <= i; five++) {
				int ten = i - five;
				if (dp[i][five] == 0 || five < ten) continue;
				if (ch == '.') {
					dp[i + 1][five] = add(dp[i + 1][five], dp[i][five]);
					dp[i + 1][five + 1] = add(dp[i + 1][five + 1], dp[i][five]);
				} else if (ch == '(') {
					dp[i + 1][five + 1] = add(dp[i + 1][five + 1], dp[i][five]);
				} else if (ch == ')') {
					dp[i + 1][five] = add(dp[i + 1][five], dp[i][five]);
				}
			}
		}
		int ans = dp[n][n / 2];
		printf("%d\n", ans);
	}
	return 0;
}
