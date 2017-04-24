#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 22;
int mat[N][N], n, m;
int tmp[N][N];

void fix() {
	for (int i = 0; i < m; i++) {
		int p = 0;
		for (int j = 0; j < n; j++) {
			if (mat[j][i] == -1) continue;
			swap(mat[p][i], mat[j][i]);
			p++;
		}
	}
}

void fix_tmp() {
	for (int i = 0; i < m; i++) {
		int p = 0;
		for (int j = 0; j < n; j++) {
			if (tmp[j][i] == -1) continue;
			swap(tmp[p][i], tmp[j][i]);
			p++;
		}
	}
}

void print() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) cout << mat[i][j] << ' ';
		cout << endl;
	}
	cout << "~~~~~~~~~~~~~~" << endl;
}

void print_tmp() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) cout << tmp[i][j] << ' ';
		cout << endl;
	}
	cout << "~~~~~~~~~~~~~~" << endl;
}

void copy() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) tmp[i][j] = mat[i][j];
	}
}

void update() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) mat[i][j] = tmp[i][j];
	}
}

int cal(int x, int y) {
	int col = 0, row = 0;
	int l, r;
	l = r = x;
	while (0 <= l && tmp[l][y] != -1) l--; l++;
	while (r < n && tmp[r][y] != -1) r++; r--;
	if (r - l + 1 == tmp[x][y]) return tmp[x][y];
	l = r = y;
	while (0 <= l && tmp[x][l] != -1) l--; l++;
	while (r < m && tmp[x][r] != -1) r++; r--;
	if (r - l + 1 == tmp[x][y]) return tmp[x][y];
	return 0;
}

int sx[N * N], sy[N * N];
int cal() {
	int sum = 0, top = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp[i][j] == -1) continue;
			int t = cal(i, j);
			sum += t;
			//cout << i << ' ' << j << ' ' << t << endl;
			if (t) top++, sx[top] = i, sy[top] = j;
		}
	}
	while (~top) {
		//cout << sx[top] << ' ' << sy[top] << endl;
		tmp[sx[top]][sy[top]] = -1;
		top--;
	}
	fix_tmp();
	//print_tmp();
	//cout << sum << endl;
	return sum;
}

int get_score() {
	int sum = 0, t;
	while (t = cal()) sum += t;
	return sum;
}

int insert(int x) {
	int mx = 0, col = m, low = n;
	for (int i = 0; i < m; i++) {
		int ok = -1;
		for (int j = 0; j < n; j++) if (mat[j][i] == -1) { ok = j; break; }
		if (~ok) {
			copy();
			tmp[ok][i] = x;
			//print_tmp();
			int s = get_score();
			if (s > mx) {
				mx = s;
				col = i;
				low = ok;
			} else if (s == mx && low > ok) {
				col = i;
				low = ok;
			}
		}
	}
	copy();
	tmp[low][col] = x;
	get_score();
	update();
	return mx;
}

bool full() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) if (mat[i][j] == -1) return 0;
	}
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int k, x;
	while (cin >> n >> m >> k) {
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j < m; j++) cin >> mat[i][j];
		}
		fix();
		int sum = 0, t = 0;
		while (k--) {
			cin >> x;
			if (full()) continue;
			t = insert(x);
			sum += t;
			fix();
			//print();
			//cout << k << endl;
		}
		cout << sum << endl;
	}
	return 0;
}
