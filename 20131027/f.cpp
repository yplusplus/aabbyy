#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-6;
const DB PI = acos(-1.0);
const DB K = 1e3;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a, const Point &b) { return acos(dot(a, b) / veclen(a) / veclen(b)); }
inline Point mid(const Point &a, const Point &b) { return (a + b) / 2; }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline void get(Point &a) {
	double x, y;
	cin >> x >> y;
	a = Point(x, y) * K;
}

int n;
const int N = 111;
Point pt[N];

bool check() {
	for (int i = 0; i < 2; i++) pt[i + n] = pt[i];
	DB ang = PI * (n - 2) / n;
	DB len = veclen(pt[0] - pt[1]);
	//cout << ang << endl;
	int dir = sgn(cross(pt[1] - pt[0], pt[2] - pt[0]));
	for (int i = 1; i <= n; i++) {
		if (sgn(veclen(pt[i - 1] - pt[i]) - len)) return 0;
		if (pt[i - 1] == pt[i]) return 0;
		DB tmp = angle(pt[i - 1] - pt[i], pt[i + 1] - pt[i]);
		if (sgn(tmp - ang)) return 0;
		if (dir != sgn(cross(pt[i] - pt[i - 1], pt[i + 1] - pt[i - 1]))) return 0;
	}
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	while (cin >> n) {
		for (int i = 0; i < n; i++) get(pt[i]);
		if (check()) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}




