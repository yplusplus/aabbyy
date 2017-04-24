#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB PI = acos(-1.0);
const DB D = 1e-10;
const DB FINF = 1e55;
const DB EPS = 1e-12;
inline int sgn(const DB &p) { return (p > EPS) - (p < -EPS); }
template<class T> T sqr(T x) { return x * x; }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0; }
inline bool btseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) < 0; }
inline bool between(const Point &p, const Point &a, const Point &b) { return sgn(dot(a - p, b - p)) < 0; }
inline bool get(Point &a) { return cin >> a.x >> a.y; }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return c + Point(cos(p), sin(p)) * r; }
	bool on(const Point &p) const { return sgn(veclen(p - c) - r) == 0; }
	bool in(const Point &p) const { return sgn(veclen(p - c) - r) < 0; }
	bool out(const Point &p) const { return sgn(veclen(p - c) - r) > 0; }
	bool get() { return cin >> c.x >> c.y >> r; }
} ;

int clint(const Circle &c, const Line &l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (c.out(ip) || c.on(ip)) return 0;
	DB d = veclen(ip - c.c);
	Point dxy = vecunit(l.vec()) * sqrt(sqr(c.r) - sqr(d));
	int tt = 0;
	sol[tt] = ip + dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	sol[tt] = ip - dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	return tt;
}

Point rect[11], mouse;
Circle disk;

int in_rect(const Point &p) {
	int wn = 0;
	rect[4] = rect[0];
	for (int i = 0; i < 4; i++) {
		if (onseg(p, rect[i], rect[i + 1])) return -1;
		int k = sgn(cross(rect[i + 1] - rect[i], p - rect[i]));
		int d1 = sgn(rect[i].y - p.y);
		int d2 = sgn(rect[i + 1].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0) wn++;
		if (k < 0 && d2 <= 0 && d1 > 0) wn--;
	}
	return wn != 0;
}

const int N = 222;
Line side[11];
Point pts[N];
DB dis[N][N];

void floyd(int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
			}
		}
	}
}

DB cal(int a, int b) {
	if (a == b) return 0;
	if (a > b) return dis[b][a];
	Point &pa = pts[a], &pb = pts[b];
	if (in_rect(pa) == 1 || in_rect(pb) == 1) return FINF;
	for (int i = 0; i < 4; i++) {
		if (sgn(cross(pa - pb, side[i].vec())) == 0) continue;
		Point ip = llint(Line(pa, pb), side[i]);
		if (between(ip, pa, pb) && between(ip, side[i].s, side[i].t)) return FINF;
	}
	return veclen(pa - pb);
}

DB work() {
	rect[4] = rect[0];
	for (int i = 0; i < 4; i++) {
		Point d = vecunit(rect[i + 1] - rect[i]) * D;
		side[i] = Line(rect[i] - d, rect[i + 1] + d);
	}
	int tt = 0, c;
	Point tmp[6];
	pts[tt++] = mouse;
	for (int i = 0; i < 4; i++) {
		c = clint(disk, side[i], tmp);
		for (int j = 0; j < c; j++) {
			DB ang = angle(tmp[j] - disk.c);
			pts[tt++] = disk.point(ang + D);
			pts[tt++] = disk.point(ang - D);
		}
		pts[tt++] = side[i].s;
		pts[tt++] = side[i].t;
	}
	c = clint(disk, Line(mouse, disk.c), tmp);
	for (int i = 0; i < c; i++) pts[tt++] = tmp[i];
	sort(pts + 1, pts + tt);
	tt = (int) (unique(pts, pts + tt) - pts);
	for (int i = 0; i < tt; i++) {
		for (int j = 0; j < tt; j++) {
			dis[i][j] = cal(i, j);
		}
	}
	//cout << tt << endl;
	//for (int i = 0; i < tt; i++) cout << i << ' ' << cal(0, i) << ' ' << pts[i].x << ' ' << pts[i].y << endl;
	//for (int i = 0; i < tt; i++) {
		//for (int j = 0; j < tt; j++) {
			//if (dis[i][j] == FINF) cout << "inf ";
			//else cout << dis[i][j] << ' ';
		//}
		//cout << endl;
	//}
	floyd(tt);
	DB ans = FINF;
	for (int i = 0; i < tt; i++) {
		if (!disk.on(pts[i])) continue;
		if (in_rect(pts[i])) continue;
		ans = min(dis[0][i], ans);
	}
	return ans;
}

void fix() {
	DB s = 0;
	rect[4] = rect[0];
	for (int i = 0; i < 4; i++) s += cross(rect[i], rect[i + 1]);
	if (sgn(s) < 0) reverse(rect, rect + 4);
}

bool input() {
	for (int i = 0; i < 4; i++) if (!get(rect[i])) return 0;
	fix();
	disk.get();
	get(mouse);
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(8);
	while (input()) cout << (double) work() << endl;
	return 0;
}



