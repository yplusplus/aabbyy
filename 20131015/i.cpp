#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB EPS = 1e-10;
inline int sgn(DB x) { return (x > EPS) - (x < -EPS);}
typedef pair<DB, DB> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p);}
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p);}
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p);}

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x;}
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y;}
inline DB veclen(const Point &a) { return sqrt(dot(a, a));}

Point pt[10];
bool scan(Point &a) { return cin >> a.x >> a.y;}
bool input() {
	for (int i = 0; i < 3; i++) if (!scan(pt[i])) return 0;
	return 1;
}

void fix() {
	DB a = 0;
	for (int i = 0; i < 3; i++) a += cross(pt[i], pt[i + 1]);
	if (a < 0) reverse(pt, pt + 3);
	for (int i = 0; i < 10; i++) pt[i] = pt[i % 3];
}

typedef pair<Point, Point> PDD;

void cal(DB a, DB b, DB c, DB &x, DB &y) {
	DB dt = b * b - 4 * a * c;
	if (sgn(dt) < 0) x = y = -1;
	else x = (- b - sqrt(dt)) / (2 * a), y = (- b + sqrt(dt)) / (2 * a);
}

bool cal(Point a, Point b, Point c, PDD &s) {
	DB x = veclen(a - b), y = veclen(c - b), z = veclen(a - c);
	DB x1, x2;
	cal(x * 2, -(x + y + z), y, x1, x2);
	if (0 <= sgn(x1) && sgn(x1 - 1.0) <= 0 && 0 <= sgn(1 / (2.0 * x1)) && sgn(1 / (2.0 * x1) - 1.0) <= 0) {
		s = PDD(b + (a - b) * x1, b + (c - b) / (x1 * 2));
		return 1;
	}
	if (0 <= sgn(x2) && sgn(x2 - 1.0) <= 0 && 0 <= sgn(1 / (2.0 * x2)) && sgn(1 / (2.0 * x2) - 1.0) <= 0) {
		s = PDD(b + (a - b) * x2, b + (c - b) / (x2 * 2));
		return 1;
	}
	return 0;
}

bool work() {
	fix();
	PDD tmp;
	for (int i = 0; i < 3; i++) {
		if (cal(pt[i], pt[i + 1], pt[i + 2], tmp)) {
			cout << "YES" << endl;
			cout << tmp.x.x << ' ' << tmp.x.y << endl;
			cout << tmp.y.x << ' ' << tmp.y.y << endl;
			return 1;
		}
	}
	return 0;
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(13);
	while (input()) if (!work()) cout << "NO" << endl;
	return 0;
}







