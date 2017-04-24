#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 111;
inline int lowbit(int x) { return x & -x; }
struct BIT {
	LL a[N][N];
	void init() { for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) a[i][j] = 0; }
	void add(int x, int y, int d) {
		x += 2; y += 2;
		for (int i = x; i > 0; i -= lowbit(i)) {
			for (int j = y; j > 0; j -= lowbit(j)) {
				a[i][j] += d;
			}
		}
	}
	void add(int a, int b, int c, int d, int e) {
		add(c, d, e); add(a - 1, b - 1, e);
		add(a - 1, d, -e); add(c, b - 1, -e);
	}
	LL get(int x, int y) {
		LL s = 0; x += 2; y += 2;
		for (int i = x; i < N; i += lowbit(i)) {
			for (int j = y; j < N; j += lowbit(j)) {
				s += a[i][j];
			}
		}
		return s;
	}
} bit;

int main() {
	ios::sync_with_stdio(0);
	int cas = 1, n, m, x;
	while (cin >> n >> m) {
		cout << "Case " << cas++ << endl;
		bit.init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> x;
				bit.add(i, j, i, j, x);
			}
		}
		int k, a, b, c, d, e, f;
		cin >> k;
		while (k--) {
			cin >> a;
			if (a == 0) {
				cin >> b >> c >> d >> e >> f;
				if (c > 1) bit.add(b, 1, b, c - 1, -f);
				if (e < m) bit.add(d, e + 1, d, m, -f);
				bit.add(b, 1, d, m, f);
			} else if (a == 1) {
				cin >> b >> c >> d >> e >> f;
				if (b > 1) bit.add(1, c, b - 1, c, -f);
				if (d < n) bit.add(d + 1, e, n, e, -f);
				bit.add(1, c, n, e, f);
			} else if (a == 2) {
				cin >> b >> c;
				cout << bit.get(b, c) << endl;
			}
			//for (int i = 1; i <= n; i++) {
			//	for (int j = 1; j <= m; j++) cout << bit.get(i, j) << ' ';
			//	cout << endl;
			//}
		}
	}
	return 0;
}
