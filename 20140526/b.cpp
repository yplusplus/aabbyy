#include <bits/stdc++.h>
using namespace std;

const int N = 512;
int row[N], column[N], newID[N], last[N];
char mat[N][N];
typedef pair<int, int> Node;
#define x first
#define y second
Node nodes[N];

bool build(int n, int m, int k) {
	for (int i = 0; i < m; ++i) {
		last[i] = 0;
		//cout << newID[i] << ' ';
	}
	//cout << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			mat[i][j] = '*';
		}
		mat[i][m] = 0;
	}
	for (int i = 0, id = 0; i < n; ++i) {
		if (row[i] == 0) continue;
		if (i + k > n) return 0;
		for (int i = 0; i < m; ++i) {
			nodes[i].x = column[i];
			nodes[i].y = i;
		}
		sort(nodes, nodes + m);
		reverse(nodes, nodes + m);
		for (int i = 0; i < m; ++i) {
			newID[i] = nodes[i].y;
		}
		for (int j = 0; j < row[i]; ++j, ++id) {
			int t;
			for (int p = 0; p < m; ++p) {
				t = newID[p];
				if (column[t] == 0) continue;
				if (last[t] > i) continue;
				break;
			}
			if (column[t] == 0 || last[t] > i) {
				return 0;
			} else {
				last[t] = i + k;
			}
			--column[t];
			for (int p = 0; p < k; ++p) {
				if (mat[i + p][t] == '*') {
					if (p == 0 || p == k - 1) mat[i + p][t] = '+';
					else mat[i + p][t] = '|';
				} else {
					return 0;
				}
			}
		}
		for (int j = k - 1; j >= 0; --j) {
			if (row[i + j] < row[i]) {
				return 0;
			}
			row[i + j] -= row[i];
		}
	}
	for (int i = 0; i < m; ++i) {
		if (column[i]) return 0;
	}
	return 1;
}

int run() {
	int n, m, k;
	while (cin >> n >> m >> k) {
		for (int i = 0; i < n; ++i) {
			cin >> row[i];
			row[i] = m - row[i];
		}
		for (int i = 0; i < m; ++i) {
			cin >> column[i];
		}
		if (build(n, m, k)) {
			for (int i = 0; i < n; ++i) {
				cout << mat[i] << endl;
			}
		} else {
			cout << "inconsistent" << endl;
		}
	}
	return 0;
}

int main() {
	freopen("chip.in", "r", stdin);
	freopen("chip.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
