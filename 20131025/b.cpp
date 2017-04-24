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

const DB EPS = 1e-8;
const DB FINF = 1e20;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) {  return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB pt2line(const Point &p, const Point &a, const Point &b) { return cross(a - p, b - p) / veclen(a - b); }

const int N = 222;
DB dis[N];
Point pt[N];
int n, k;

DB cal(const Point &a, const Point &b) {
	for (int i = 0; i < n; i++) dis[i] = pt2line(pt[i], a, b);
	DB ret = FINF;
	sort(dis, dis + n);
	//for (int i = 0; i < n; i++) cout << i << ' ' << dis[i] << endl;
	for (int i = k - 1; i < n; i++) {
		ret = min(fabs(dis[i - k + 1] - dis[i]), ret);
	}
	return ret - 1.0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> n >> k) {
		for (int i = 0; i < n; i++) cin >> pt[i].x >> pt[i].y;
		if (n <= 2 || k <= 2) {
			cout << 0.0 << endl;
			continue;
		}
		DB ans = FINF, cur;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				//cout << i << "->" << j << endl;
				cur = cal(pt[i], pt[j]);
				ans = min(ans, cur);
			}
		}
		cout << max(ans, 0.0) << endl;
	}
	return 0;
}



