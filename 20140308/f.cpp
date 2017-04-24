#include <bits/stdc++.h>
using namespace std;

int run() {
	int n, a, b, c, _;
	bool pnt = 0;
	cin >> _;
	while (_--) {
		if (pnt) cout << endl;
		pnt = 1;
		cin >> n;
		if (n == 2) {
			cin >> a >> b >> c;
			cout << (b * b - 4 * a * c >= 0 ? "NO" : "YES") << endl;
		} else {
			for (int i = 0; i <= n; ++i) cin >> a;
			cout << (n <= 1 ? "YES" : "NO") << endl;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
