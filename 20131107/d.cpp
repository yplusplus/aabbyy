#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const DB EPS = 1e-8;
inline int sgn(const DB &x) { return (x > EPS) - (x < -EPS); }
struct Point {
	DB x, y;
	int id;
	Point() {}
	Point(DB x, DB y) : x(x), y(y) {}
} ;
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
bool get(Point &p) { return scanf("%lf%lf", &p.x, &p.y) != -1; }

int andrew(Point *pt, int n, Point *ch) {
	int m = 0;
	sort(pt, pt + n);
	for (int i = 0; i < n; i++) {
		while (m > 1 && sgn(cross(pt[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) m--;
		ch[m++] = pt[i];
	}
	int k = m;
	for (int i = n - 1; i >= 0; i--) {
		while (m > k && sgn(cross(pt[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) m--;
		ch[m++] = pt[i];
	}
	if (n > 1) m--;
	return m;
}

const int N = 2222;
Point pt[N], ch[N];
bool vis[N];

int main() {
	int n;
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) { get(pt[i]); pt[i].id = i; }
		for (int i = 0; i < n; i++) vis[i] = 0;
		int cnt = 0;
		while (1) {
			if (n < 3) break;
			cnt++;
			int c = andrew(pt, n, ch);
			for (int i = 0; i < c; i++) vis[ch[i].id] = 1;
			int nn = 0;
			for (int i = 0; i < n; i++) {
				if (vis[pt[i].id]) continue;
				pt[nn++] = pt[i];
			}
			n = nn;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
