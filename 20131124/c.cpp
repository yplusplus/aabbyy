#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB EPS = 1e-10;
const DB PI = acos(-1.0);
typedef pair<DB, DB> Point;
#define x first
#define y second
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline bool get(Point &a) { return cin >> a.x >> a.y; }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool btwn(const Point &p, const Point &a, const Point &b) { return sgn(dot(a - p, b - p)) < 0; }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	bool in(const Point &a) const { return sgn(veclen(a - c) - r) < 0; }
} ;

template<class T> T sqr(T a) { return a * a; }
int clint(const Circle &c, const Line &l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (!c.in(ip)) return 0;
	DB d = sqr(c.r) - sqr(veclen(ip - c.c));
	d = fabs(d); d = sqrt(d);
	int tt = 0;
	sol[tt] = ip + vecunit(l.vec()) * d;
	if (btwn(sol[tt], l.s, l.t)) tt++;
	sol[tt] = ip - vecunit(l.vec()) * d;
	if (btwn(sol[tt], l.s, l.t)) tt++;
	return tt;
}

DB Rm, R, r;
Point coin, v;
const DB FINF = 1e20;
const Point O(0.0, 0.0);

DB work() {
	Point p1[2], p2[2];
	int k1 = clint(Circle(O, Rm + r), Line(coin, coin + vecunit(v) * FINF), p1);
	int k2 = clint(Circle(O, R + r), Line(coin, coin + vecunit(v) * FINF), p2);
	if (k2 == 0) return 0;
	if (k1 == 0) return veclen(p2[0] - p2[1]) / veclen(v);
	return min(veclen(p2[0] - p1[0]), veclen(p2[0] - p1[1])) * 2 / veclen(v);
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> Rm >> R >> r) {
		get(coin); get(v);
		cout << work() << endl;
	}
	return 0;
}
