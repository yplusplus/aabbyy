#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

typedef pair<double, double> Point;
typedef pair<bool, Point> Node;
#define x first
#define y second

Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline double dist(Point a, Point b) { return sqrt(dot(a - b, a - b));}

const int N = 111111;
const double FINF = 1e100;
const double EPS = 1e-10;
Node pt[N], tmp[N];
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}

inline bool cmpy(Node a, Node b) { return sgn(a.y.y - b.y.y) < 0 || sgn(a.y.y - b.y.y) == 0 && sgn(a.y.x - b.y.x) < 0 || sgn(a.y.x - b.y.x) == 0 && sgn(a.y.y - b.y.y) == 0 && a.x < b.x;}
inline bool cmpx(Node a, Node b) { return a.y.x < b.y.x;}

#define lson l, m
#define rson m + 1, r
double nnp(int l, int r) {
	//cout << l << ' ' << r << endl;
	if (r - l < 3) {
		double ret = FINF;
		for (int i = l; i < r; i++) {
			for (int j = i + 1; j <= r; j++) if (pt[i].x ^ pt[j].x) ret = min(ret, dist(pt[i].y, pt[j].y));
		}
		//cout << ret << endl;
		return ret;
	}
	int m = l + r >> 1;
	Point mp = pt[m].y;
	double md = min(nnp(lson), nnp(rson));
	int tt = 0;
	for (int i = l; i <= r; i++) if (fabs(pt[i].y.x - mp.x) <= md) tmp[tt++] = pt[i];
	sort(tmp, tmp + tt, cmpy);
	for (int i = 0; i < tt; i++) {
		for (int j = i + 1; j < tt; j++) {
			if (dist(tmp[i].y, tmp[j].y) > md) break;
			if (tmp[i].x ^ tmp[j].x) md = min(md, dist(tmp[i].y, tmp[j].y));
		}
	}
	return md;
}

int main() {
	//freopen("in", "r", stdin);
	int n, a, b;
	while (~scanf("%d%d%d", &n, &a, &b)) {
		for (int i = 0; i < n; i++) scanf("%lf%lf", &pt[i].y.x, &pt[i].y.y), pt[i].x = 0;
		for (int i = 0; i < n; i++) scanf("%lf%lf", &pt[i + n].y.x, &pt[i + n].y.y), pt[i + n].x = 1;
		n <<= 1;
		sort(pt, pt + n, cmpx);
		printf("%.3f\n", nnp(0, n - 1) / ((double) a + b));
	}
	return 0;
}


