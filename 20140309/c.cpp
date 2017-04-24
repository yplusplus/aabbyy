#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
typedef vector<Point> VP;
typedef vector<DB> VD;
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
istream &operator >> (istream &in, Point &a) { in >> a.x >> a.y; return in; }

const DB EPS = 1e-6;
const DB PI = acos(-1.0);
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }

void work(VD &a, int n) {
	sort(a.begin(), a.end());
	a.push_back(a[0] + PI * 2);
	bool ok = 0;
	int l, r;
	DB ans;
	for (int i = 0; i < n; ++i) {
		if (sgn(a[i + 1] - a[i] - PI) >= 0) {
			ok = 1;
			l = (i + 1) % n, r = i;
			DB dt1 = a[l] + PI / 2;
			DB dt2 = a[r] - PI / 2;
			if (fabs(dt1 + PI * 2) < fabs(dt1)) dt1 += PI * 2;
			if (fabs(dt1 - PI * 2) < fabs(dt1)) dt1 -= PI * 2;
			if (fabs(dt2 + PI * 2) < fabs(dt2)) dt2 += PI * 2;
			if (fabs(dt2 - PI * 2) < fabs(dt2)) dt2 -= PI * 2;
			if (sgn(fabs(dt1) - fabs(dt2)) == 0) ans = max(dt1, dt2);
			else {
				if (sgn(fabs(dt1) - fabs(dt2)) < 0) ans = dt1;
				else ans = dt2;
			}
			ans *= 180 / PI;
		}
	}
	a.pop_back();
	if (!ok) {
		cout << "Unacceptable" << endl;
		return ;
	}
	if (sgn(a[0] + PI / 2) >= 0 && sgn(a[n - 1] - PI / 2) <= 0) cout << "Acceptable as proposed" << endl;
	else {
		if (ans > 0) cout << "Acceptable after clockwise rotation of " << fabs(ans) << " degrees" << endl;
		else cout << "Acceptable after counterclockwise rotation of " << fabs(ans) << " degrees" << endl;
	}
}

int run() {
	int n, theta, cas = 0;
	while (cin >> n >> theta && (n + theta)) {
		VP pt(n + 1);
		pt[0] = Point(0, 0);
		for (int i = 1; i <= n; ++i) cin >> pt[i];
		VD ang(n);
		for (int i = 0; i < n; ++i) ang[i] = angle(pt[i + 1] - pt[i]);
		cout << "Case " << ++cas << ": ";
		if (0 == theta) cout << "Acceptable as proposed" << endl;
		else work(ang, n);
		cout << endl;
	}
	return 0;
}

int main() {
	//freopen("in_c", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	return run();
}
