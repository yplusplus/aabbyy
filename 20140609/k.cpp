#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-10;
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

void andwer(vector<Point> &pt, vector<Point> &ch) {
	int n = pt.size(), m = 0;
	sort(pt.begin(), pt.end());
	ch.clear();
	for (int i = 0; i < n; ++i) {
		while (m > 1 && cross(ch[m - 1] - ch[m - 2], pt[i] - ch[m - 2]) <= 0) ch.pop_back(), --m;
		ch.push_back(pt[i]);
		++m;
	}
	int k = m;
	for (int i = n - 2; i >= 0; --i) {
		while (m > k && cross(ch[m - 1] - ch[m - 2], pt[i] - ch[m - 2]) <= 0) ch.pop_back(), --m;
		ch.push_back(pt[i]);
		++m;
	}
}

inline int toNext(int x, int m) { ++x; return x >= m ? 0 : x; }
DB pt2line(const Point &p, const Point &a, const Point &b) { return fabs(cross(a - p, b - p) / veclen(a - b)); }

void find(const Point &a, const Point &b, const vector<Point> &pt, int &id) {
	while (1) {
		int nx = toNext(id, pt.size());
		if (sgn(pt2line(pt[id], a, b) - pt2line(pt[nx], a, b)) > 0) break;
		id = nx;
	}
}

int run() {
	int n, cas = 0;
	while (cin >> n && n) {
		vector<Point> pt(n);
		for (int i = 0; i < n; ++i) {
			cin >> pt[i].x >> pt[i].y;
		}
		vector<Point> ch;
		andwer(pt, ch);
		int current = 0;
		DB answer = DBL_MAX;
		for (int i = 0; i < ch.size() - 1; ++i) {
			//cout << ch[i].x << ' ' << ch[i].y << ' ' << ch[i + 1].x << ' ' << ch[i + 1].y << endl;
			find(ch[i], ch[i + 1], ch, current);
			//cout << "Far " << ch[current].x << ' ' << ch[current].y << ' ' << pt2line(pt[current], ch[i], ch[i + 1]) << endl;
			answer = min(answer, pt2line(ch[current], ch[i], ch[i + 1]));
		}
		cout << "Case " << ++cas << ": " << answer << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(6);
	return run();
}
