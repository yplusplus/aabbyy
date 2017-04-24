#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 222;
const double EPS = 1e-6;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, double p) { return Point(a.x / p, a.y / p);}

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double area(Point a, Point b, Point c) { return cross(b - a, c - a) / 2;}
Point O = Point(0.0, 0.0);
Point poly[N], pt[N];

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() { return t - s;}
	Point point(double p) { return s + vec() * p;}
} ;

inline Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}
inline bool between(Point x, Point a, Point b) { return sgn(dot(a - x, b - x)) <= 0;}

Point gravity(Point *pt, int n) {
	Point ret = O;
	double sum = 0;
	pt[n] = pt[0];
	for (int i = 0; i < n; i++) {
		double t = area(O, pt[i], pt[i + 1]);
		ret = ret + (pt[i] + pt[i + 1]) * t / 3;
		sum += t;
	}
	return ret / sum;
}

int n, m;
double L, R, ry[N];
bool safe(double y) {
	Line l(Point(0.0, y), Point(1.0, y));
	int s, t;
	s = 0;
	while (s < m - 1) {
		Point ip = llint(l, Line(pt[s], pt[s + 1]));
		if (between(ip, pt[s], pt[s + 1])) break;
		s++;
	}
	t = m - 2;
	while (t >= 0) {
		Point ip = llint(l, Line(pt[t], pt[t + 1]));
		if (between(ip, pt[t], pt[t + 1])) break;
		t--;
	}
	int tt = 0;
	poly[tt++] = llint(l, Line(pt[s], pt[s + 1]));
	for (int i = s + 1; i <= t; i++) poly[tt++] = pt[i];
	poly[tt++] = llint(l, Line(pt[t], pt[t + 1]));
	Point g = gravity(poly, tt);
	if (sgn(L - g.x) <= 0 && sgn(g.x - R) <= 0) return 1;
	return 0;
}

double dc2(double l, double r) {
	double m;
	while (r - l > EPS) {
		m = (l + r) / 2;
		if (safe(m)) l = m;
		else r = m;
	}
	return m;
}

double cy[N];
int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(3);
	int T;
	double H;
	cin >> T;
	while (T-- && cin >> n >> m) {
		for (int i = 0; i < n; i++) {
			cin >> pt[i].x >> pt[i].y;
			ry[i] = pt[i].y;
		}
		L = pt[0].x;
		reverse(pt, pt + n);
		m += n;
		for (int i = n; i < m ; i++) {
			cin >> pt[i].x >> pt[i].y;
			ry[i] = pt[i].y;
		}
		R = pt[n].x;
		H = min(pt[0].y, pt[m - 1].y);
		sort(ry, ry + m);
		n = (int) (unique(ry, ry + m) - ry);
		bool fall = 0;
		double ans;
		for (int i = 1; i < n; i++) {
			if (sgn(ry[i] - H) > 0) break;
			//cout << i << ' ' << safe(ry[i - 1]) << ' ' << safe(ry[i]) << endl;
			if (safe(ry[i - 1]) && !safe(ry[i])) {
				ans = dc2(ry[i - 1], ry[i]);
				fall = 1;
				break;
			}
		}
		if (fall) cout << ans << endl;
		else cout << H << endl;
	}
	return 0;
}





