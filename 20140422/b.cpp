#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 7;
const int MOD = 1e4 + 7;
struct Matrix {
	int value[N][N], size;
	Matrix() { memset(value, 0, sizeof value); }
	Matrix(int size, int x = 0) : size(size) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				value[i][j] = 0;
			}
			value[i][i] = x;
		}
	}
	void print() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cout << value[i][j] << ' ';
			}
			cout << endl;
		}
	}
} ;

Matrix operator * (const Matrix &a, const Matrix &b) {
	int size = a.size;
	Matrix s(size);
	for (int i = 0; i < size; ++i) {
		for (int k = 0; k < size; ++k) {
			if (a.value[i][k]) {
				for (int j = 0; j < size; ++j) {
					s.value[i][j] += a.value[i][k] * b.value[k][j];
					s.value[i][j] %= MOD;
				}
			}
		}
	}
	return s;
}

Matrix operator ^ (Matrix a, int p) {
	int size = a.size;
	Matrix s(size, 1);
	while (p > 0) {
		if (p & 1) s = s * a;
		a = a * a, p >>= 1;
	}
	return s;
}

int run() {
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		int n, m;
		cin >> n >> m;
		Matrix op(m), base(m);
		for (int i = 1; i < m; ++i) op.value[i][0] = 1;
		for (int i = 1; i < m; ++i) op.value[i - 1][i] = 1;
		base.value[0][0] = 2;
		base = base * (op ^ n - 1);
		//base.print();
		int ans = 0;
		for (int i = 0; i < m; ++i) {
			ans += base.value[0][i];
			if (ans >= MOD) ans -= MOD;
		}
		cout << "Case " << cas << ": " << ans << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
