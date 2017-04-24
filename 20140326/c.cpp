#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 7;
char mat[N][N];

void fix(int &n, int &m, int size) {
	while (n * m < size) {
		if (n == m) m <<= 1;
		else if (n > m) m += n;
		else n += m;
	}
}

string decode(const string &q, int n, int m) {
	string ans;
	int len = q.length();
	fix(n, m, len);
	//cout << n << ' ' << m << endl;
	int r = len % m, d = len / m, p = 0;
	//cout << r << ' ' << d << ' ' << len << endl;
	for (int j = m - 1; j >= 0; --j) {
		int sz = d;
		if (j < r) ++sz;
		for (int i = 0; i < sz; ++i) mat[i][j] = q[p], ++p;
	}
	for (int i = 0, t = d - (r == 0); i < t; ++i) {
		if ((m & 1) && (i & 1)) swap(mat[i][m - 1], mat[i - 1][m - 1]);
		for (int j = 0; j < m; ++j) if (j & 1) swap(mat[i][j], mat[i][j - 1]);
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		mat[i][j] -= (i + j + 2) % 26;
		while (mat[i][j] < 'a') mat[i][j] += 26;
	}
	//for (int i = 0; i < n; ++i) {
		//for (int j = 0; j < m; ++j) cout << mat[i][j]; cout << endl;
	//}
	p = 0;
	for (int i = 0; i < n && p < len; ++i) {
		for (int j = 0; j < m && p < len; ++j) {
			ans += mat[i][j];
			++p;
		}
	}
	return ans;
}

int run() {
	int _, n, m;
	string q;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> q >> n >> m;
		cout << "Case #" << cas << ": " << decode(q, n, m) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
