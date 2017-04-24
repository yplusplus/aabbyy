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
const DB EPS = 1e-5;
const DB FINF = 1e5;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
template<class T> inline T sqr(T x) { return x * x; }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline DB angle(const Point &a, const Point &b) { return acos(max(min(dot(a, b) / veclen(a) / veclen(b), (DB) 1.0), (DB) -1.0)); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
DB sinx, cosx;
inline Point rotate(const Point &a) { return Point(a.x * cosx - a.y * sinx, a.x * sinx + a.y * cosx); }
inline bool get(Point &a) { return cin >> a.x >> a.y; }

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
inline bool btwn(const Point &p, const Point &a, const Point &b) { return sgn(dot(a - p, b - p)) < 0; }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return c + Point(cos(p), sin(p)) * r; }
	bool in(const Point &p) const { return sgn(veclen(p - c) - r) < 0; }
	bool on(const Point &p) const { return sgn(veclen(p - c) - r) == 0; }
	bool out(const Point &p) const { return sgn(veclen(p - c) - r) > 0; }
} ;

int clint(const Circle &c, const Line &l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (c.out(ip) || c.on(ip)) return 0;
	DB d = sqrt(sqr(c.r) - sqr(veclen(ip - c.c)));
	Point dxy = vecunit(l.vec()) * d;
	int tt = 0;
	sol[tt] = ip + dxy;
	if (btseg(sol[tt], l.s, l.t)) tt++;
	sol[tt] = ip - dxy;
	if (btseg(sol[tt], l.s, l.t)) tt++;
	return tt;
}

DB RI;
Point refract(const Point &n, const Point &v) {
	DB ang = angle(n, v);
	//cout << "n " << n.x << ' ' << n.y << endl;
	//cout << "v " << v.x << ' ' << v.y << endl;
	//cout << ang << endl;
	sinx = sin(ang) / RI;
	cosx = sqrt(1.0 - sqr(sinx));
	//cout << asin(sinx) << ' ' << acos(cosx) << endl;
	Point tmp;
	tmp = rotate(n);
	if (sgn(cross(tmp, n)) * sgn(cross(tmp, v)) <= 0) return tmp;
	sinx = -sin(ang) / RI;
	cosx = sqrt(1.0 - sqr(sinx));
	tmp = rotate(n);
	if (sgn(cross(tmp, n)) * sgn(cross(tmp, v)) <= 0) return tmp;
	return v;
}

Circle Ocean;
Line cal(const Point &p, const Point &v, bool &ok) {
	Point inf = p + vecunit(v) * FINF;
	Point tmp[2];
	int c = clint(Ocean, Line(p, inf), tmp);
	if (c == 0) ok = 0;
	Point ip = inf;
	for (int i = 0; i < c; i++) if (veclen(ip - p) > veclen(tmp[i] - p)) ip = tmp[i];
	Point to = refract(Ocean.c - ip, v);
	//cout << "to " << to.x << ' ' << to.y << endl;
	return Line(ip, ip + vecunit(to) * FINF);
}

Point p[2], v[2];
Line ray[2];
int main() {
	//freopen("in", "r", stdin);
	while (cin >> Ocean.r >> RI) {
		Ocean.c = Point(0.0, 0.0);
		bool ok = 1;
		for (int i = 0; i < 2; i++) {
			get(p[i]); get(v[i]);
			ray[i] = cal(p[i], v[i], ok);
		}
		if (!ok) {
			cout << "No" << endl;
			continue;
		}
		if (sgn(cross(ray[0].vec(), ray[1].vec())) == 0) {
			if (onseg(ray[0].s, ray[1].s, ray[1].t) && onseg(ray[1].s, ray[0].s, ray[0].t)) cout << "Yes" << endl;
			else cout << "No" << endl;
		} else {
			Point ip = llint(ray[0], ray[1]);
			if (Ocean.in(ip)) cout << "Yes" << endl;
			else cout << "No" << endl;
			//cout << ip.x << ' ' << ip.y << endl;
		}
	}
	return 0;
}


