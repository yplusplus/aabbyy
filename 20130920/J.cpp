#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
const int N = 11111;
ll a[N];

int gauss(int row, int col) {
	int i, r, c;
	for (r = 0, c = col - 1; r < row && c >= 0; r++, c--) {
		for (i = r; i < row; i++)
			if (a[i] >> c & 1) break;
		if (i == row) { r--; continue; }
		if (i != r) swap(a[i], a[r]);
		for (i  = 0; i < row; i++) {
			if (i != r && a[i] >> c & 1) a[i] ^= a[r];
		}
	}
	//cout << r << " " << c << endl;
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	int T, Case = 1;
	int n, m;
	cin >> T;
	ll k;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i];
		int r = gauss(n, 64);
		sort(a, a + n);
		n = unique(a, a + n) - a;
		//cout << "r = " << r << endl;
		//for (int i = 0; i < r; i++) {
			//cout << a[i] << endl;
		//}
		cin >> m;
		cout << "Case #" << Case++ << ":" << endl;
		while (m--) {
			cin >> k;
			int pos = 0;
			if (a[0] == 0) k--, pos++;
			ll ans = 0;
			for ( ;pos < n && k; pos++, k >>= 1) {
				if (k & 1) ans ^= a[pos];
			}
			if (k) cout << -1 << endl;
			else cout << ans << endl;
		}
	}
	return 0;
}