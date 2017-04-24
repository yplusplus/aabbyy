#include <cmath>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB EPS = 1e-5;
const DB PI = acos(-1.0);
inline int sgn(DB x) { return (x > EPS) - (x < -EPS);}
typedef pair<DB, DB> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p);}
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p);}

inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y;}
inline DB veclen(const Point &a) { return sqrt(dot(a, a));}
inline DB angle(const Point &a) { return atan2(a.y, a.x);}
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a);}

void get_nx(Point &l, Point &r, const DB &v1, const DB &v2, const DB &t) {
	Point O;
	if (sgn(v1 - v2) == 0) {
		Point dir = normal(r - l);
		l = l + dir * v1 * t;
		r = r + dir * v2 * t;
		return ;
	}
	if (sgn(v1) * sgn(v2) < 0) {
		DB d = fabs(v1) / (fabs(v1) + fabs(v2));
		//cout << "opp" << ' ' << d << endl;
		O = l + (r - l) * d;
		DB c = angle(l - O);
		//cout << "current " << c << endl;
		c -= v1 * t / veclen(l - O);
		//cout << v1 << ' ' << t << endl;
		//cout << "diff " << v1 * t << ' ' << veclen(l - O) << endl;
		//cout << "new " << c << endl;
		l = O + Point(cos(c), sin(c)) * veclen(l - O);
		c += PI;
		r = O + Point(cos(c), sin(c)) * veclen(r - O);
	} else {
		O = r + (r - l) * v2 / (v1 - v2);
		//cout << O.x << ' ' << O.y << endl;
		DB c;
		//cout << veclen(r - O) << ' ' << veclen(l - O) << endl;
		//cout << c << endl;
		if (fabs(v1) > fabs(v2)) c = angle(l - O) - v1 * t / veclen(l - O);
		else c = angle(r - O) + v2 * t / veclen(r - O);
		//cout << c << endl;
		l = O + Point(cos(c), sin(c)) * veclen(l - O);
		r = O + Point(cos(c), sin(c)) * veclen(r - O);
	}
	
}

DB fix(DB x) { if (sgn(x) == 0) return 0.0; return x;}

int main() {
	//freopen("in", "r", stdin);
	int n, m;
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		Point L(-m, 0), R(m, 0);
		DB v1, v2, t;
		for (int i = 0; i < n; i++) {
			scanf("%lf%lf%lf", &v1, &v2, &t);
			v1 = v1 / 180 * PI;
			v2 = v2 / 180 * PI;
			//cout << L.x << ' ' << L.y << ' ' << R.x << ' ' << R.y << endl;
			get_nx(L, R, v1, v2, t);
			//cout << L.x << ' ' << L.y << ' ' << R.x << ' ' << R.y << endl;
		}
		Point M = (L + R) / 2;
		printf("%.6f\n%.6f\n", fix(M.x), fix(M.y));
	}
	return 0;
}

