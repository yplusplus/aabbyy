#include <cmath>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef pair<DB, DB> Node;
typedef pair<int, int> PII;
const int N = 111111;
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
template<class T> inline T sqr(T x) { return x * x; }
#define x first
#define y second

struct Point {
	DB x, y, z;
	void get() { scanf("%lf%lf%lf", &x, &y, &z); }
} ;
DB R;
Node rec[N];

int tt;
bool convert(const Point &o, const Point &v) {
	DB a = sqr(v.x) + sqr(v.y) + sqr(v.z);
	DB b = 2 * (o.x * v.x + o.y * v.y + o.z * v.z);
	DB c = sqr(o.x) + sqr(o.y) + sqr(o.z) - sqr(R);
	DB dt = sqr(b) - 4 * a * c;
	if (sgn(dt) < 0) return 0;
	dt = sqrt(fabs(dt));
	rec[tt] = Node((- b + dt) / (2 * a), (- b - dt) / (2 * a));
	return sgn(rec[tt].x) >= 0;
}

int main() {
	int _, n;
	Point A, D;
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		scanf("%d%lf", &n, &R);
		tt = 0;
		for (int i = 1; i <= n; i++) {
			A.get(); D.get();
			if (convert(A, D)) tt++;
		}
		sort(rec, rec + tt);
		int c = 0;
		DB last = rec[0].y - 1;
		for (int i = 0; i < tt; i++) if (sgn(rec[i].y - last) > 0) c++, last = rec[i].x;
		printf("Case %d: %d %d\n", cas, tt, c);
	}
	return 0;
}
