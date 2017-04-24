#include <bits/stdc++.h>
using namespace std;

const int K = 6;
const int N = 22;

int n, puzzle[K][4][N][N], answer[N][N][N];

bool Fill0(const int ht[N][N], const int id) {
	if (id) {
		for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { if (answer[i][j][d]) { return 0; } } } }
	}
	for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { answer[i][j][d] = id; } } }
	return 1;
}

bool Fill1(const int ht[N][N], const int id) {
	if (id) {
		for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { if (answer[d][j][n - i - 1]) { return 0; } } } }
	}
	for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { answer[d][j][n - i - 1] = id; } } }
	return 1;
}

bool Fill2(const int ht[N][N], const int id) {
	if (id) {
		for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { if (answer[n - j - 1][d][n - i - 1]) { return 0; } } } }
	}
	for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { answer[n - j - 1][d][n - i - 1] = id; } } }
	return 1;
}

bool Fill3(const int ht[N][N], const int id) {
	if (id) {
		for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { if (answer[n - d - 1][n - j - 1][n - i - 1]) { return 0; } } } }
	}
	for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { answer[n - d - 1][n - j - 1][n - i - 1] = id; } } }
	return 1;
}

bool Fill4(const int ht[N][N], const int id) {
	if (id) {
		for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { if (answer[j][n - d - 1][n - i - 1]) { return 0; } } } }
	}
	for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { answer[j][n - d - 1][n - i - 1] = id; } } }
	return 1;
}

bool Fill5(const int ht[N][N], const int id) {
	if (id) {
		for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { if (answer[n - i - 1][j][n - d - 1]) { return 0; } } } }
	}
	for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int d = 0; d < ht[i][j]; ++d) { answer[n - i - 1][j][n - d - 1] = id; } } }
	return 1;
}

bool (*Func [6])(const int ht[N][N], const int id);

void Prepare() {
	Func[0] = Fill0;
	Func[1] = Fill1;
	Func[2] = Fill2;
	Func[3] = Fill3;
	Func[4] = Fill4;
	Func[5] = Fill5;
}

bool vis[6];

bool Gao(const int p) {
	if (p >= K) {
		return 1;
	}

	for (int i = 0; i < K; ++i) {
		if (vis[i]) {
			continue;
		}
		vis[i] = 1;
		for (int j = 0; j < 4; ++j) {
			if (Func[p](puzzle[i][j], i + 1)) {
				if (Gao(p + 1)) {
					return 1;
				}
				Func[p](puzzle[i][j], 0);
			}
		}
		vis[i] = 0;
	}

	return 0;
}

int Run() {
	Prepare();
	while (cin >> n) {
		for (int i = 0; i < K; ++i) {
			for (int t = 0; t < 4; ++t) {
				if (t) {
					for (int j = 0; j < n; ++j) {
						for (int k = 0; k < n; ++k) {
							puzzle[i][t][j][k] = puzzle[i][t - 1][n - k - 1][j];
						}
					}
				} else {
					for (int j = 0; j < n; ++j) {
						for (int k = 0; k < n; ++k) {
							cin >> puzzle[i][0][j][k];
						}
					}
				}
			}
		}
		memset(answer, 0, sizeof answer);
		memset(vis, 0, sizeof vis);
		vis[0] = 1;
		if (Func[0](puzzle[0][0], 1) && Gao(1)) {
			cout << "Yes" << endl;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					for (int k = 0; k < n; ++k) {
						if (k) {
							cout.put(' ');
						}
						cout << answer[i][j][k];
					}
					cout << endl;
				}
			}
		} else {
			cout << "No" << endl;
		}
	}

	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return Run();
}
