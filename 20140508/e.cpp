#include <bits/stdc++.h>
using namespace std;

typedef long double DB;
const DB EPS = 1e-11;
const DB PI = acos(-1.0);
const int N = 1 << 9;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
struct Point {
	DB x, y;
	int id;
	Point() {}
	Point(DB x, DB y) : x(x), y(y), id(-1) {}
} ;
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
bool operator < (const Point &a, const Point &b) {
	if (sgn(a.x - b.x)) return a.x < b.x;
	return a.y < b.y;
}

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return Point(c.x + cos(p) * r, c.y + sin(p) * r); }
} circle[N];
Point pt[N * N << 1], ch[N * N << 1];
int tt;

int andrew(int n) {
	sort(pt, pt + n);
	int m = 0;
	for (int i = 0; i < n; ++i) {
		while (m > 1 && sgn(cross(pt[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) --m;
		ch[m++] = pt[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; --i) {
		while (m > k && sgn(cross(pt[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) --m;
		ch[m++] = pt[i];
	}
	return m;
}

void getPoint(int i, int j) {
	DB dist = veclen(circle[i].c - circle[j].c);
	DB dir = angle(circle[j].c - circle[i].c);
	DB da = asin((circle[j].r - circle[i].r) / dist);
	pt[tt] = circle[i].point(dir + PI / 2 + da);
	pt[tt++].id = i;
	pt[tt] = circle[i].point(dir - PI / 2 - da);
	pt[tt++].id = i;
}

DB getArc(const Point &a, const Point &b, int id) {
	DB a1 = angle(a - circle[id].c);
	DB a2 = angle(b - circle[id].c);
	if (sgn(a2 - a1) < 0) a2 += PI * 2;
	return circle[id].r * (a2 - a1);
}

double solve(int n) {
	if (n == 1) return 2 * PI * circle[0].r;
	DB sum = 0;
	tt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			getPoint(i, j);
		}
	}
	//for (int i = 0; i < tt; ++i) cout << pt[i].x << ' ' << pt[i].y << ' ' << pt[i].id << endl;
	int m = andrew(tt);
	ch[m] = ch[0];
	for (int i = 0; i < m; ++i) {
		//cout << ch[i].x << ' ' << ch[i].y << ' ' << ch[i].id << endl;
		if (ch[i].id == ch[i + 1].id) {
			sum += getArc(ch[i], ch[i + 1], ch[i].id);
		} else {
			sum += veclen(ch[i] - ch[i + 1]);
		}
	}
	return double(sum);
}

int run() {
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			cin >> circle[i].c.x >> circle[i].c.y >> circle[i].r;
		}
		cout << solve(n) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(20);
	freopen("murder.in", "r", stdin);
	freopen("murder.out", "w", stdout);
	return run();
}
