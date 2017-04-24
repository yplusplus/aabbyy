#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<double, double> Point;
#define x first
#define y second
template <class T> T sqr(T x) { return x * x;}
const double EPS = 1e-8;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
const double g = 9.8;

void fly(Point &p, Point &v, double t) {
	double dx = v.x * t;
	double dy = v.y * t - g * sqr(t) / 2;
	p = Point(p.x + dx, p.y + dy);
	v = Point(v.x, v.y - g * t);
}

double fly_time(Point p, Point v) {
	double a = g, b = - 2 * v.y, c = - 2 * p.y;
	return (sqrt(sqr(b) - 4 * a * c) - b) / (2 * a);
}

double fly(Point p, Point v) {
	double t = fly_time(p, v);
	return p.x + v.x * t;
}

int main() {
	//freopen("in", "r", stdin);
	double H, t, V1, V2, V3;
	Point V;
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(3);
	char op[11];
	while (cin >> H >> op) {
		if (*op == 'R') {
			cin >> V.x >> V.y;
			cout << fly(Point(0.0, H), V) << endl;
		} else if (*op == 'B') {
			cin >> V.x >> V.y >> t >> V1 >> V2 >> V3;
			double ft = fly_time(Point(0.0, H), V);
			if (sgn(ft - t) <= 0) cout << fly(Point(0.0, H), V) << endl;
			else {
				Point c(0.0, H);
				fly(c, V, t);
				cout << fly(c, Point(V1, V.y)) << ' ' << fly(c, Point(V2, V.y)) << ' ' << fly(c, Point(V3, V.y)) << endl;
			}
		} else {
			cin >> V.x >> V.y >> t;
			double ft = fly_time(Point(0.0, H), V);
			if (sgn(ft - t) <= 0) cout << fly(Point(0.0, H), V) << endl;
			else {
				Point c(0.0, H);
				fly(c, V, t);
				V = Point(V.x * 2, V.y * 2);
				cout << fly(c, V) << endl;
			}
		}
	}
	return 0;
}





