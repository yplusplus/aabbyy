#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1.0);
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}

inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double veclen(Point a) { return sqrt(dot(a, a));}
inline Point vecunit(Point a) { return a / veclen(a);}
inline Point normal(Point a) { return Point(-a.y, a.x) / veclen(a);}
inline double angle(Point x) { return atan2(x.y, x.x);}

const int N = 11111;
struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() { return t - s;}
	Point point(double p) { return s + vec() * p;}
} stick[N];
inline Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}
typedef pair<double, int> Event;
Event ev[N << 2];

int getevent(int n) {
	int c = 0;
	for (int i = 1; i <= n; i++) {
		Line &s = stick[i];
		double a = angle(s.s), b = angle(s.t);
		if (a > b) swap(a, b);
		if (b - a > PI) {
			ev[c++] = Event(-PI, i), ev[c++] = Event(a, -i);
			ev[c++] = Event(b, i), ev[c++] = Event(PI, -i);
		} else ev[c++] = Event(a, i), ev[c++] = Event(b, -i);
	}
	return c;
}

Line ray;
struct Seg { 
	int a;
	Seg() {}
	Seg(int a) : a(a) {}
	bool operator < (Seg t) const {
		int b = t.a;
		Point ia = llint(stick[a], ray), ib = llint(stick[b], ray);
		return veclen(ia) < veclen(ib);
	}
	bool operator == (Seg t) const { return a == t.a;}
} ;
multiset<Seg> seg;
set<int> see;

int work(int m) {
	sort(ev, ev + m);
	//cout << m << endl;
	//for (int i = 0; i < m; i++) cout << ev[i].first << ' ' << ev[i].second << endl;
	seg.clear();
	see.clear();
	int p = 0;
	ray = Line(Point(0, 0), Point(-1, 0));
	while (p < m && sgn(ev[p].x + PI) == 0) {
		if (ev[p].y > 0) seg.insert(Seg(ev[p].y));
		else seg.erase(Seg(-ev[p].y));
		p++; 
	}
	while (p < m) {
		if (seg.size()) see.insert(seg.begin()->a);
		if (ev[p].y > 0) {
			ray.t = Point(cos(ev[p].x), sin(ev[p].x));
			seg.insert(Seg(ev[p].y));
		} else seg.erase(Seg(-ev[p].y));
		if (sgn(ev[p].x - PI) == 0) break;
		p++;
	}
	return see.size();
}

int main() {
	//freopen("in", "r", stdin);
	int n;
	while (~scanf("%d", &n)) {
		Point a;
		scanf("%lf%lf", &a.x, &a.y);
		for (int i = 1; i <= n; i++) {
			Line &s = stick[i];
			scanf("%lf%lf%lf%lf", &s.s.x, &s.s.y, &s.t.x, &s.t.y);
			s.s = s.s - a, s.t = s.t - a;
		}
		int m = getevent(n);
		printf("%d\n", work(m));
	}
	return 0;
}



