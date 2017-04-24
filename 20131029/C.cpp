#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB EPS = 1e-10;
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }
DB a1, b1, a2, b2;
DB n, m, x[2], y[2];
DB t[2];

DB cal(DB *a, DB *b) {
	//cout << a[0] << ' ' << a[1] << ' ' << b[0] << ' ' << b[1] << endl;
	DB d = a2 * a[0] + b2 * b[0] - a2 * a[1] - b2 * b[1];
	if (sgn(d) > 0) return a1 * a[1] + b1 * b[1];
	if (sgn(d) < 0) return a1 * a[0] + b1 * b[0];
	return max(a1 * a[0] + b1 * b[0], a1 * a[1] + b1 * b[1]);
}

void update(DB a, DB &ans) {
	if (a > ans) {
		ans = a;
		t[0] = x[0], t[1] = y[0];
	}
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> a1 >> b1 >> a2 >> b2 >> n >> m) {
		DB ans = 0, sum = (a2 * n + b2 * m) / 2;
		x[0] = 0, y[0] = 0;
		x[1] = n, y[1] = m;
		update(cal(x, y), ans);
		x[0] = n, y[0] = m;
		x[1] = 0, y[1] = 0;
		update(cal(x, y), ans);
		x[0] = 0, x[1] = n;
		if (sgn(a2 * n - sum) >= 0) y[0] = m, y[1] = 0;
		else y[1] = (sum - a2 * n) / b2, y[0] = m - y[1];
		update(cal(x, y), ans);
		x[0] = n, x[1] = 0;
		if (sgn(b2 * m - sum) <= 0) y[0] = 0, y[1] = m;
		else y[1] = sum / b2, y[0] = m - y[1];
		update(cal(x, y), ans);
		y[0] = 0, y[1] = m;
		if (sgn(b2 * m - sum) >= 0) x[0] = n, x[1] = 0;
		else x[1] = (sum - b2 * m) / a2, x[0] = n - x[1];
		update(cal(x, y), ans);
		y[0] = m, y[1] = 0;
		if (sgn(a2 * n - sum) <= 0) x[0] = 0, x[1] = n;
		else x[1] = sum / a2, x[0] = n - x[1];
		update(cal(x, y), ans);
		//cout << ans << endl;
		cout << t[0] << ' ' << t[1] << endl;
	}
	return 0;
}