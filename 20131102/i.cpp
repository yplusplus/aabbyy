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
const DB EPS = 1e-8;
const DB FINF = 1e6;
const int T = 333;
inline int sgn(const DB &a) { return (a < EPS) - (a > -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline Point vecunit(const Point &a) { return a / veclen(a); }

DB pt2seg(const Point &p, const Point &a, const Point &b) {
	if (a == b) return veclen(p - a);
	if (sgn(dot(p - a, b - a)) <= 0) return veclen(p - a);
	if (sgn(dot(p - b, a - b)) <= 0) return veclen(p - b);
	return fabs(cross(a - p, b - p) / veclen(a - b));
}

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

Point pt[4];
int id[4];

bool input() {
	for (int i = 0; i < 4; i++) {
		if (!(cin >> pt[i].x >> pt[i].y)) return 0;
	}
	return 1;
}

Point ori(0.0, 0.0);

DB dc2() {
	Point &a = pt[id[0]], &b = pt[id[1]];
	Point &c = pt[id[2]], &d = pt[id[3]];
	Point l = a + vecunit(a - b) * FINF;
	Point r = b + vecunit(b - a) * FINF;
	Point m1, m2, dx;
	for (int i = 0; i < T; i++) {
		dx = (r - l) / 3;
		m1 = l + dx; m2 = r - dx;
		DB d1 = veclen(m1) + fabs(cross(c - m1, d - m1) / veclen(c - d));
		DB d2 = veclen(m2) + fabs(cross(c - m2, d - m2) / veclen(c - d));
		if (d1 > d2) l = m1;
		else r = m2;
	}
	return veclen(l) + fabs(cross(c - l, d - l) / veclen(c - d));
}

DB work() {
	DB ans = FINF;
	for (int i = 0; i < 4; i++) id[i] = i;
	do {
		ans = min(ans, dc2());
	} while (next_permutation(id, id + 4));
	return ans;
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (input()) cout << work() << endl;
	return 0;
}

