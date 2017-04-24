#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
struct Point {
	DB x, y, z;
	Point() {}
	Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
} pyramid[4], Lich;
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y, a.z - b.z); }

inline Point cross(const Point &a, const Point &b) { return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB area(const Point &a, const Point &b, const Point &c) { return veclen(cross(c - a, b - a)) / 2; }
inline DB volume(const Point &a, const Point &b, const Point &c, const Point &d) { return dot(cross(b - a, c - a), d - a) / 6; }

DB m, h, H, R;

DB cal(int x) {
	DB v = volume(pyramid[x], pyramid[x + 1 & 3], pyramid[x + 2 & 3], Lich);
	DB a = area(pyramid[x], pyramid[x + 1 & 3], pyramid[x + 2 & 3]);
	return fabs(v * 3 / a);
}

bool check() {
	for (int i = 0; i < 4; i++) {
		DB d = cal(i);
		if (sgn(d - R) <= 0) return 1;
	}
	return 0;
}

int main() {
	while (cin >> m >> h >> H) {
		cin >> Lich.x >> Lich.y;
		for (int i = 0; i < 4; i++) cin >> pyramid[i].x >> pyramid[i].y;
		for (int i = 0; i < 4; i++) pyramid[i].z = 0;
		pyramid[3].z = H;
		if (sgn(m - h) < 0) {
			cout << "NO" << endl;
			continue;
		}
		R = m - h;
		Lich.z = h;
		if (check()) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
