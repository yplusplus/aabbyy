#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double DB;
DB h1, h2, d1, d2, a, b;
const DB EPS = 1e-8;
const int T = 222;
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }

DB cal(DB x) { return sqrt(max((h1 - a * x * x) / b, (DB) 0.0)) + x; }

DB dc3(DB l, DB r) {
	DB d, m1, m2;
	for (int i = 0; i < T; i++) {
		d = (r - l) / 3;
		m1 = l + d, m2 = r - d;
		if (cal(m1) < cal(m2)) l = m1;
		else r = m2;
	}
	return (l + r) / 2;
}

DB dc2(DB l, DB r) {
	DB m;
	DB L = cal(l), R = cal(r);
	for (int i = 0; i < T; i++) {
		m = (l + r) / 2;
		if (cal(m) - d2 > 0) {
			if (L > R) l = m;
			else r = m;
		} else {
			if (L > R) r = m;
			else l = m;
		}
	}
	return (l + r) / 2;
}

bool check(DB x) {
	//cout << "x " << x << ' ' << cal(x) << endl;
	if (sgn(cal(x) - d2)) return 0;
	if (sgn(0 - x) <= 0 && x < d1) {
		DB y = h1 - a * x * x;
		y -= b * (d1 - x) * (d1 - x);
		//cout << "y " << y << endl;
		return sgn(y - h2) >= 0;
	} else {
		DB y = h1 - a * d1 * d1;
		//cout << "y " << y << endl;
		return sgn(y - h2) >= 0;
	}
}

bool work() {
	DB e = sqrt(h1 / a), mx = dc3((DB) 0.0, e), ans;
	//cout << e << ' ' << mx << endl;
	//cout << cal(0.0) << '/' << cal(e) << '~' << cal(mx) << endl;
	ans = dc2((DB) 0.0, mx);
	if (check(ans)) return 1;
	ans = dc2(mx, e);
	if (check(ans)) return 1;
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(6);
	while (cin >> h1 >> h2 >> d1 >> d2 >> a >> b) {
		if (work()) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
