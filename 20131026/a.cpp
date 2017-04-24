#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

const DB EPS = 1e-6;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline void get(Point &p) { scanf("%lf%lf", &p.x, &p.y); }

DB get_x(const DB &y, const Point &s, const Point &t) {
	DB dy = t.y - s.y, dx = t.x - s.x;
	return (y - s.y) / dy * dx + s.x;
}

const int N = 111111;
const DB FINF = 1e100;
int n, m, q;
Point L[N], R[N], pt[N];
DB rx[N];

DB work() {
	DB ans = FINF;
	L[0] = Point(L[1].x, L[1].y - 1);
	R[0] = Point(R[1].x, R[1].y - 1);
	for (int i = 1, j = 1; i <= n; i++) {
		Point &cur = L[i];
		while (j < m && sgn(R[j].y - cur.y) < 0) j++;
		DB tx = get_x(cur.y, R[j - 1], R[j]);
		ans = min(fabs(tx - cur.x), ans);
	}
	for (int i = 1, j = 1; i <= m; i++) {
		Point &cur = R[i];
		while (j < n && sgn(L[j].y - cur.y) < 0) j++;
		DB tx = get_x(cur.y, L[j - 1], L[j]);
		ans = min(fabs(tx - cur.x), ans);
	}
	//cout << "Current Answer " << ans << endl;
	DB lb = L[1].y, ub = L[n].y;
	for (int i = 1, lj = 1, rj = 1; i <= q; ) {
		if (sgn(pt[i].y - lb) < 0) { i++; continue; }
		if (sgn(pt[i].y - ub) > 0) break;
		Point &cur = pt[i];
		int j = i;
		while (j <= q && sgn(pt[i].y - pt[j].y) == 0) {
			rx[j] = pt[j].x;
			j++;
		}
		//cout << "Processing " << i << " to " << j << endl;
		//sort(pt + i, pt + j);
		sort(rx + i, rx + j);
		while (lj < n && sgn(L[lj].y - cur.y) < 0) lj++;
		while (rj < m && sgn(R[rj].y - cur.y) < 0) rj++;
		//cout << "Lid " << lj << " Rid " << rj << endl;
		DB curL = get_x(cur.y, L[lj - 1], L[lj]);
		DB curR = get_x(cur.y, R[rj - 1], R[rj]);
		//cout << "L " << curL << " R " << curR << endl;
		DB last = curL, mx = 0;
		int t = i;
		//while (t < j && sgn(pt[t].x - curR) < 0) {
		while (t < j && sgn(rx[t] - curR) < 0) {
			if (sgn(curL - rx[t]) < 0) {
				//cout << last << "=>" << pt[t].x << endl;
				mx = max(rx[t] - last, mx);
				last = rx[t];
			}
			t++;
		}
		mx = max(curR - last, mx);
		ans = min(mx, ans);
		i = j;
	}
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) get(L[i]);
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) get(R[i]);
		scanf("%d", &q);
		for (int i = 1; i <= q; i++) get(pt[i]);
		printf("%.10f\n", work());
	}
	return 0;
}



