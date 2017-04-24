#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
char ma[N][N];
int gor[N][N];
int gol[N][N];
double dp[2][N][3];
int n;

bool is_zero(double x) {
	if (fabs(x) < 1e-6) return true;
	return false;
}

void solve() {
	n--;
	if (n <= 0) return;
	//cout << n << endl;
	int m = strlen(ma[1] + 1);
	for (int i = 1; i <= n; i++) ma[i][m + 1] = '.';
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 1; j--) {
			if (ma[i][j] == '.' || ma[i][j] == '/') continue;
			if (ma[i][j + 1] == '.') gor[i][j] = j + 1;
			if (ma[i][j + 1] == '|' || ma[i][j + 1] == '/') gor[i][j] = j;
			if (ma[i][j + 1] == '_') gor[i][j] = gor[i][j + 1];
		}
		for (int j = 1; j <= m; j++) {
			if (ma[i][j] == '.' || ma[i][j] == '\\') continue;
			if (ma[i][j - 1] == '.') gol[i][j] = j - 1;
			if (ma[i][j - 1] == '|' || ma[i][j - 1] == '\\') gol[i][j] = j;
			if (ma[i][j - 1] == '_') gol[i][j] = gol[i][j - 1];
		}
	}
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= m; i++) dp[0][i][0] = 100.0 / m;
	for (int i = 1; i <= n; i++) {
		int p = i & 1;
		int q = p ^ 1;
		memset(dp[p], 0, sizeof(dp[p]));
		for (int j = 0; j <= m + 1; j++) {
			if (ma[i - 1][j] != '.') continue;
			double x;
			int pos;
			if (ma[i][j] == '|') {
				x = 0;
				for (int k = 0; k < 3; k++) x += dp[q][j][k];
				pos = gor[i][j];
				dp[p][pos][2] += x / 2;
				pos = gol[i][j];
				dp[p][pos][1] += x / 2;
			} else if (ma[i][j] == '/') {
				x = 0;
				for (int k = 0; k < 3; k++) x += dp[q][j][k];
				pos = gol[i][j];
				dp[p][pos][1] += x;
			} else if (ma[i][j] == '\\') {
				x = 0;
				for (int k = 0; k < 3; k++) x += dp[q][j][k];
				pos = gor[i][j];
				dp[p][pos][2] += x;
			} else if (ma[i][j] == '.') {
				for (int k = 0; k < 3; k++) dp[p][j][k] += dp[q][j][k];
			} else if (ma[i][j] == '_') {
				pos = gor[i][j];
				dp[p][pos][2] += dp[q][j][2];
				pos = gol[i][j];
				dp[p][pos][1] += dp[q][j][1];
			}
		}
	}
	double ans = 0;
	for (int i = 0; i <= m + 1; i++) {
		if (ma[n][i] == '.') {
			for (int j = 0; j < 3; j++) ans += dp[n & 1][i][j];
		}
	}
	printf("%.2f\n", ans);
}

void init() {
	n = 0;
	memset(ma, '.', sizeof(ma));
}

int main() {
	//freopen("in.txt", "r", stdin);
	char line[N];
	init();
	while (gets(line) > 0) {
		n++;
		strcpy(ma[n] + 1, line);
		while (n > 1005) {
			cout << "mgq" << endl;
		}
		if (strlen(ma[n] + 1) == 0) {
			solve();
			init();
		}
	}
	solve();
	return 0;
}
