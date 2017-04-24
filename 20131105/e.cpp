#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-6;
const DB PI = acos(-1.0);
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }

inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return c + Point(cos(p), sin(p)) * r; }
	bool on(const Point &p) const { return sgn(veclen(p - c) - r) == 0; }
} ;

template<class T> inline T sqr(T x) { return x * x; }
// 0~2 : ip cnt
// -1 : coin..
int ccint(const Circle &a, const Circle &b, Point *sol) {
	if (sgn(a.r) == 0) {
		sol[0] = a.c;
		return 1;
	}
	if (sgn(b.r) == 0) {
		sol[0] = b.c;
		return 1;
	}
	DB d = veclen(a.c - b.c);
	DB sr = a.r + b.r, dr = fabs(a.r - b.r);
	if (sgn(d - sr) > 0) return 0;
	if (sgn(d - dr) < 0) return 0;
	if (sgn(d) == 0 && sgn(dr) == 0) return -1;
	DB ang = angle(b.c - a.c);
	d = (sqr(a.r) + sqr(d) - sqr(b.r)) / (2 * a.r * d);
	d = min(max(d, -1.0), 1.0);
	DB da = acos(d);
	sol[0] = a.point(ang + da);
	sol[1] = a.point(ang - da);
	if (sol[0] == sol[1]) return 1;
	return 2;
}

Point A, B;
inline bool get(Point &a) { return cin >> a.x >> a.y; }
inline Circle convert(const Circle &cir, const DB &a, const DB &b, const Point &m) {
	Point t = m - cir.c;
	return Circle(t * b / a + m, cir.r * b / a);
}

inline DB fix(const DB &x) { return sgn(x) ? x : 0; }

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(2);
	while (get(A)) {
		get(B);
		DB a, b, c, d, v;
		cin >> a >> b >> c >> d >> v;
		a *= v, b *= v, c *= v, d *= v;
		if (sgn(a + b) == 0) {
			cout << 1 << endl;
			cout << A.x << ' ' << A.y << endl;
		} else if (sgn(c + d) == 0) cout << -1 << endl;
		else {
			Point ip[2];
			int t = ccint(Circle(A, b), Circle(B, c), ip);
			if (t == -1) cout << -1 << endl;
			else {
				Point ans[11];
				int cnt = 0, cc = 0;
				for (int i = 0; i < 2; i++) {
					Circle img = convert(Circle(B, d), c + d, a + b, ip[i]);
					cc = ccint(Circle(A, a), img, ans + cnt);
					if (cc == -1) {
						cnt = -1;
						break;
					} else cnt += cc;
				}
				if (cnt == -1) cout << -1 << endl;
				else {
					sort(ans, ans + cnt);
					cc = cnt; cnt = 0;
					for (int i = 0; i < cc; i++) {
						if (i == 0 || !(ans[i] == ans[i - 1])) ans[cnt++] = ans[i];
					}
					cout << cnt << endl;
					for (int i = 0; i < cnt; i++) cout << fix(ans[i].x) << ' ' << fix(ans[i].y) << endl;
				}
			}
		}
	}
	return 0;
}

