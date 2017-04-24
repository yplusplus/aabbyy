#include <bits/stdc++.h>
using namespace std;

const int UB = 1222;

int work(double r, double b, double m) {
	int n = 1;
	while (n < UB) {
		b = b * (100 + r) / 100;
		b = floor(b * 100 + 0.5) / 100;
		b -= m;
		if (b <= 1e-8) return n;
		n++;
	}
	return n;
}

int main() {
	double r, b, m;
	ios::sync_with_stdio(0);
	int _;
	cin >> _;
	while (_--) {
		cin >> r >> b >> m;
		int ans = work(r, b, m);
		if (ans > 1200) cout << "impossible" << endl;
		else cout << ans << endl;
	}
	return 0;
}
