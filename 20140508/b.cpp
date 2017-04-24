#include <bits/stdc++.h>
using namespace std;

typedef double DB;
DB a, b, c, d;
DB l1, r1, l2, r2;
const DB UNIT = 1.0;
const DB MAX = 1e3;
const DB EPS = 1e-10;
const int T = 1 << 8;

inline DB getPart(const DB &a, const DB &b, const DB &x, const DB &y) { return x * y / 2 * (a * x / 3 + b); }
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
DB getVolume(const DB &a, const DB &b, const DB &x, const DB &y) {
	if (x <= UNIT) {
		if (y <= UNIT) {
			return getPart(a, b, x, y);
		} else {
			return getPart(a, b, x, y) - getPart(a, b, x / y * (y - UNIT), y - UNIT);
		}
	} else {
		if (y <= UNIT) {
			DB d = y / x * (x - UNIT);
			return d * UNIT * (a / 2 + b) + getPart(a, b, UNIT, y - d);
		} else {
			DB d = y / x * (x - UNIT);
			if (d >= UNIT) return (UNIT * a / 2 + b) * UNIT * UNIT;
			return d * UNIT * (a / 2 + b) + getPart(a, b, UNIT, y - d) - getPart(a, b, x / y * (y - UNIT), y - UNIT);
		}
	}
}

void find(const DB &c, const DB &d, const DB &x) {
	l2 = 0, r2 = MAX;
	DB halfVolume = (c / 2 + d) / 2, m;
	for (int i = 0; i < T; ++i) {
		m = (l2 + r2) / 2;
		if (getVolume(c, d, m, x) < halfVolume) l2 = m;
		else r2 = m;
	}
}

void solve() {
	//cout << getVolume(a, b, 1.1682544017813692, 1.1682544017813692) << endl;
	l1 = 0, r1 = MAX;
	if (sgn(a) && sgn(c)) {
		DB halfVolume = (a / 2 + b) / 2, m;
		for (int i = 0; i < T; ++i) {
			m = (l1 + r1) / 2;
			find(c, d, m);
			if (getVolume(a, b, m, l2) < halfVolume) l1 = m;
			else r1 = m;
		}
		//cout << getVolume(a, b, l1, l2) << ' ' << getVolume(c, d, l2, l1) << endl;
		//cout << l1 << ' ' << l2 << endl;
		//cout << (100 / l1) << ' ' << (100 / l2) << ' ' << -100.0 << endl;
		if (sgn(halfVolume - getVolume(a, b, l1, l2))) cout << "0 0 0" << endl;
		else cout << (100 / l1) << ' ' << (100 / l2) << ' ' << -100.0 << endl;
	} else {
		if (sgn(a) == 0 && sgn(c) == 0) {
			cout << "1 1 -1" << endl;
		} else {
			if (sgn(a)) {
				cout << 0.0 << ' ' << 2.0 << ' ' << -1.0 << endl;
			} else {
				cout << 2.0 << ' ' << 0.0 << ' ' << -1.0 << endl;
			}
		}
	}
}

int run() {
	while (cin >> a >> b >> c >> d) solve();
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	freopen("bacteria.in", "r", stdin);
	freopen("bacteria.out", "w", stdout);
	return run();
}
