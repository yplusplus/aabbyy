#include <bits/stdc++.h>
using namespace std;

const int N = 44;
int n;
const int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; }
inline int encode(int x, int y) { return x * n + y; }
int mat[N][N];
typedef long long LL;

LL det() {
	int m = n * n;
	LL ret = 1;
	for (int p = 1; p < m; p++) {
		for (int i = p + 1; i < m; i++) {
			while (mat[i][p]) {
				int k = mat[p][p] / mat[i][p];
				for (int j = p; j < m; j++) {
					mat[p][j] -= mat[i][j] * k;
					swap(mat[p][j], mat[i][j]);
				}
				ret = -ret;
			}
		}
		ret *= mat[p][p];
	}
	return ret;
}

int main() {
	int _;
	cin >> _;
	while (_-- && cin >> n) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int i1 = encode(i, j);
				for (int k = 0; k < 8; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (!inmat(x, y)) continue;
					int i2 = encode(x, y);
					mat[i1][i2] = mat[i2][i1] = -1;
					mat[i1][i1]++;
				}
			}
		}
		cout << det() << endl;
		for (int i = 0; i < n * n; i++) {
			for (int j = 0; j < n * n; j++) {
				cout << mat[i][j] << ' ';
			}
			cout << endl;
		}
	}
	return 0;
}
