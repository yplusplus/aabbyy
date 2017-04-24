#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const int T = 222;
const DB EPS = 1e-12;
const DB PI = acos(-1.0);
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS);}

struct Point {
	DB x, y, z;
	Point() {}
	Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
	bool get() { return cin >> x >> y >> z;}
} ;
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z;}
inline DB veclen(const Point &a) { return sqrt(dot(a, a));}
inline DB angle(const Point &a, const Point &b) { return dot(a, b) / (veclen(a) * veclen(b));}

Point A, B;
DB R, D, V, rad;

inline DB cal_carrier(const DB &p) { return (rad - p) * R;}
inline DB cal_spaceship(const DB &p) { return veclen(Point(R + D - R * cos(p), R * sin(p), 0.0)) / V;}

DB dc2(DB l, DB r) {
	DB m;
	for (int i = 0; i < T; i++) {
		m = (l + r) / 2;
		DB a = cal_carrier(m), b = cal_spaceship(m);
		if (a > b) l = m;
		else r = m;
	}
	return m;
}

DB work() {
	DB t = acos(R / (R + D));
	DB ans, pos = dc2(0.0, min(rad, t));
	if (cal_carrier(pos) > cal_spaceship(pos) + EPS) {
		DB tm = cal_spaceship(pos);
		DB p = (rad - t) * R - tm;
		//cout << p << endl;
		ans = tm + p / (V + 1);
	} else ans = cal_spaceship(pos);
	return ans;
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (A.get()) {
		B.get();
		cin >> V;
		R = veclen(A);
		D = veclen(B) - R;
		if (sgn(angle(A, B) + 1.0) <= 0) rad = PI;
		else if (sgn(angle(A, B) - 1.0) >= 0) rad = 0;
		else rad = acos(angle(A, B));
		cout << work() << endl;
	}
	return 0;
}
