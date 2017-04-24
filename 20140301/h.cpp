#include <bits/stdc++.h>
using namespace std;

const int N = 111;
typedef double DB;
typedef pair<DB, DB> Point;
const DB EPS = 1e-3;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
Point get_pt() { double x, y; scanf("%lf%lf", &x, &y); return Point(x, y); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} line[N];
int n;

inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool isparallel(const Line &a, const Line &b) { return sgn(cross(a.vec(), b.vec())) == 0; }
inline bool between(const Point &a, const Point &b, const Point &c) { return sgn(dot(c - a, c - b)) <= 0; }
bool in_seg(const Line &line, const Point &point) { return between(line.s, line.t, point); }

int calc(double x) { return x < 0 ? 0 : (int) (x / 50.0 + 1); }

int main() {
	int Case = 1;
	while (~scanf("%d", &n), n) {
		for (int i = 0; i < n; i++) {
			Point s = get_pt();
			Point t = get_pt();
			line[i] = Line(s, t);
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			vector<double> dis;
			for (int j = 0; j < n; j++) {
				if (i == j || isparallel(line[i], line[j])) continue;
				Point p = llint(line[i], line[j]);
				if (in_seg(line[i], p) && in_seg(line[j], p)) {
					dis.push_back(veclen(p - line[i].s));
				}
			}
			sort(dis.begin(), dis.end());
			if (dis.size() == 0) { ans += calc(veclen(line[i].vec())); }
			else {
				double t = veclen(line[i].vec());
				ans += calc(dis[0] - 25);
				ans += calc(t - dis.back() - 25);
				for (int i = 0; i < dis.size() - 1; i++) {
					ans += calc(dis[i + 1] - dis[i] - 50);
				}
			}
		}
		printf("Map %d\n", Case++);
		printf("Trees = %d\n", ans);
	}
	return 0;
}
