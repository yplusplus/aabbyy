#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-10;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline bool get(Point &a) { return cin >> a.x >> a.y; }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} l1, l2;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

DB check() {
	Line a(l1.s, l1.s + normal(l1.vec()));
	Line b(l1.t, l1.t + normal(l1.vec()));
	Line c(l2.s, l2.s + normal(l2.vec()));
	Line d(l2.t, l2.t + normal(l2.vec()));
	Point p1 = llint(a, l1);
	Point p2 = llint(b, l1);
	Point p3 = llint(c, l1);
	Point p4 = llint(d, l1);
	if (p2 < p1) swap(p1, p2);
	if (p4 < p3) swap(p3, p4);
//	cout << p1.x << ' ' << p1.y << endl;
//	cout << p2.x << ' ' << p2.y << endl;
//	cout << p3.x << ' ' << p3.y << endl;
//	cout << p4.x << ' ' << p4.y << endl;
	if (p2 < p3 || p4 < p1) return 0;
	if (p1 == p4 || p2 == p3) return 0;
	return -1;
}

int andrew(Point *p, int n, Point *ch) {
	sort(p, p + n);
	int m = 0;
	for (int i = 0; i < n; i++) {
		while (m > 1 && sgn(cross(p[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--) {
		while (m > k && sgn(cross(p[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) m--;
		ch[m++] = p[i];
	}
	return m;
}

DB area(Point *p, int n) {
	p[n] = p[0];
	DB s = 0;
	for (int i = 0; i < n; i++) s += cross(p[i], p[i - 1]);
	return fabs(s / 2);
}

DB work() {
	if (sgn(veclen(l1.vec())) == 0 || sgn(veclen(l2.vec())) == 0) return 0;
	if (sgn(cross(l1.vec(), l2.vec())) == 0) return check();
	Line a(l1.s, l1.s + normal(l1.vec()));
	Line b(l1.t, l1.t + normal(l1.vec()));
	Line c(l2.s, l2.s + normal(l2.vec()));
	Line d(l2.t, l2.t + normal(l2.vec()));
	Point p[11], ch[11]; int tt = 0;
	p[tt++] = llint(a, c);
	p[tt++] = llint(a, d);
	p[tt++] = llint(b, c);
	p[tt++] = llint(b, d);
	int m = andrew(p, 4, ch);
	return area(ch, m);
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (get(l1.s)) {
		get(l1.t); get(l2.s); get(l2.t);
		DB ans = work();
		if (ans < -0.5) cout << -1 << endl;
		else cout << ans << endl;
	}
	return 0;
}
