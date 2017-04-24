#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const DB EPS = 1e-8;
const DB FINF = 1e10;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

struct Point {
	DB x, y, z;
	Point() {}
	Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
	void get() { cin >> x >> y >> z; }
} ;
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y, a.z + b.z); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y, a.z - b.z); }

inline Point cross(const Point &a, const Point &b) { return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
DB get_dist(const Point &p, const Point &a, const Point &b) {
	if (sgn(veclen(a - b)) == 0) return veclen(a - p);
	//if (sgn(dot(a - b, p - b)) <= 0) return veclen(b - p);
	if (sgn(dot(b - a, p - a)) <= 0) return veclen(a - p);
	return veclen(cross(a - p, b - p)) / veclen(a - b);
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	int n;
	while (cin >> n) {
		Point A, B, p;
		A.get();
		B.get();
		DB ans = 0;
		for (int i = 0; i < n; i++) {
			p.get();
			ans = max(get_dist(p, A, B), ans);
		}
		cout << ans << endl;
	}
	return 0;
}
