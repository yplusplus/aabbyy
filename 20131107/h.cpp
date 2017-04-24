#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-8;
const DB PI = acos(-1.0);
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline bool inrect(const Point &p, const Point &a, const Point &b) { return sgn(a.x - p.x) < 0 && sgn(p.x - b.x) < 0 && sgn(a.y - p.y) < 0 && sgn(p.y - b.y) < 0; }


struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0; }
inline bool btseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) < 0; }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return c + Point(cos(p), sin(p)) * r; }
	bool in(const Point &a) const { return sgn(veclen(a - c) - r) < 0; }
	bool out(const Point &a) const { return sgn(veclen(a - c) - r) > 0; }
	bool on(const Point &a) const { return sgn(veclen(a - c) - r) == 0; }
} cup;

template<class T> T sqr(T x) { return x * x; }
int clint(const Circle &c, const Line &l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (c.out(ip)) return 0;
	DB d = max(sqr(c.r) - sqr(veclen(ip - c.c)), 0.0);
	Point dxy = vecunit(l.vec()) * sqrt(d);
	int tt = 0;
	sol[tt] = ip + dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	sol[tt] = ip - dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	return tt;
}

const int N = 55;
DB R;
int n;
Point pt[N][5];
Point ips[N << 4];

bool inrect(const Point &p) {
	for (int i = 0; i < n; i++) {
		if (inrect(p, pt[i][0], pt[i][2])) return 1;
	}
	return 0;
}

bool cmp(const Point &a, const Point &b) { return sgn(angle(a) - angle(b)) < 0; }

DB get_sec(const Point &a, const Point &b) {
	DB a1 = angle(a), a2 = angle(b);
	return R * (a2 - a1);
}

DB work() {
	int tt = 0, c;
	cup = Circle(Point(0.0, 0.0), R);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			tt += clint(cup, Line(pt[i][j], pt[i][j + 1]), ips + tt);
		}
	}
	DB ans = 0;
	Point mid;
	ips[tt++] = cup.point(-PI + EPS);
	ips[tt++] = cup.point(PI - EPS);
	sort(ips, ips + tt, cmp);
	for (int i = 0; i < tt - 1; i++) {
		//cout << ips[i].x << ' ' << ips[i].y << endl;
		mid = cup.point((angle(ips[i]) + angle(ips[i + 1])) / 2);
		//cout << "ang " << angle(ips[i]) << ' ' << angle(ips[i + 1]) << endl;
		//cout << "mid " << mid.x << ' ' << mid.y << endl;
		if (inrect(mid)) ans += get_sec(ips[i], ips[i + 1]);
	}
	if (tt > 1) {
		mid = cup.point((angle(ips[0]) + angle(ips[tt - 1])) / 2 + PI);
		if (inrect(mid)) {
			DB a1 = angle(ips[0]), a2 = angle(ips[tt - 1]);
			ans += R * (a1 - a2 + 2 * PI);
		}
	}
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	int t;
	while (~scanf("%lf%d", &R, &t)) {
		//cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		double a, b, c, d;
		n = 0;
		for (int i = 0; i < t; i++) {
			scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
			if (a > c) swap(a, c);
			if (b > d) swap(b, d);
			if (sgn(a - c) == 0 || sgn(b - d) == 0) continue;
			pt[n][0] = Point(a, b);
			pt[n][1] = Point(c, b);
			pt[n][2] = Point(c, d);
			pt[n][3] = Point(a, d);
			pt[n][4] = pt[n][0];
			n++;
		}
		printf("%.3f\n", work());
	}
	return 0;
}


