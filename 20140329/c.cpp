#include <bits/stdc++.h>
using namespace std;

const int MOD = 1991;
const int N = 111;
int n, m, q;

struct Mat {
	int v[N][N];
	void zero() { memset(v, 0, sizeof(v)); }
	void unit() { zero(); for (int i = 0; i < N; i++) { v[i][i] = 1; } }
};

Mat operator*(const Mat &a, const Mat &b) {
	Mat res;
	res.zero();
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (a.v[i][k] == 0) continue;
			for (int j = 0; j < n; j++) {
				if (b.v[k][j] == 0) continue;
				res.v[i][j] = (res.v[i][j] + a.v[i][k] * b.v[k][j]) % MOD;
			}
		}
	}
	return res;
}

Mat operator^(Mat a, int n) {
	Mat res;
	res.unit();
	while (n) {
		if (n & 1) res = res * a;
		a = a * a;
		n >>= 1;
	}
	return res;
}

/*
void output(const Mat &a) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", a.v[i][j]);
		}
		cout << endl;
	}
}
*/

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		Mat a;
		a.zero();
		int k;
		scanf("%d%d%d%d", &n, &m, &k, &q);
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			u--, v--;
			a.v[u][v]++;
		}
		a = a ^ k;
		//output(a);
		while (q--) {
			int u, v;
			scanf("%d%d", &u, &v);
			u--, v--;
			printf("%d\n", a.v[u][v]);
		}
	}
	return 0;
}
