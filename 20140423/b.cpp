#define MY_LOCAL 0
#include <bits/stdc++.h>
using namespace std;

typedef double DB;
struct Point {
	DB x, y;
	Point() {}
	Point(DB x, DB y) : x(x), y(y) {}
	void get() { cin >> x >> y; }
} ;
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
const DB EPS = 1e-4;
const DB MOVE = 0.2;
const DB DIST1 = 1e2;
const DB DIST2 = 1e6;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
inline Point middle(const Point &a, const Point &b) { return (a + b) / 2; }
inline Point normal(const Point &a) { return Point(-a.y, a.x); }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(p - a, p - b)) == 0 && sgn(dot(a - p, b - p)) < 0; }
inline Point vecunit(const Point &a) { return a / veclen(a); }
Point s1[2], s2[2];

bool input() {
	for (int i = 0; i < 2; ++i) s1[i].get();
	for (int i = 0; i < 2; ++i) s2[i].get();
	DB sum = 0;
	for (int i = 0; i < 2; ++i) sum += veclen(s1[i]);
	for (int i = 0; i < 2; ++i) sum += veclen(s2[i]);
	return sgn(sum);
}

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	bool in(const Point &a) const { return sgn(veclen(a - c) - r) < 0; }
	bool out(const Point &a) const { return sgn(veclen(a - c) - r) > 0; }
} ;

inline bool check(const Circle &c, const Point &a, const Point &b) {
	if (c.in(a) && c.out(b)) return 1;
	if (c.in(b) && c.out(a)) return 1;
	return 0;
}

bool check(const Point &a, const Point &b, const Point &c, const Point &d) {
	Point ap = a + vecunit(b - a) * MOVE;
	Point cp = c + vecunit(d - c) * MOVE;
	//cout << ap.x << ' ' << ap.y << ' ' << cp.x << ' ' << cp.y << endl;
	Point mid = middle(ap, cp), nor = normal(ap - cp);
	Circle temp;
	temp.c = mid + nor * DIST1;
	temp.r = veclen(temp.c - ap);
	//cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
	if (check(temp, a, b) && check(temp, c, d)) {
		cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
		return 1;
	}
	temp.c = mid - nor * DIST1;
	temp.r = veclen(temp.c - ap);
	//cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
	if (check(temp, a, b) && check(temp, c, d)) {
		cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
		return 1;
	}
	temp.c = mid + nor * DIST2;
	temp.r = veclen(temp.c - ap);
	//cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
	if (check(temp, a, b) && check(temp, c, d)) {
		cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
		return 1;
	}
	temp.c = mid - nor * DIST2;
	temp.r = veclen(temp.c - ap);
	//cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
	if (check(temp, a, b) && check(temp, c, d)) {
		cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
		return 1;
	}
	return 0;
}

bool check() {
	Point v1 = s1[0] - s1[1];
	Point v2 = s2[0] - s2[1];
	if (sgn(cross(v1, v2)) == 0) {
		if (onseg(s1[0], s2[0], s2[1]) && onseg(s1[1], s2[0], s2[1])) {
			Circle temp(middle(s1[0], s1[1]) - vecunit(v1) * DIST2, DIST2);
			if (check(temp, s1[0], s1[1]) && check(temp, s2[0], s2[1])) {
				cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
				return 1;
			}
		}
		if (onseg(s2[0], s1[0], s1[1]) && onseg(s2[1], s1[0], s1[1])) {
			Circle temp(middle(s2[0], s2[1]) - vecunit(v1) * DIST2, DIST2);
			if (check(temp, s1[0], s1[1]) && check(temp, s2[0], s2[1])) {
				cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
				return 1;
			}
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (sgn(veclen(s1[i] - s2[j]))) continue;
			Circle temp(s1[i], MOVE);
			if (check(temp, s1[0], s1[1]) && check(temp, s2[0], s2[1])) {
				cout << temp.c.x << ' ' << temp.c.y << ' ' << temp.r << endl;
				return 1;
			}
		}
	}
	return 0;
}

void work() {
	bool ok = 0;
	if (check()) {
		ok = 1;
	} else {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				if (check(s1[i], s1[i ^ 1], s2[j], s2[j ^ 1])) {
					ok = 1;
					return ;
				}
			}
		}
	}
	if (!ok) while (1);
}

int run() {
	while (input()) work();
	return 0;
}

int main() {
#if MY_LOCAL
	freopen("in_b", "r", stdin);
#else
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
