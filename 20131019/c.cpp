// 22:32
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
const DB PI = acos(-1.0);
inline int sgn(DB a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }

DB cosx, sinx;
void rotate(DB &a, DB &b) {
	DB na = a * cosx - b * sinx;
	DB nb = a * sinx + b * cosx;
	a = na, b = nb;
}
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const double &p) const { return s + vec() * p; }
} ;
bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) < 0; }
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	bool in(const Point &p) { return sgn(r - veclen(p - c)) >= 0; }
	bool on(const Point &p) { return sgn(r - veclen(p - c)) == 0; }
} ;

struct Point3 {
	DB x, y, z;
	Point3() {}
	Point3(DB x, DB y, DB z) : x(x), y(y), z(z) {}
	bool get() { return cin >> x >> y >> z; }
	Point3 operator - (const Point3 &a) { return Point3(x - a.x, y - a.y, z - a.z); }
} tri[3];
inline Point3 cross(const Point3 &a, const Point3 &b) { return Point3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

Point pt[4];
bool input() {
	for (int i = 0; i < 3; i++) if (!tri[i].get()) return 0;
	return 1;
}

DB H;
Point con(Point3 a, const Point3 &n) {
	DB l1 = veclen(Point(n.x, n.y)), l2 = veclen(Point(l1, n.z));
	if (sgn(l1) == 0) return Point(a.x, a.y);
	cosx = n.x / l1, sinx = -n.y / l1;
	rotate(a.x, a.y);
	cosx = n.z / l2, sinx = l1 / l2;
	rotate(a.x, a.z);
	H = a.z;
	//cout << "z " << a.z << endl;
	return Point(a.x, a.y);
}

Circle cir;
int clint(const Point &a, const Point &b, Point *sol) {
	Point nor = normal(a - b), ip = llint(Line(a, b), Line(cir.c, cir.c + nor));
	DB d = veclen(ip - cir.c);
	if (sgn(cir.r - d) <= 0) return 0;
	Point dxy = vecunit(a - b) * sqrt(cir.r * cir.r - d * d);
	int tt = 0;
	sol[tt] = ip + dxy;
	if (onseg(sol[tt], a, b)) tt++;
	sol[tt] = ip - dxy;
	if (onseg(sol[tt], a, b)) tt++;
	return tt;
}

inline DB gettri(const Point &a, const Point &b) { return cross(a - cir.c, b - cir.c) / 2; }
DB getsec(const Point &a, const Point &b) {
	DB a1 = angle(a - cir.c);
	DB a2 = angle(b - cir.c);
	DB da = fabs(a1 - a2);
	da = min(da, 2 * PI - da);
	//cout << da / PI * 180 << endl;
	return sgn(gettri(a, b)) * cir.r * cir.r * da / 2;
}

DB cal() {
	DB ans = 0;
	//cout << cir.c.x << ' ' << cir.c.y << ' ' << cir.r << endl;
	//for (int i = 0; i < 3; i++) cout << pt[i].x << ' ' << pt[i].y << endl;
	Point tmp[2];
	for (int i = 0; i < 3; i++) {
		int c = clint(pt[i], pt[i + 1], tmp);
		//cout << c << endl;
		if (c == 0) {
			if (cir.in(pt[i]) && cir.in(pt[i + 1])) ans += gettri(pt[i], pt[i + 1]);
			else ans += getsec(pt[i], pt[i + 1]);
		} else if (c == 1) {
			if (!cir.in(pt[i])) ans += getsec(pt[i], tmp[0]) + gettri(tmp[0], pt[i + 1]);
			else ans += gettri(pt[i], tmp[0]) + getsec(tmp[0], pt[i + 1]);
		} else {
			if ((tmp[0] < tmp[1]) ^ (pt[i] < pt[i + 1])) swap(tmp[0], tmp[1]);
			ans += getsec(pt[i], tmp[0]) + gettri(tmp[0], tmp[1]) + getsec(tmp[1], pt[i + 1]);
		}
	}
	return fabs(ans);
}

DB work() {
	Point3 nor = cross(tri[1] - tri[0], tri[2] - tri[0]);
	//cout << nor.x << ' ' << nor.y << ' ' << nor.z << endl;
	for (int i = 0; i < 3; i++) pt[i] = con(tri[i], nor);
	pt[3] = pt[0];
	if (sgn(H - 100) >= 0) return 0;
	cir = Circle(Point(0.0, 0.0), sqrt(10000 - H * H));
	//cout << H << ' ' << cir.r << endl;
	//for (int i = 0; i < 3; i++) cout << i << ' ' << veclen(pt[i] - pt[i + 1]) << endl;
	return cal();
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(5);
	while (input()) cout << work() << endl;
	return 0;
}


