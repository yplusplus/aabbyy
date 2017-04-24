#include <climits>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
inline Point rotate(const Point &a, const DB &x) { return Point(a.x * cos(x) - a.y * sin(x), a.x * sin(x) + a.y * cos(x)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
const DB EPS = 1e-10;
const DB FINF = 1e10;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }

int andwer(Point *const pt, int n, Point *const ch) {
	int m = 0;
	sort(pt, pt + n);
	for (int i = 0; i < n; ++i) {
		while (m > 1 && sgn(cross(pt[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) --m;
		ch[m] = pt[i];
		++m;
	}
	int k = m;
	for (int i = n - 2; i >= 0; --i) {
		while (m > k && sgn(cross(pt[i] - ch[m - 2], ch[m - 1] - ch[m - 2])) >= 0) --m;
		ch[m] = pt[i];
		++m;
	}
	return m - 1;
}

const int N = 11234;
Point pt[N], ch[N];
int n, m;
inline int mNext(int x) { return x == m - 1 ? 0 : x + 1; }
inline int mLast(int x) { return x == 0 ? m - 1 : x - 1; }
inline DB dist(const Point &a, const Point &b, const Point &c) { return fabs(cross(b - a, c - a) / veclen(b - c)); }

int run() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &pt[i].x, &pt[i].y);
		}
		m = andwer(pt, n, ch);
		//for (int i = 0; i < m; ++i) { cout << ch[i].x << ' ' << ch[i].y << endl; }
		DB answer = FINF;
		int U, L, R;
		int NU, NL, NR;
		U = R = 1;
		L = 0;
		while (1) {
			NU = mNext(U);
			if (dist(ch[NU], ch[0], ch[1]) > dist(ch[U], ch[0], ch[1])) U = NU;
			else break;
		}
		Point t1, t2;
		DB ang = angle(ch[1] - ch[0]);
		while (1) {
			NL = mLast(L);
			t1 = rotate(ch[L], -ang);
			t2 = rotate(ch[NL], -ang);
			if (t1.x > t2.x) L = NL;
			else break;
		}
		while (1) {
			NR = mNext(R);
			t1 = rotate(ch[R], -ang);
			t2 = rotate(ch[NR], -ang);
			if (t1.x < t2.x) R = NR;
			else break;
		}
		for (int i = 0; i < m; ++i) {
			int l = i, r = mNext(i);
			while (1) {
				NU = mNext(U);
				if (dist(ch[NU], ch[l], ch[r]) > dist(ch[U], ch[l], ch[r])) U = NU;
				else break;
			}
			Point t1, t2;
			DB ang = angle(ch[r] - ch[l]);
			DB minx = rotate(ch[L], -ang).x, maxx = rotate(ch[R], -ang).x;
			while (1) {
				NL = mNext(L);
				t1 = rotate(ch[L], -ang);
				t2 = rotate(ch[NL], -ang);
				if (t1.x > t2.x) L = NL, minx = t2.x;
				else break;
			}
			while (1) {
				NR = mNext(R);
				t1 = rotate(ch[R], -ang);
				t2 = rotate(ch[NR], -ang);
				if (t1.x < t2.x) R = NR, maxx = t2.x;
				else break;
			}
			//cout << U << ' ' << L << ' ' << R << endl;
			answer = min((maxx - minx + dist(ch[U], ch[l], ch[r])) * 2, answer);
		}
		printf("%.6f\n", answer);
	}
	return 0;
}

int main() {
	//ios::sync_with_stdio(0);
	return run();
}
