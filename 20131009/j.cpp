#include <cstdio>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const long double EPS = 1e-14;
const long double PI = acos(-1.0);
inline int sgn(long double x) { return (x > EPS) - (x < -EPS);}

struct Point {
	long double x, y, z;
	Point() {}
	Point(const long double &x, const long double &y, const long double &z) : x(x), y(y), z(z) {}
} ;
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y, a.z + b.z);}
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y, a.z - b.z);}
Point operator * (const Point &a, const long double &p) { return Point(a.x * p, a.y * p, a.z * p);}
Point operator / (const Point &a, const long double &p) { return Point(a.x / p, a.y / p, a.z / p);}

inline long double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z;}
inline Point cross(const Point &a, const Point &b) { return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);}
inline long double veclen(const Point &a) { return sqrt(dot(a, a));}
inline Point vecunit(const Point &a) { return a / veclen(a);}
inline long double triarea(const Point &a, const Point &b, const Point &c) { return veclen(cross(b - a, c - a));}
inline void print(Point a) { cout << a.x << ' ' << a.y << ' ' << a.z << endl;}

struct Plane {
	Point p, n;
	Plane() {}
	Plane(Point p, Point n) : p(p), n(n) {}
} ;
// warn for directed dist~
inline long double pt2plane(const Point &p, const Point &p0, const Point &n) { return dot(p - p0, n) / veclen(n);}
inline long double pt2plane(const Point &p, const Plane &P) { return pt2plane(p, P.p, P.n);}
// get projection
inline Point ptonplane(const Point &p, const Point &p0, const Point &n) {
	double dis = pt2plane(p, p0, n);
	//cout << "n "; print(n);
	//cout << dis << endl;
	return p - vecunit(n) * dis;
}
inline Point ptonplane(const Point &p, const Plane &P) { return ptonplane(p, P.p, P.n);}
inline bool ptinplane(const Point &p, const Point &p0, const Point &n) { return sgn(dot(p - p0, n)) == 0;}
inline bool ptinplane(const Point &p, const Plane &P) { return ptinplane(p, P.p, P.n);}

struct Line {
	Point s, t;
	Line() {}
	Line(const Point &s, const Point &t) : s(s), t(t) {}
	Point vec() { return t - s;}
} ;

inline long double pt2line(const Point &p, const Point &s, const Point &t) {
	Point v1 = t - s, v2 = p - s;
	return veclen(cross(v1, v2)) / veclen(v1);
}
inline long double pt2line(const Point &p, const Line &l) { return pt2line(p, l.s, l.t);}

int lpint(const Point &s, const Point &t, const Point &p0, const Point &n, Point &x) {
	long double r1 = dot(n, p0 - s);
	long double r2 = dot(n, t - s);
	if (sgn(r2) == 0) {
		if (ptinplane(s, p0, n)) return 2;
		return 0;
	}
	x = s + (t - s) * (r1 / r2);
	return 1;
}
inline int lpint(const Line &l, const Plane &p, Point &x) { return lpint(l.s, l.t, p.p, p.n, x);}

Point ptonline(Point p, Line l) {
	Plane P(p, l.vec());
	Point ret;
	if (lpint(l, P, ret) != 1) cout << "???" << endl;
	return ret;
}

bool ptinquad(const Point &p, const Point &a, const Point &b, const Point &c, const Point &d) {
	long double a1 = triarea(p, a, b);
	long double a2 = triarea(p, b, c);
	long double a3 = triarea(p, c, d);
	long double a4 = triarea(p, d, a);
	long double b1 = triarea(a, b, c);
	long double b2 = triarea(c, d, a);
	//cout << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << ' ' << b1 << ' ' << b2 << endl;
	//cout << "area " << a1 + a2 + a3 + a4 << ' ' << b1 + b2 << endl;
	return sgn(a1 + a2 + a3 + a4 - b1 - b2) == 0;
}

bool scan(Point &a) { return cin >> a.x >> a.y >> a.z;}
struct Ball {
	Point c;
	long double r;
	Ball() {}
	Ball(const Point &c, const long double &r) : c(c), r(r) {}
	bool get() {
		scan(c);
		return cin >> r;
	}
} planet;

template<class T> T sqr(T x) { return x * x;}
int lbint(Line l, Ball b, Point *sol) {
	long double dis = pt2line(b.c, l);
	if (sgn(dis - b.r) > 0) return 0;
	Point ip = ptonline(b.c, l);
	if (sgn(dis - b.r)) {
		long double ds = sqrt(sqr(b.r) - sqr(dis));
		sol[0] = ip + vecunit(l.vec()) * ds;
		sol[1] = ip - vecunit(l.vec()) * ds;
		return 2;
	} else {
		sol[0] = ip;
		return 1;
	}
	return -1;
}

bool operator < (const Point &a, const Point &b) {
	if (sgn(a.x - b.x)) return a.x < b.x;
	if (sgn(a.y - b.y)) return a.y < b.y;
	return a.z < b.z;
}	
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0 && sgn(a.z - b.z) == 0;}

long double pt2seg(const Point &p, const Point &a, const Point &b) {
	if (a == b) return veclen(p - a);
	Point v1 = b - a, v2 = p - a, v3 = p - b;
	if (sgn(dot(v1, v2)) < 0) return veclen(v2);
	if (sgn(dot(v1, v3)) > 0) return veclen(v3);
	return veclen(cross(v1, v2)) / veclen(v1);
}

Point a, b, v;

const long double FINF = 1e20;
const int T = 222;
long double dc3() {
	Point a1, b1, a2, b2;
	long double l = 0, r = FINF, m1, m2;
	for (int i = 0; i < T; i++) {
		long double t = (r - l) / 3;
		m1 = l + t, m2 = r - t;
		a1 = a + v * m1, b1 = b + v * m1;
		a2 = a + v * m2, b2 = b + v * m2;
		long double d1 = pt2seg(planet.c, a1, b1);
		long double d2 = pt2seg(planet.c, a2, b2);
		if (d1 > d2) l = m1;
		else r = m2;
	}
	return l;
}

long double dc2(long double r) {
	long double l = 0, m;
	Point ap, bp;
	for (int i = 0; i < T; i++) {
		long double m = (l + r) / 2;
		ap = a + v * m, bp = b + v * m;
		if (pt2seg(planet.c, ap, bp) <= planet.r) r = m;
		else l = m;
	}
	return l;
}

int work() {
	long double t = dc3();
	//cout << "t " << t << endl;
	if (sgn(t) == 0 || sgn(pt2seg(planet.c, a + v * t, b + v * t) - planet.r) > 0) return 0;
	long double p = dc2(t);
	Point ap, bp;
	ap = a + v * p, bp = b + v * p;
	//cout << veclen(ap - planet.c) << ' ' << planet.r << endl;
	//cout << veclen(bp - planet.c) << ' ' << planet.r << endl;
	//cout << sgn(veclen(bp - planet.c) - planet.r) << endl;
	Point ip = ptonline(planet.c, Line(ap, bp));
	//if (sgn(dot(ap - ip, bp - ip)) == 0) return 2;
	//return 1;
	if (sgn(veclen(ap - planet.c) - planet.r) == 0 || sgn(veclen(bp - planet.c) - planet.r) == 0) return 1;
	return 2;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(6);
	while (planet.get()) {
		scan(a);
		scan(b);
		scan(v);
		int ans = work();
		if (ans == 0) cout << "False alarm" << endl;
		else if (ans == 1) cout << "Crash" << endl;
		else cout << "Warning" << endl;
	}
	return 0;
}




