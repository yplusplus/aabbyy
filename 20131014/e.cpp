#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
const double END = 1e-5;
inline int sgn(const double &x) { return (x > EPS) - (x < -EPS);}
const double K = 0.8;
const double D = 100.0;
const double PI = acos(-1.0);
const double FINF = 1e100;
const int N = 33;
const int T = 6;

typedef pair<double, double> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (const Point &a, const double &p) { return Point(a.x * p, a.y * p);}
Point operator / (const Point &a, const double &p) { return Point(a.x / p, a.y / p);}
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;}

inline double cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x;}
inline double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y;}
inline double veclen(const Point &a) { return sqrt(dot(a, a));}
inline double rd() { return rand() % 1000 / 1000.0;}
inline double rd_dir() { return rd() * 2 * PI;}
inline Point rd_pt(double r) { double t = rd_dir(); return Point(cos(t), sin(t)) * r;}

bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0;}
double pt2seg(const Point &p, const Point &a, const Point &b) {
	if (a == b) return veclen(p - a);
	if (sgn(dot(p - a, b - a)) <= 0) return veclen(p - a);
	if (sgn(dot(p - b, a - b)) <= 0) return veclen(p - b);
	return fabs(cross(a - p, b - p)) / veclen(a - b);
}

int n;
Point pt[N];

double cal(const Point &p) {
	double ret = FINF;
	for (int i = 0; i < n; i++) ret = min(ret, pt2seg(p, pt[i], pt[i + 1]));
	return ret;
}

bool inpoly(const Point &p) {
	int wn = 0;
	for (int i = 0; i < n; i++) {
		if (onseg(p, pt[i], pt[i + 1])) return 0;
		int k = sgn(cross(pt[i + 1] - pt[i], p - pt[i]));
		int d1 = sgn(pt[i].y - p.y);
		int d2 = sgn(pt[i + 1].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0) wn++;
		if (k < 0 && d2 <= 0 && d1 > 0) wn--;
	}
	return wn != 0;
}

void SAA(Point &p) {
	double r = D, nd, bd = cal(p);
	Point np;
	while (r > END) {
		int t = T;
		bool ok = 1;
		while (t--) {
			np = p + rd_pt(r);
			if (!inpoly(np)) continue;
			double nd = cal(np);
			if (sgn(nd - bd) > 0) p = np, bd = nd, ok = 0;
		}
		if (ok) r *= K;
	}
}

double work() {
	pt[n] = pt[0];
	double best = 0;
	for (int i = 0; i < n; i++) {
		Point tmp;
		int cnt = 55;
		while (cnt--) {
			tmp = pt[i] + rd_pt(0.8);
			if (inpoly(tmp)) {
				SAA(tmp);
				best = max(best, cal(tmp));
			}
		}
	}
	return best;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(2);
	srand(time(0));
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> pt[i].x >> pt[i].y;
		cout << work() << endl;
	}
	return 0;
}

