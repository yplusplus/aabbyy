#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }

template<class T> inline T sqr(T x) { return x * x; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB dist(const Point &p, const Point &a, const Point &b) { return fabs(cross(a - p, b - p) / sqrt(dot(a - b, a - b))); }

const int N = 222;
const int T = 24 * 60;
const DB PI = acos(-1.0);
const DB PI2 = PI * 2;
const Point O(0.0, 0.0);
struct Circle {
	Point c;
	DB r;
	void get() { cin >> c.x >> c.y >> r; }
} cir[N];

DB cal(DB rad, int n) {
	DB sum = 0;
	for (int i = 0; i < n; i++) {
		Point V(cos(rad), sin(rad));
		if (dot(V, cir[i].c) < 0) continue;
		DB d = dist(cir[i].c, O, V), r = cir[i].r;
		if (d > r) continue;
		sum += 2 * sqrt(sqr(r) - sqr(d));
	}
	return sum;
}

int main() {
	int n;
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(5);
	while (cin >> n && n) {
		for (int i = 0; i < n; i++) cir[i].get();
		DB ans = 0;
		for (int i = 0; i < T; i++) ans = max(cal(PI2 * i / T, n), ans);
		cout << ans << endl;
	}
	return 0;
}
