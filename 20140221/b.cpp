#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
const int N = 22;
VI mat[N][N];

void flip_merge(VI &a, VI &b) {
	for (int i = b.size() - 1; i >= 0; i--) a.push_back(-b[i]);
	b.clear();
}

int main() {
	int n, m, x, cas = 0;
	while (cin >> n >> m && n + m) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> x;
				mat[i][j].clear();
				mat[i][j].push_back(x);
			}
		}
		int l, r, t, b;
		t = 0, l = 0, b = n - 1, r = m - 1;
		string str;
		if (n + m - 2) cin >> str;
		for (int i = 0, sz = n + m - 2; i < sz; i++) {
			if ('T' == str[i]) { for (int i = l; i <= r; i++) flip_merge(mat[t + 1][i], mat[t][i]); t++; }
			if ('B' == str[i]) { for (int i = l; i <= r; i++) flip_merge(mat[b - 1][i], mat[b][i]); b--; }
			if ('L' == str[i]) { for (int i = t; i <= b; i++) flip_merge(mat[i][l + 1], mat[i][l]); l++; }
			if ('R' == str[i]) { for (int i = t; i <= b; i++) flip_merge(mat[i][r - 1], mat[i][r]); r--; }
		}
		cout << "Case " << ++cas << ":";
		for (int i = 0, sz = n * m; i < sz; i++) {
			//cerr << "Debug " << i << ' ' << mat[t][l][i] << endl;
			if (mat[t][l][i] > 0) cout << ' ' << mat[t][l][i];
		}
		cout << endl;
	}
	return 0;
}
