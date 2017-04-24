#include <bits/stdc++.h>
using namespace std;

typedef vector<int> Array;
typedef vector<Array> Matrix;
Array X, Y;
Array x[4];
//Matrix Map;
const int N = 5000;
char Map[N][N];
int n, m, w;

inline int getID(const Array &arr, int x) { return lower_bound(arr.begin(), arr.end(), x) - arr.begin(); }
inline bool inMap(int a, int b) { return 0 <= a && a < n && 0 <= b && b < m; }

int run() {
	int cas = 0;
	while (cin >> n >> m >> w && (n + m + w)) {
		swap(n, m);
		X.clear();
		Y.clear();
		for (int i = 0; i < 4; ++i) {
			x[i].resize(w);
		}
		for (int i = 0; i < w; ++i) {
			for (int j = 0; j < 4; ++j) {
				cin >> x[j][i];
			}
			if (inMap(x[0][i] - 1, 0)) X.push_back(x[0][i] - 1);
			X.push_back(x[0][i]);
			X.push_back(x[2][i]);
			if (inMap(x[2][i] + 1, 0)) X.push_back(x[2][i] + 1);
			assert(x[1][i] == x[3][i]);
			for (int d = -1; d <= 1; ++d) {
				if (inMap(0, x[1][i] + d)) Y.push_back(x[1][i] + d);
			}
		}
		X.push_back(0);
		Y.push_back(0);
		X.push_back(n - 1);
		Y.push_back(m - 1);
		sort(X.begin(), X.end());
		X.resize(unique(X.begin(), X.end()) - X.begin());
		sort(Y.begin(), Y.end());
		Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
		//Map.clear();
		//Map.resize(X.size(), Array(Y.size(), 0));
		for (int i = 0; i < X.size(); ++i) {
			for (int j = 0; j < Y.size(); ++j) {
				Map[i][j] = 0;
			}
		}
		for (int i = 0; i < w; ++i) {
			int l = getID(X, x[0][i]);
			int r = getID(X, x[2][i]);
			int h = getID(Y, x[1][i]);
			for (int j = l; j <= r; ++j) {
				Map[j][h] = 1;
			}
		}
		//for (int i = 0; i < X.size(); ++i) { cout << X[i] << ' '; } cout << endl;
		//for (int i = 0; i < Y.size(); ++i) { cout << Y[i] << ' '; } cout << endl;
		if (Map[X.size() - 1][Y.size() - 1] == 0) Map[X.size() - 1][Y.size() - 1] = 2;
		for (int i = X.size() - 1; i >= 0; --i) {
			for (int j = Y.size() - 1; j >= 0; --j) {
				if (Map[i][j] == 2) {
					if (inMap(i - 1, j) && Map[i - 1][j] == 0) {
						Map[i - 1][j] = 2;
					}
					if (inMap(i, j - 1) && Map[i][j - 1] == 0) {
						Map[i][j - 1] = 2;
					}
				}
			}
		}
		//for (int i = Y.size() - 1; i >= 0; --i) { for (int j = 0; j < X.size(); ++j) { cout << int(Map[j][i]); } cout << endl; }
		long long answer = 0;
		X.push_back(n);
		Y.push_back(m);
		n = X.size() - 1;
		m = Y.size() - 1;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (Map[i][j] == 0) {
					answer += (long long) (X[i + 1] - X[i]) * (Y[j + 1] - Y[j]);
					//cout << (X[i + 1] - X[i]) << ' ' << (Y[j + 1] - Y[j]) << endl;
				}
			}
		}
		cout << "Case " << ++cas << ": " << answer << endl;
	}
	return 0;
}

int main() {
	//freopen("in_c", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
