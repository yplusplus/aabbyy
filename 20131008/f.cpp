#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-6;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}

typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y;}

inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double angle(Point a) { return atan2(a.y, a.x);}
inline double veclen(Point a) { return sqrt(dot(a, a));}
inline Point vecunit(Point a) { return a / veclen(a);}
inline Point normal(Point a) { return Point(-a.y, a.x) / veclen(a);}
inline bool scan(Point &a) { return cin >> a.x >> a.y;}

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() { return t - s;}
	Point point(double p) { return s + vec() * p;}
} ;
Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}
inline bool onseg(Point p, Point a, Point b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0;}

struct Circle {
	Point c;
	double r;
	Circle() {}
	Circle(double p) { c + Point(cos(p), sin(p)) * r;}
	bool in(Point a) { return sgn(veclen(a - c) - r) < 0;}
} ;

void print(Point &a) { cout << a.x << ' ' << a.y << endl;}
template<class T> T sqr(T x) { return x * x;}
int clint(Circle c, Line l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (!c.in(ip)) return 0;
	double d = sqrt(sqr(c.r) - sqr(veclen(ip - c.c)));
	Point dxy = vecunit(l.vec()) * d;
	int tt = 0;
	sol[tt] = ip + dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	sol[tt] = ip - dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	return tt;
}

Circle cir;
Point rect[11];

inline double gettri(Circle c, Point a, Point b) { return cross(a - c.c, b - c.c) / 2;}
inline double getsec(Circle c, Point a, Point b) {
	double a1 = angle(a - c.c);
	double a2 = angle(b - c.c);
	double da = fabs(a1 - a2);
	da = min(da, PI * 2 - da);
	return sgn(cross(a - c.c, b - c.c)) * da * sqr(c.r) / 2;
}

double cal(int n) {
	double ret = 0;
	rect[n] = rect[0];
	Point tmp[2];
	for (int i = 0; i < n; i++) {
		int cnt = clint(cir, Line(rect[i], rect[i + 1]), tmp);
		if (cnt == 0) {
			if (cir.in(rect[i]) || cir.in(rect[i + 1])) ret += gettri(cir, rect[i], rect[i + 1]);
			else ret += getsec(cir, rect[i], rect[i + 1]);
		}
		if (cnt == 1) {
			if (cir.in(rect[i]) || !cir.in(rect[i + 1]) && sgn(veclen(rect[i + 1] - cir.c) - cir.r)) ret += gettri(cir, rect[i], tmp[0]) + getsec(cir, tmp[0], rect[i + 1]);
			else ret += getsec(cir, rect[i], tmp[0]) + gettri(cir, tmp[0], rect[i + 1]);
		}
		if (cnt == 2) {
			if ((tmp[0] < tmp[1]) ^ (rect[i] < rect[i + 1])) swap(tmp[0], tmp[1]);
			ret += getsec(cir, rect[i], tmp[0]) + gettri(cir, tmp[0], tmp[1]) + getsec(cir, tmp[1], rect[i + 1]);
		}
		//cout << cnt << ' ' << ret << endl;
	}
	return ret;
}
		



int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	double a, b, c, d;
	bool pnt = 0;
	while (scan(cir.c)) {
		if (pnt) cout << endl;
		else pnt = 1;
		cin >> cir.r;
		cin >> a >> b >> c >> d;
		if (a > c) swap(a, c);
		if (b > d) swap(b, d);
		rect[0] = Point(a, b);
		rect[1] = Point(c, b);
		rect[2] = Point(c, d);
		rect[3] = Point(a, d);
		cout << cal(4) << endl;
	}
	return 0;
}
