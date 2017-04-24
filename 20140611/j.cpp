#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool onSeg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0; }

typedef vector<Line> Lines;
typedef vector<DB> Array;
typedef vector<Point> Points;
inline void getLine(const DB &x, const DB &h, const DB &b, Lines &lines) {
	lines.push_back(Line(Point(x - b / 2, 0), Point(x, h)));
	lines.push_back(Line(Point(x, h), Point(x + b / 2, 0)));
}

DB solve(const Lines &lines) {
	int n = lines.size();
	Array position;
	//Point ip = llint(lines[1], lines[2]); cout << ip.x << ' ' << ip.y << endl;
	for (int i = 0; i < n; ++i) {
		position.push_back(lines[i].s.x);
		position.push_back(lines[i].t.x);
		for (int j = i + 1; j < n; ++j) {
			if (sgn(cross(lines[i].vec(), lines[j].vec())) == 0) {
				continue;
			}
			Point ip = llint(lines[i], lines[j]);
			if (onSeg(ip, lines[i].s, lines[i].t) && onSeg(ip, lines[j].s, lines[j].t)) {
				position.push_back(ip.x);
			}
		}
	}
	Points tops;
	for (int i = 0; i < position.size(); ++i) {
		DB y = 0;
		Line line(Point(position[i], 0), Point(position[i], 1));
		for (int j = 0; j < n; ++j) {
			if (sgn(lines[j].s.x - position[i]) <= 0 && sgn(position[i] - lines[j].t.x) <= 0) {
				y = max(llint(lines[j], line).y, y);
			}
		}
		tops.push_back(Point(position[i], y));
	}
	sort(tops.begin(), tops.end());
	DB sum = 0;
	//for (int i = 0; i < tops.size(); ++i) { cout << tops[i].x << ' ' << tops[i].y << endl; }
	for (int i = 1; i < tops.size(); ++i) {
		if (sgn(tops[i - 1].y) == 0 && sgn(tops[i].y) == 0) continue;
		sum += veclen(tops[i - 1] - tops[i]);
	}
	//cout << sum << endl;
	return sum;
}

int run() {
	int n, cas = 0;
	while (cin >> n && n) {
		Lines lines;
		DB x, h, b;
		for (int i = 0; i < n; ++i) {
			cin >> x >> h >> b;
			getLine(x, h, b, lines);
		}
		cout << "Case " << ++cas << ": " << int(solve(lines) + 0.5) << endl << endl;
	}
	return 0;
}

int main() {
	//freopen("in_j", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
