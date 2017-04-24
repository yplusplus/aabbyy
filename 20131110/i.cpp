#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-8;
const DB FINF = 1e10;
template<class T> T sqr(T x) { return x * x; }
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }

inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
bool get(Point &a) { return scanf("%lf%lf", &a.x, &a.y) != -1; }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
	bool btwn(const Point &p) const { return sgn(dot(s - p, t - p)) < 0; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.t) / cross(a.vec(), b.vec())); }

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
	DB d;
	if (c.out(ip) || c.on(ip)) d = 0;
	else {
		d = veclen(ip - c.c);
		d = sqrt(max((DB) 0.0, sqr(c.r) - sqr(d)));
	}
	Point dxy = vecunit(l.vec()) * d;
	sol[0] = ip + dxy;
	sol[1] = ip - dxy;
	return 2;
}

const int N = 111;
Point V, pt[N];
Line track;
DB v1, v2, R, dis[N][N], best[N];
struct Seg {
	DB s, t;
	int id;
	void fix() { if (s > t) swap(s, t); }
	Seg() {}
	Seg(DB s, DB t, int id) : s(s), t(t), id(id) {}
	bool operator < (const Seg &a) const {
		if (sgn(s - a.s)) return s < a.s;
		return t < a.t;
	}
} seg[N];
int n;
DB cal_dis(const Point &p) { return veclen(p) / v1 * sgn(dot(V, p)); }

DB work() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) dis[i][j] = veclen(pt[i] - pt[j]) / v2;
	}
	Point tmp[2];
	for (int i = 0; i < n; i++) {
		int t = clint(Circle(pt[i], R), track, tmp);
		seg[i].s = cal_dis(tmp[0]);
		seg[i].t = cal_dis(tmp[1]);
		seg[i].id = i;
		seg[i].fix();
	}
	sort(seg, seg + n);
	//for (int i = 0; i < n; i++) cout << seg[i].s << ' ' << seg[i].t << ' ' << seg[i].id << endl;
	memset(best, 0, sizeof(best));
	for (int i = 0; i < n; i++) {
		best[i] = seg[i].t - seg[i].s;
		for (int j = 0; j < i; j++) {
			if (sgn(seg[i].t - seg[j].t) <= 0) continue;
			if (sgn(seg[j].t - seg[i].s) < 0) {
				DB dt = dis[seg[i].id][seg[j].id];
				dt -= seg[i].s - seg[j].t;
				dt = max(0.0, dt);
				best[i] = max(best[j] - dt + seg[i].t - seg[i].s, best[i]);
			} else {
				DB dt = dis[seg[i].id][seg[j].id];
				best[i] = max(best[j] - (seg[j].t - seg[i].s) - dt + seg[i].t - seg[i].s, best[i]);
			}
		}
	}
	DB ans = 0;
	for (int i = 0; i < n; i++) ans = max(best[i], ans);
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	int _;
	scanf("%d", &_);
	while (_--) {
		scanf("%d%lf%lf", &n, &R, &v2);
		get(V); v1 = veclen(V);
		for (int i = 0; i < n; i++) get(pt[i]);
		track = Line(V * (-1.0), V);
		printf("%.2f\n", work());
	}
	return 0;
}
