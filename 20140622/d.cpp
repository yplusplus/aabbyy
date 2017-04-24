#include <bits/stdc++.h>
using namespace std;


typedef double DB;
typedef pair<DB, DB> Point;
typedef vector<Point> Points;
const DB PI = acos(-1.0);
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
istream &operator >> (istream &in, Point &a) { return in >> a.x >> a.y; }
ostream &operator << (ostream &out, const Point &a) { return out << a.x << ' ' << a.y; }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
Point center;
Points pt;

bool cmp(const Point &a, const Point &b) { return angle(a - center) < angle(b - center); }

int run() {
	int n;
	while (cin >> n) {
		cin >> center;
		if (n == 0 && fabs(center.x) < 1e-12 && fabs(center.y) < 1e-12) {
			break;
		}
		center.x /= 2;
		center.y /= 2;
		pt.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> pt[i];
		}
		sort(pt.begin(), pt.end(), cmp);
		pt.resize(n << 1);
		for (int i = 0; i < n; ++i) {
			pt[i + n] = pt[i];
		}
		int p = 0;
		while (1) {
			DB a1 = angle(pt[p] - center);
			DB a2 = angle(pt[p + (n >> 1) - 1] - center);
			DB a3 = angle(pt[p + (n >> 1)] - center);
			while (a2 < a1) a2 += PI * 2;
			while (a3 < a1) a3 += PI * 2;
			if (a2 - a1 <= PI && a3 - a1 >= PI) {
				break;
			}
			++p;
		}
		for (int i = 0; i < (n >> 1); ++i) {
			cout << pt[i + p] << endl;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
