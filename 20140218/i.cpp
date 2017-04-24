#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-10;
const DB FINF = 1e88;
const DB PI = acos(-1.0);
const DB PI2 = PI * 2;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
template<class T> inline T sqr(T x) { return x * x; }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point vecunit(const Point &a) { return a / veclen(a); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
	Line move(const DB &d) const {
		Point nor = normal(vec()) * d;
		return Line(s + nor, t + nor);
	}
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0; }
inline bool btseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) < 0; }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return c + Point(cos(p), sin(p)) * r; }
	bool in(const Point &a) const { return sgn(veclen(a - c) - r) < 0; }
	bool on(const Point &a) const { return sgn(veclen(a - c) - r) == 0; }
	bool out(const Point &a) const { return sgn(veclen(a - c) - r) > 0; }
} ;

int clint(const Circle &c, const Line &l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (c.out(ip)) return 0;
	if (c.on(ip)) {
		if (onseg(ip, l.s, l.t)) {
			sol[0] = ip;
			return 1;
		}
		return 0;
	}
	Point dxy = vecunit(l.vec()) * sqrt(sqr(c.r) - sqr(veclen(ip - c.c)));
	int tt = 0;
	if (onseg(sol[tt] = ip + dxy, l.s, l.t)) tt++;
	if (onseg(sol[tt] = ip - dxy, l.s, l.t)) tt++;
	return tt;
}

int ccint(const Circle &a, const Circle &b, Point *sol) { // Special for this problem
	DB d = veclen(a.c - b.c);
	if (sgn(d - a.r - b.r) > 0) return 0;
	d /= 2;
	DB ang = angle(b.c - a.c), da = acos(d / a.r);
	if (sgn(d - a.r - b.r) == 0) {
		sol[0] = a.point(ang);
		return 1;
	}
	sol[0] = a.point(ang + da);
	sol[1] = a.point(ang - da);
	return 2;
}

const int N = 111;
const Point O(0, 0);
DB r, horizon[N], vertical[N];
int n;
Point pt[N], dest;
Line line[N];
Circle cir[N];

typedef pair<int, bool> Node; // 0-on segment, 1-on circle
typedef pair<Point, Node> Status;

Status find_circle(const Status &a) {
	int id = a.y.x, best_id;
	bool pos;
	DB best = FINF, ang, cur_ang = angle(a.x - cir[id].c);
	Point tmp[2];
	for (int i = id + 1; i < n; i++) { // line
		int cnt = clint(cir[id], line[i], tmp);
		for (int j = 0; j < cnt; j++) {
			ang = angle(tmp[j] - cir[id].c);
			if (sgn(ang - cur_ang) > 0) ang -= PI2;
			//cout << "line " << ang << ' ' << cur_ang << ' ' << line[i].s.x << ' ' << line[i].s.y << ' ' << line[i].t.x << ' ' << line[i].t.y << endl;
			//cout << tmp[j].x << ' ' << tmp[j].y << ' ' << onseg(tmp[j], line[i].s, line[i].t) << endl;
			if (best > cur_ang - ang) best = cur_ang - ang, best_id = i, pos = 0;
		}
	}
	for (int i = id + 1; i < n; i++) { // circle
		int cnt = ccint(cir[id], cir[i], tmp);
		for (int j = 0; j < cnt; j++) {
			ang = angle(tmp[j] - cir[id].c);
			if (sgn(ang - cur_ang) > 0) ang -= PI2;
			//cout << "circle " << ang << ' ' << cur_ang << ' ' << tmp[j].x << ' ' << tmp[j].y << endl;
			if (best > cur_ang - ang) best = cur_ang - ang, best_id = i, pos = 1;
		}
	}
	//cout << "change angle " << best << endl;
	return Status(cir[id].point(cur_ang - best), Node(best_id, pos));
}

Status find_line(const Status &a) {
	int id = a.y.x, best_id;
	bool pos;
	Point tmp[2], best = a.x + vecunit(line[id].vec()) * FINF;
	for (int i = id + 1; i < n; i++) { // line
		if (sgn(cross(line[i].vec(), line[id].vec())) == 0) continue;
		tmp[0] = llint(line[i], line[id]);
		if (!onseg(tmp[0], line[i].s, line[i].t) || !onseg(tmp[0], line[id].s, line[id].t)) continue;
		if (sgn(veclen(tmp[0] - a.x) - veclen(best - a.x)) < 0) {
			best = tmp[0], best_id = i, pos = 0;
		}
	}
	for (int i = id; i < n; i++) { // circle
		int cnt = clint(cir[i], line[id], tmp);
		for (int j = 0; j < cnt; j++) {
			if (sgn(veclen(tmp[j] - a.x) - veclen(best - a.x)) < 0) {
				best = tmp[j], best_id = i, pos = 1;
			}
		}
	}
	return Status(best, Node(best_id, pos));
}

DB cal_circle(const Status &a, const Status &b) {
	int id = a.y.x;
	DB ang_a = angle(a.x - cir[id].c);
	DB ang_b = angle(b.x - cir[id].c);
	if (sgn(ang_b - ang_a) > 0) ang_b -= PI2;
	return r * (ang_a - ang_b);
}
inline DB cal_line(const Status &a, const Status &b) { return veclen(a.x - b.x); }

DB work() {
	DB sum = 0;
	Status cur(Point(0, r), Node(1, 0)), next;
	while (sgn(cur.x.x - dest.x) < 0) {
		if (cur.y.y) {
			next = find_circle(cur);
			sum += cal_circle(cur, next);
		} else {
			next = find_line(cur);
			sum += cal_line(cur, next);
		}
		cur = next;
		//cout << cur.x.x << ' ' << cur.x.y << ' ' << cur.y.x << ' ' << cur.y.y << endl;
	}
	return sum;
}

int main() {
	int cas = 1;
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(3);
	while (cin >> r >> n && n) {
		for (int i = 0; i < n; i++) cin >> horizon[i] >> vertical[i];
		pt[0] = O;
		for (int i = 0; i < n; i++) pt[i + 1 << 1] = (pt[i << 1 | 1] = pt[i << 1] + Point(horizon[i], 0)) + Point(0, vertical[i]);
		n <<= 1;
		dest = pt[n - 1];
		//cout << n << endl;
		//for (int i = 0; i < n; i++) cout << pt[i].x << ' ' << pt[i].y << endl;
		for (int i = 0; i < n; i++) cir[i] = Circle(pt[i], r);
		for (int i = 1; i < n; i++) line[i] = Line(pt[i - 1], pt[i]);
		for (int i = 1; i < n; i++) line[i] = line[i].move(r);
		cout << "Case " << cas++ << ": Distance = " << work() << endl << endl;
	}
	return 0;
}
