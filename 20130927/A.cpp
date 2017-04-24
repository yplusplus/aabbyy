#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-4;
const double PI = acos(-1.0);
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
template<class T> T sqr(T x) { return x * x;}
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double d) { return Point(a.x * d, a.y * d);}
Point operator * (double d, Point a) { return Point(a.x * d, a.y * d);}
Point operator / (Point a, double d) { return Point(a.x / d, a.y / d);}
bool operator < (Point a, Point b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y;}
bool operator == (Point a, Point b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;}

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double veclen(Point a) { return sqrt(dot(a, a));}
inline double angle(Point a) { return atan2(a.y, a.x);}
inline Point vecunit(Point a) { return a / veclen(a);}
inline Point normal(Point a) { return Point(-a.y, a.x) / veclen(a);}
inline bool getpoint(Point &p) { return cin >> p.x >> p.y;}

const int N = 2222;
struct Line {
	Point s, t;
	double a;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) { a = angle(t - s);}
	Point vec() { return t - s;}
	Point point(double p) { return s + vec() * p;}
	bool get() { getpoint(s); getpoint(t); a = angle(t - s); return 1;}
	bool operator < (Line l) const { return a < l.a;}
} ;
inline Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}
inline bool onseg(Point p, Point a, Point b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) < 0;}
inline bool onleft(Point p, Line l) { return sgn(cross(p - l.s, l.vec())) < 0;}
Point cherry;
void adjust(Line &l) { if (!onleft(cherry, l)) l = Line(l.t, l.s);}

Point ip[N];
Line q[N];
int halfplane(Line *l, int n, Point *pt) {
	sort(l, l + n);
	int qh, qt;
	qh = qt = 0;
	q[qt] = l[0];
	//for (int i = 0; i < n + 4; i++) cout << l[i].s.x << ' ' << l[i].s.y << ' ' << l[i].t.x << ' ' << l[i].t.y << ' ' << l[i].a << endl;
	for (int i = 1; i < n; i++) {
		while (qh < qt && !onleft(ip[qt - 1], l[i])) qt--;
		while (qh < qt && !onleft(ip[qh], l[i])) qh++;
		q[++qt] = l[i];
		if (sgn(cross(q[qt].vec(), q[qt - 1].vec())) == 0) {
			qt--;
			if (onleft(l[i].s, q[qt])) q[qt] = l[i];
		}
		if (qh < qt) ip[qt - 1] = llint(q[qt - 1], q[qt]);
	}
	while (qh < qt && !onleft(ip[qt - 1], q[qh])) qt--;
	if (qt - qh <= 1) return 0;
	ip[qt] = llint(q[qt], q[qh]);
	int c = 0;
	for (int i = qh; i <= qt; i++) pt[c++] = ip[i];
	return c;
}

struct Circle {
	Point c;
	double r;
	Circle() {}
	Circle(Point c, double r) : c(c), r(r) {}
	Point point(double p) { return c + r * Point(cos(p), sin(p));}
	bool in(Point a) { return sgn(veclen(c - a) - r) <= 0;}
} cake;
int n;
Line cut[N];

int clint(Circle c, Line l, Point *sol) {
	Point nor = normal(l.vec()), ip = llint(l, Line(c.c, c.c + nor));
	if (!c.in(ip)) return 0;
	double d = veclen(ip - c.c);
	Point dxy = vecunit(l.vec()) * sqrt(fabs(sqr(c.r) - sqr(d)));
	int tt = 0;
	sol[tt] = ip + dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	sol[tt] = ip - dxy;
	if (onseg(sol[tt], l.s, l.t)) tt++;
	return tt;
}

inline double gettri(Circle c, Point a, Point b) { return cross(a - c.c, b - c.c) / 2;}
double getsec(Circle c, Point a, Point b) {
	double a1 = angle(a - c.c), a2 = angle(b - c.c);
	double da = fabs(a1 - a2);
	da = min(da, PI * 2 - da);
	return sgn(cross(a - c.c, b - c.c)) * da * sqr(c.r) / 2;
}

double cal(Circle c, Point *p, int n) {
	Point tmp[2];
	double ret = 0;
	p[n] = p[0];
	for (int i = 0; i < n; i++) {
		int cnt = clint(c, Line(p[i], p[i + 1]), tmp);
		if (cnt == 0) {
			if (cake.in(p[i]) && cake.in(p[i + 1])) ret += gettri(cake, p[i], p[i + 1]);
			else ret += getsec(cake, p[i], p[i + 1]);
		} else if (cnt == 1) {
			if (cake.in(p[i])) ret += gettri(cake, p[i], tmp[0]) + getsec(cake, tmp[0], p[i + 1]);
			else ret += getsec(cake, p[i], tmp[0]) + gettri(cake, tmp[0], p[i + 1]);
		} else {
			if ((p[i] < p[i + 1]) ^ (tmp[0] < tmp[1])) swap(tmp[0], tmp[1]);
			ret += getsec(cake, p[i], tmp[0]) + gettri(cake, tmp[0], tmp[1]) + getsec(cake, tmp[1], p[i + 1]);
		}
	}
	return ret;
}

void input() {
	cake.c = Point(0.0, 0.0);
	cin >> cake.r >> n;
	for (int i = 0; i < n; i++) cut[i].get();
	getpoint(cherry);
	for (int i = 0; i < n; i++) adjust(cut[i]);
}

const double FINF = 1e5;
Point pt[N];
double work() {
	cut[n] = Line(Point(-FINF, -FINF), Point(FINF, -FINF));
	cut[n + 1] = Line(Point(FINF, -FINF), Point(FINF, FINF));
	cut[n + 2] = Line(Point(FINF, FINF), Point(-FINF, FINF));
	cut[n + 3] = Line(Point(-FINF, FINF), Point(-FINF, -FINF));
	//for (int i = 0; i < n + 4; i++) cout << cut[i].s.x << ' ' << cut[i].s.y << ' ' << cut[i].t.x << ' ' << cut[i].t.y << endl;
	int m = halfplane(cut, n + 4, pt);
	//for (int i = 0; i < m; i++) cout << pt[i].x << ' ' << pt[i].y << endl;
	double ans = cal(cake, pt, m);
	ans = fabs(ans) * 100 / (PI * sqr(cake.r));
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(5);
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		input();
		cout << "Case " << cas << ": " << work() << "%" << endl;
	}
	return 0;
}



