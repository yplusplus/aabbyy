#include <bits/stdc++.h>
using namespace std;

int run() {
	int h, r, s, m;
	while (cin >> h >> r >> s >> m) {
		double L = hypot(h, r) * s / h;
		for (int i = 0; i < m; ++i) {
			cout << (L * pow(1.0 * (m - i) / m, 1.0 / 3)) << endl;
		}
	}
	return 0;
}

int main() {
	freopen("sand.in", "r", stdin);
	freopen("sand.out", "w", stdout);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(20);
	return run();
}
