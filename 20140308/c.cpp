#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
typedef vector<Point> VP;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
void operator >> (istream &in, Point &p) { in >> p.x >> p.y; }

typedef pair<Point, DB> Node;
typedef vector<Node> VN;

Point merge(const VN &node) {
	Point sum(0, 0);
	DB sum_area = 0;
	for (int i = 0, sz = node.size(); i < sz; ++i) {
		sum = sum + node[i].x * node[i].y;
		sum_area += node[i].y;
	}
	return sum / sum_area;
}

Node get_gravity(VP &pt) {
	Node sum(Point(0, 0), 0);
	int n = pt.size();
	pt.push_back(pt[0]);
	for (int i = 0; i < n; ++i) {
		DB a = cross(pt[i], pt[i + 1]);
		sum.x = sum.x + (pt[i] + pt[i + 1]) * a;
		sum.y += cross(pt[i], pt[i + 1]);
	}
	sum.x = sum.x / (3 * sum.y);
	pt.pop_back();
	return sum;
}

inline DB fix(const DB &x) { return fabs(x) < 1e-10 ? 0 : x; }

int run() {
	int _, n, k;
	cin >> _;
	while (_--) {
		cin >> n;
		VN rec(n);
		for (int i = 0; i < n; ++i) {
			cin >> k;
			VP pt(k);
			for (int j = 0; j < k; ++j) cin >> pt[j];
			reverse(pt.begin(), pt.end());
			rec[i] = get_gravity(pt);
		}
		Point ans = merge(rec);
		cout << fix(ans.x) << ' ' << fix(ans.y) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(4);
	return run();
}
