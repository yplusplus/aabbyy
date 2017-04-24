#include <iostream>
#include <cstdio>
using namespace std;

const long long MOD = 1000007LL;
const int N = 111;
int a[N], n;

int gauss(int row, int col) {
	int r, c, i, j;
	for (c = col - 1, r = 0; r < row && c >= 0; r++, c--) {
		for (i = r; i < row; i++) if (a[i] >> c & 1) break;
		if (i == row) { r--; continue; }
		if (i != r) swap(a[i], a[r]);
		for (i = 0; i < row; i++) {
			if (i != r && a[i] >> c & 1) a[i] ^= a[r];
		}
	}
	return row - r;
}

long long power_mod(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b & 1) res = (res * a) % MOD;
		b >>= 1;
		a = (a * a) % MOD;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i];
		int t = gauss(n, 31);
		cout << power_mod(2, t) << endl;
	}
	return 0;
}

