#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

typedef pair<double, double> Point;
template<class T> T sqr(T x) { return x * x;}
#define x first
#define y second

const double PI = acos(-1.0);
const double EPS = 1e-8;
const double FINF = 1e100;
const int N = 55;
Point pos[N];
double v[N];
int n;
inline double dist(Point a, Point b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));}

double cal(Point a) {
	double ret = 0;
	for (int i = 0; i < n; i++) ret = max(dist(a, pos[i]) / v[i], ret);
	return ret;
}

const int P = 1111;
const double K = 0.8;
double rd() { return (rand() % P) * 1.0 / P;}

void saa(Point &a) {
	Point na;
	double d = cal(a), nd, r = 100000;
	while (r > 1e-5) {
		bool ok = 1;
		for (int i = 0; i < 10; i++) {
			double t = rd() * 2 * PI;
			na = Point(a.x + r * cos(t), a.y + r * sin(t));
			nd = cal(na);
			if (nd < d) d = nd, a = na, ok = 0;
		}
		if (ok) r = r * K;
	}
}

int main() {
	int _;
	scanf("%d", &_);
	srand(time(0));
	while (_--) {
		scanf("%d", &n);
		double sx = 0, sy = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lf%lf%lf", &pos[i].x, &pos[i].y, v + i);
			sx += pos[i].x, sy += pos[i].y;
		}
		double ans = FINF;
		int T = 33;
		while (T--) {
			Point tmp(sx, sy);
			saa(tmp);
			ans = min(ans, cal(tmp));
		}
		printf("%.6f\n", ans);
	}
	return 0;
}



