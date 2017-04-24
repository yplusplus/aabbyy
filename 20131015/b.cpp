#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (const Point &a, const double &p) { return Point(a.x * p, a.y * p);}
Point operator * (const double &p, const Point &a) { return Point(a.x * p, a.y * p);}
Point operator / (const Point &a, const double &p) { return Point(a.x / p, a.y / p);}

inline double cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x;}
inline double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y;}
inline double veclen(const Point &a) { return sqrt(dot(a, a));}
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a);}

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s;}
	Point point(double p) const { return s + vec() * p;}
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}

struct Circle {
	Point c;
	double r;
	Circle() {}
	Circle(Point c, double r) : c(c), r(r) {}
	bool in(const Point &p) { return sgn(veclen(p - c) - r) <= 0;}
} ;

inline Circle get_cir(const Point &a, const Point &b) { return Circle((a + b) / 2, veclen(a - b) / 2);}
Circle get_cir(const Point &a, const Point &b, const Point &c) {
	if (sgn(dot(b - a, c - a)) <= 0) return get_cir(b, c);
	if (sgn(dot(a - b, c - b)) <= 0) return get_cir(a, c);
	if (sgn(dot(b - c, a - c)) <= 0) return get_cir(b, a);
	Point m1 = (a + b) / 2, m2 = (b + c) / 2;
	Point n1 = normal(a - b), n2 = normal(b - c);
	Point ip = llint(Line(m1, m1 + n1), Line(m2, m2 + n2));
	return Circle(ip, veclen(ip - a));
}

const int N = 111;
Point pt[N];
int n;

Circle min_cir() {
	random_shuffle(pt, pt + n);
	Circle ans(pt[0], 0.0);
	for (int i = 0; i < n; i++) {
		if (ans.in(pt[i])) continue;
		ans = Circle(pt[i], 0.0);
		for (int j = 0; j < i; j++) {
			if (ans.in(pt[j])) continue;
			ans = get_cir(pt[i], pt[j]);
			for (int k = 0; k < j; k++) {
				if (ans.in(pt[k])) continue;
				ans = get_cir(pt[i], pt[j], pt[k]);
			}
		}
	}
	return ans;
}

bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;}

bool check(const Circle &a) { 
	for (int i = 0; i < n; i++)
		if (a.c == pt[i]) return 1;
	return 0;
}

Circle fix(const Circle &a) {
	Point t;
	for (int i = 0; i < n; i++) {
		if (sgn(veclen(a.c - pt[i]) - a.r) == 0) {
			t = pt[i];
			break;
		}
	}
	Point nor = (a.c - t) / veclen(a.c - t) * 0.5;
	return Circle(a.c + nor, veclen(a.c + nor - t));
}

Circle work() {
	Circle ret(Point(0.0, 0.0), 0.0);
	for (int i = 0; i < n; i++) {
		ret.r = max(ret.r, veclen(pt[i]));
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> pt[i].x >> pt[i].y;
		//Circle tmp = min_cir();
		//if (check(tmp)) tmp = fix(tmp);
		Circle tmp = work();
		cout << tmp.c.x << ' ' << tmp.c.y << ' ' << tmp.r << endl;
	}
	return 0;
}





