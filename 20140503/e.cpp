#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int T = 1 << 8;
const DB PI = acos(-1.0);
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
struct Point {
	DB x, y, z;
	Point() {}
	Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
	void get() { cin >> x >> y >> z; }
} ;
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y, a.z - b.z); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }

DB r, d, nr;
Point Andy, Geo;
Point dxy;

inline DB fix(const DB &a) { return max(-1.0, min(1.0, a)); }
DB getDist(const Point &a, const Point &b) { // base on center(0, 0)
	DB ang = acos(fix(dot(a, b) / veclen(a) / veclen(b)));
	return r * ang;
}
inline DB getDist(const Point &M) { return getDist(Andy, M) + getDist(Geo - dxy, M - dxy); }
inline bool onFirst(const Point &a) { return sgn(veclen(a) - r) == 0; }
template<class T> inline T sqr(const T &a) { return a * a; }
inline Point getPoint(const DB &a) { return Point(nr * cos(a), nr * sin(a), d / 2); }

DB ts(DB L, DB R) {
	DB M1, M2, D, d1, d2;
	for (int i = 0; i < T; ++i) {
		D = (R - L) / 3;
		M1 = L + D;
		M2 = R - D;
		d1 = getDist(getPoint(M1));
		d2 = getDist(getPoint(M2));
		if (d1 > d2) L = M1;
		else R = M2;
	}
	return getDist(getPoint((L + R) / 2));
}

DB solve() {
	nr = sqrt(sqr(r) - sqr(d / 2));
	DB ans = DBL_MAX;
	for (int i = 0; i < T; ++i) {
		DB L = PI * 4 / T * i, R = PI * 4 / T * (i + 1);
		ans = min(ts(L, R), ans);
	}
	return ans;
}

int run() {
	while (cin >> r >> d) {
		Andy.get();
		Geo.get();
		dxy = Point(0, 0, d);
		bool b1 = onFirst(Andy);
		bool b2 = onFirst(Geo);
		if (b1 ^ b2) {
			if (b2) swap(Geo, Andy);
			cout << solve() << endl;
		} else {
			if (b1) cout << getDist(Andy, Geo) << endl;
			else cout << getDist(Andy - dxy, Geo - dxy) << endl;
		}
	}
	return 0;
}

int main() {
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
