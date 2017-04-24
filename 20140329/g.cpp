#include <iostream>
#include <cstring>
using namespace std;

const int N = 33;
long long dp[N][N];

void init() {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 0 && j == 0) continue;
			if (j - 1 >= 0) dp[i][j] += dp[i][j - 1];
			if (i - 1 >= 0 && j + 1 < N) dp[i][j] += dp[i - 1][j + 1];
		}
	}
}

int main() {
	init();
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		cout << dp[n][0] << endl;
	}
	return 0;
}
