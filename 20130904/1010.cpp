#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 22222;
const double FINF = 1e100;
typedef pair<double, double> Point;
#define x first
#define y second
template<class T> T sqr(T x) { return x * x;}
Point pt[N], tmp[N];
inline bool cmp(Point a, Point b) { return a.y < b.y;}
inline double dist(Point a, Point b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));}

double nnp(int l, int r) {
	if (r - l <= 1) return FINF;
	if (r - l <= 3) {
		double ret = FINF;
		for (int i = l; i <= r; i++) {
			for (int j = i + 1; j <= r; j++) {
				for (int k = j + 1; k <= r; k++) {
					ret = min(ret, dist(pt[i], pt[j]) + dist(pt[j], pt[k]) + dist(pt[k], pt[i]));
				}
			}
		}
		//cout << l << ' ' << r << ' ' << ret << endl;
		return ret;
	}
	int tt = 0, m = l + r >> 1;
	Point mid = pt[m];
	double mn = min(nnp(l, m - 1), nnp(m + 1, r));
	for (int i = l; i <= r; i++) {
		if (fabs(mid.x - pt[i].x) <= mn / 2) tmp[tt++] = pt[i];
	}
	sort(tmp, tmp + tt, cmp);
	for (int i = 0; i < tt; i++) {
		int j = i + 1;
		while (j < tt && fabs(tmp[i].y - tmp[j].y) <= mn / 2) j++;
		for (int a = i; a < j; a++) {
			for (int b = a + 1; b < j; b++) {
				for (int c = b + 1; c < j; c++) {
					mn = min(mn, dist(tmp[a], tmp[b]) + dist(tmp[a], tmp[c]) + dist(tmp[b], tmp[c]));
				}
			}
		}
	}
	return mn;
}

int main() {
	//freopen("in", "r", stdin);
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%lf%lf", &pt[i].x, &pt[i].y);
		sort(pt, pt + n);
		printf("%.3f\n", nnp(0, n - 1));
	}
	return 0;
}
