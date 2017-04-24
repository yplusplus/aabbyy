#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second

const DB PI = acos(-1.0);
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline Point vecunit(const Point &a) { return a / veclen(a); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool onSeg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) < 0; }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return c + Point(cos(p), sin(p)) * r; }
	bool in(const Point &a) const { return sgn(veclen(a - c) - r) < 0; }
	bool on(const Point &a) const { return sgn(veclen(a - c) - r) == 0; }
	bool out(const Point &a) const { return sgn(veclen(a - c) - r) > 0; }
} ;
int clint(const Circle &c, const Line &l, Point *const pt) {
	Point v = normal(l.vec());
	Point ip = llint(l, Line(c.c, c.c + v));
	DB d = veclen(ip - c.c);
	if (sgn(d - c.r) >= 0) return 0;
	d = sqrt(c.r * c.r - d * d);
	int t = 0;
	Point temp;
	temp = ip + vecunit(l.vec()) * d;
	if (onSeg(temp, l.s, l.t)) pt[t++] = temp;
	temp = ip - vecunit(l.vec()) * d;
	if (onSeg(temp, l.s, l.t)) pt[t++] = temp;
	return t;
}

DB getSec(const Circle &c, const Point &a, const Point &b) {
	DB a1 = angle(a - c.c);
	DB a2 = angle(b - c.c);
	//if (a2 < a1) a2 += PI * 2;
	return c.r * c.r * (a2 - a1) / 2;
}
DB getTri(const Circle &c, const Point &a, const Point &b) { return cross(a - c.c, b - c.c) / 2; }

Circle origin;
vector<Point> polygon;

DB solve(int n) {
	DB area = 0;
	polygon.push_back(polygon[0]);
	Point temp[2];
	for (int i = 0; i < n; ++i) {
		int cnt = clint(origin, Line(polygon[i], polygon[i + 1]), temp);
		if (cnt == 0) {
			if (origin.in(polygon[i])) {
				area += getTri(origin, polygon[i], polygon[i + 1]);
			} else {
				area += getSec(origin, polygon[i], polygon[i + 1]);
			}
		} else if (cnt == 1) {
			if (origin.in(polygon[i])) {
				area += getTri(origin, polygon[i], temp[0]);
				area += getSec(origin, temp[0], polygon[i + 1]);
			} else {
				area += getSec(origin, polygon[i], temp[0]);
				area += getTri(origin, temp[0], polygon[i + 1]);
			}
		} else {
			if ((temp[0] < temp[1]) ^ (polygon[i] < polygon[i + 1])) {
				swap(temp[0], temp[1]);
			}
			area += getSec(origin, polygon[i], temp[0]);
			area += getTri(origin, temp[0], temp[1]);
			area += getSec(origin, temp[1], polygon[i + 1]);
		}
	}
	polygon.pop_back();
	return fabs(area);
}

int run() {
	int n;
	while (cin >> n) {
		origin.c = Point(0, 0);
		cin >> origin.r;
		polygon.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> polygon[i].x >> polygon[i].y;
		}
		cout << solve(n) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
