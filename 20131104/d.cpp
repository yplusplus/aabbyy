#include <iostream>
#include <cstring>
using namespace std;

const int M = 30;
const int MOD = 1000000007;
int n, m;

int add(int a, int b) {
	return (a + b) % MOD;
}

int mul(int a, int b) {
	return (1LL * a * b) % MOD;
}

struct Mat {
	int v[M][M];
	Mat() { memset(v, 0, sizeof(v)); }
	void toUnit() { for (int i = 0; i < M; i++) v[i][i] = 1; }
	Mat operator *(const Mat &x) {
		Mat res;
		for (int k = 0; k < m; k++) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < m; j++) {
					res.v[i][j] = add(res.v[i][j], mul(v[i][k], x.v[k][j]));
				}
			}
		}
		return res;
	}
	Mat operator ^(int n) {
		Mat res;
		Mat a = *this;
		res.toUnit();
		while (n) {
			if (n & 1) res = res * a;
			n >>= 1;
			a = a * a;
		}
		return res;
	}
};

int power_mod(int a, int n) {
	int res = 1;
	while (n) {
		if (n & 1) res = mul(res, a);
		a = mul(a, a);
		n >>= 1;
	}
	return res;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		if (m == 1) {
			cout << power_mod(2, n - 1) << endl;
			continue;
		}
		Mat a, b;
		a.v[0][0] = 1;
		for (int i = 0; i < m - 1; i++) {
			b.v[i + 1][i] = 1;
		}
		b.v[m - m][m - 1] = 1;
		b.v[m - 1][m - 1] = 1;
		Mat c = a * (b ^ n);
		cout << c.v[0][0] << endl;
	}
	return 0;
}

