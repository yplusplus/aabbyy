#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1.0);
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
template<class T> T sqr(T x) { return x * x;}
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}
bool operator == (Point a, Point b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;}

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double veclen(Point a) { return sqrt(dot(a, a));}
inline double angle(Point a) { return atan2(a.y, a.x);}
inline Point rotate(Point a, double p) { return Point(a.x * cos(p) - a.y * sin(p), a.x * sin(p) + a.y * cos(p));}
inline Point vecunit(Point a) { return a / veclen(a);}
inline Point normal(Point a) { return Point(-a.y, a.x) / veclen(a);}

const int N = 111;
Point barrier[N], gravity, sun;
int n;

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() { return t - s;}
	Point point(double p) { return s + vec() * p;}
} ;
Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));} 

struct Circle {
	Point c;
	double r;
	Circle() {}
	Circle(Point c, double r) : c(c), r(r) {}
	Point point(double p) { return Point(c.x + r * cos(p), c.y + r * sin(p));}
} earth;

inline void move(Point v) { for (int i = 0; i < n; i++) barrier[i] = barrier[i] + v;}

void rotate_gravity(double p) {
	move(gravity * (-1.0));
	for (int i = 0; i < n; i++) barrier[i] = rotate(barrier[i], p);
	move(gravity);
}

void rotate_earth(double p) {
	move(earth.c * (-1.0));
	for (int i = 0; i < n; i++) barrier[i] = rotate(barrier[i], p);
	move(earth.c);
	gravity = gravity - earth.c;
	gravity = rotate(gravity, p);
	gravity = gravity + earth.c;
}

bool clint(Line l, Circle c, Point *sol) {
	Point v = l.vec(), nor = normal(v);
	Point ip = llint(Line(c.c, c.c + nor), l);
	double r = c.r, d = veclen(ip - c.c);
	if (sgn(d - r) > 0) return 0;
	Point dx = vecunit(l.vec()) * sqrt(fabs(sqr(r) - sqr(d)));
	sol[0] = ip - dx;
	sol[1] = ip + dx;
	return 1;
}

Point O = Point(0.0, 0.0);

void get_gravity() {
	double area = 0;
	gravity = O;
	barrier[n] = barrier[0];
	for (int i = 0; i < n; i++) {
		double a = cross(barrier[i], barrier[i + 1]) / 2;
		gravity = gravity + (barrier[i] + barrier[i + 1]) * (a / 3);
		area += a;
	}
	gravity = gravity / area;
}

inline bool between(Point p, Point a, Point b) { return sgn(dot(a - p, b - p)) < 0;}
double T1, T2, T;

bool touch(double p) { // will touch barrier
	Point to = Circle(sun, 10.0).point(p);
	Line ray(sun, to);
	barrier[n] = barrier[0];
	for (int i = 0; i < n; i++) {
		Line l(barrier[i], barrier[i + 1]);
		if (sgn(cross(l.vec(), ray.vec())) == 0) continue;
		Point ip = llint(l, ray);
		if (between(ip, l.s, l.t) || ip == l.s || ip == l.t) {
			if (between(sun, ip, to)) continue;
			return 1;
		}
	}
	return 0;
}

double dir[N];
bool block_part(double &s, double &t) {
	barrier[n] = barrier[0];
	for (int i = 0; i < n; i++) dir[i] = angle(barrier[i] - sun);
	//for (int i = 0; i < n; i++) cout << dir[i] << endl;
	sort(dir, dir + n);
	dir[n] = dir[0] + PI * 2;
	for (int i = 0; i < n; i++) {
		if (touch((dir[i] + dir[i + 1]) / 2)) continue;
		s = fmod(dir[i + 1], PI * 2), t = fmod(dir[i], PI * 2);
		return 1;
	}
	return 0;
}

double length(Point a, Point b) {
	double a1 = angle(a - earth.c), a2 = angle(b - earth.c);
	double da = fabs(a1 - a2);
	da = min(da, PI * 2 - da);
	return earth.r * da;
}

double work() {
	double da = asin(earth.r / veclen(earth.c - sun));
	if (n <= 1) return earth.r * (PI / 2 - da) * 2;
	get_gravity();
	//cout << "gravity " << gravity.x << ' ' << gravity.y << endl;
	rotate_earth(T / T1 * PI * 2);
	//for (int i = 0; i < n; i++) cout << barrier[i].x << ' ' << barrier[i].y << endl;
	rotate_gravity((T / T2 - T / T1) * PI * 2);
	//for (int i = 0; i < n; i++) cout << barrier[i].x << ' ' << barrier[i].y << endl;
	if (sgn(dot(gravity - earth.c, sun - earth.c)) < 0) return earth.r * (PI / 2 - da) * 2;
	double s, t;
	if (!block_part(s, t)) return 0;
	double d = angle(earth.c - sun);
	double l = d - da, r = d + da;
	//cout << d << ' ' << da << endl;
	//cout << s << ' ' << t << ' ' << l << ' ' << r << endl;
	int tt = 0;
	for (int i = -2; i <= 2; i++) dir[tt++] = s + i * PI * 2, dir[tt++] = t + i * PI * 2;
	dir[tt++] = l, dir[tt++] = r;
	sort(dir, dir + tt);
	double ans = 0;
	Point to, ip1, ip2, tmp[2];
	for (int i = 1; i < tt; i++) {
		if (sgn(l - dir[i - 1]) <= 0 && sgn(dir[i] - r) <= 0) {
			//cout << "range " << dir[i - 1] << ' ' << dir[i] << endl;
			if (!touch((dir[i] + dir[i - 1]) / 2)) {
				//cout << "yes" << endl;
				to = Circle(sun, 10.0).point(dir[i - 1]);
				clint(Line(sun, to), earth, tmp);
				if (veclen(sun - tmp[0]) < veclen(sun - tmp[1])) ip1 = tmp[0];
				else ip1 = tmp[1];
				to = Circle(sun, 10.0).point(dir[i]);
				clint(Line(sun, to), earth, tmp);
				if (veclen(sun - tmp[0]) < veclen(sun - tmp[1])) ip2 = tmp[0];
				else ip2 = tmp[1];
				//cout << ip1.x << ' ' << ip1.y << ' ' << ip2.x << ' ' << ip2.y << endl;
				ans += length(ip1, ip2);
			}
		}
	}
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(8);
	while (cin >> sun.x >> sun.y >> earth.c.x >> earth.c.y >> earth.r) {
		cin >> n >> T1 >> T2 >> T;
		for (int i = 0; i < n; i++) cin >> barrier[i].x >> barrier[i].y;
		cout << work() << endl;
	}
	cout << (PI / 2 - asin(3.0 / 8)) * 6 << endl;
	return 0;
}



