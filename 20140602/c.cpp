#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-10;
const DB PI = acos(-1.0);

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
inline DB fix(const DB &a) { return a >= 0 ? a : a + PI; }
inline DB angle(const Point &a) { return fix(atan2(a.y, a.x)); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }

vector<Point> star;
inline bool check(const Point &a) {
	for (int i = 0; i < star.size(); ++i) { // check coincident
		if (star[i] == a) {
			return 0;
		}
	}
	vector<DB> direction(star.size());
	for (int i = 0; i < star.size(); ++i) {
		direction[i] = angle(star[i] - a);
	}
	sort(direction.begin(), direction.end());
	for (int i = 0; i < direction.size(); ++i, ++i) {
		if (i) {
			if (sgn(direction[i - 1] - direction[i]) == 0) {
				return 0;
			}
		}
		if (sgn(direction[i] - direction[i + 1]) != 0) {
			return 0;
		}
	}
	return 1;
}

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

int run() {
	int n;
	while (cin >> n) {
		int m = n << 1;
		star.resize(m);
		for (int i = 0; i < m; ++i) {
			cin >> star[i].x >> star[i].y;
		}
		vector<Point> candidates;
		// enumerate Pair(0, i) && Pair(1, j)
		for (int i = 2; i < m; ++i) {
			for (int j = 2; j < m; ++j) {
				if (i == j) continue;
				if (sgn(cross(star[0] - star[i], star[1] - star[j])) == 0) continue;
				Point temp = llint(Line(star[0], star[i]), Line(star[1], star[j]));
				if (check(temp)) {
					candidates.push_back(temp);
				}
			}
		}
		// enumerate Pair(0, 1) && Pair(i, j)
		for (int i = 2; i < m; ++i) {
			for (int j = 2; j < m; ++j) {
				if (i == j) continue;
				if (sgn(cross(star[0] - star[1], star[i] - star[j])) == 0) continue;
				Point temp = llint(Line(star[0], star[1]), Line(star[i], star[j]));
				if (check(temp)) {
					candidates.push_back(temp);
				}
			}
		}
		sort(candidates.begin(), candidates.end());
		candidates.resize(unique(candidates.begin(), candidates.end()) - candidates.begin());
		if (candidates.size() == 1) {
			cout << "Center of the universe found at (" << candidates[0].x << ", " << candidates[0].y << ")" << endl;
		} else if (candidates.size() == 0) {
			cout << "Impossible" << endl;
		} else {
			cout << "Ambiguity" << endl;
		}
	}
	return 0;
}

int main() {
	freopen("center.in", "r", stdin);
	freopen("center.out", "w", stdout);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
