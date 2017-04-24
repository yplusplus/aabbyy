#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 8;
int win[N][3][N];

bool dfs(int n, int m, int r) {
	if (n <= 1) return 0;
	if (~win[n][m][r]) return win[n][m][r];
	win[n][m][r] = 0;
	win[n][m][r] |= !dfs(n + (m + 1) / 3 - 1, (m + 1) % 3, r);
	win[n][m][r] |= !dfs(n + (m + 1) / 3 - 1, (m + 1) % 3, r + 1);
	if (r > 0) win[n][m][r] |= !dfs(n + (m + 1) / 3, (m + 1) % 3, r - 1);
	return win[n][m][r];
}

int run() {
	int n, _;
	//memset(win, -1, sizeof win);
	//for (int i = 0; i < N; ++i) cout << i << ' ' << dfs(i, 0, 0) << endl;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> n;
		cout << "Case " << cas << ": " << (n % 3 ? "Bakkar" : "Wahdan") << endl;
	}
	return 0;
}

int main() {
	freopen("jenga.in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
