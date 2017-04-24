#include <bits/stdc++.h>
using namespace std;

typedef long double DB;
typedef pair<DB, DB> Point;
typedef vector<DB> VDB;
#define x first
#define y second
const DB EPS = 1e-8;
const DB PI = acos(-1.0);
const int N = 1 << 4;
const int K = 1 << 5;
const int T = 1 << 7;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
template<class T> inline T sqr(const T &a) { return a * a; }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline DB adjust(const DB &a) { return min(DB(1), max(DB(-1), a)); }
inline DB acos(const DB &a, const DB &b, const DB &c) { return acos(adjust((sqr(b) + sqr(c) - sqr(a)) / (2 * b * c))); }
inline void get(Point &a) { cin >> a.x >> a.y; }

struct Circle {
	Point c;
	DB r;
	Circle() {}
	Circle(Point c, DB r) : c(c), r(r) {}
	Point point(const DB &p) const { return Point(c.x + r * cos(p), c.y + r * sin(p)); }
	bool exin(const Point &p) { return sgn(veclen(p - c) - r) < 0; }
	bool exout(const Point &p) { return sgn(veclen(p - c) - r) > 0; }
	bool in(const Point &p) { return sgn(veclen(p - c) - r) <= 0; }
	bool on(const Point &p) { return sgn(veclen(p - c) - r) == 0; }
	bool out(const Point &p) { return sgn(veclen(p - c) - r) >= 0; }
} ;
int n;
DB d, D;
Point sheep[N];
inline DB fix(const DB &a) {
	if (a > PI) return a - PI * 2;
	if (a < -PI) return a + PI * 2;
	return a;
	//return fmod(a + PI * 3, PI * 2) - PI;
}

int ccint(const Circle &a, const Circle &b, DB *const sol) {
	DB sr = a.r + b.r;
	DB dr = fabs(a.r - b.r);
	DB dist = veclen(a.c - b.c);
	if (sgn(dist - dr) < 0 || sgn(dist - sr) > 0) return 0;
	if (sgn(dist - dr) == 0) {
		if (a.r > b.r) sol[0] = angle(b.c - a.c);
		else sol[0] = angle(a.c - b.c);
		sol[1] = sol[0];
		return 2;
	}
	if (sgn(dist - sr) == 0) {
		sol[0] = sol[1] = angle(b.c - a.c);
		return 2;
	}
	DB ang = angle(b.c - a.c);
	DB dt = acos(b.r, a.r, dist);
	sol[0] = fix(ang - dt);
	sol[1] = fix(ang + dt);
	//sol[0] = ang - dt;
	//sol[1] = ang + dt;
	return 2;
}

bool isValid(const Point &a) {
	for (int i = 0; i < n; ++i) {
		if (Circle(sheep[i], d).out(a) && Circle(sheep[i], D).in(a)) continue;
		return 0;
	}
	return 1;
}

DB getAngle(const Point &a) {
	VDB ang(n);
	for (int i = 0; i < n; ++i) ang[i] = angle(sheep[i] - a);
	sort(ang.begin(), ang.end());
	DB maxAngle = ang[0] + PI * 2 - ang[n - 1];
	for (int i = 1; i < n; ++i) maxAngle = max(ang[i] - ang[i - 1], maxAngle);
	return PI * 2 - maxAngle;
}

Circle circles[N << 1];
DB temp[T];

DB ts(DB L, DB R, Point &pt, const Circle &c) {
	DB M1, M2, D, S1, S2;
	for (int i = 0; i < T; ++i) {
		D = (R - L) / 3;
		M1 = L + D;
		M2 = R - D;
		S1 = getAngle(c.point(M1));
		S2 = getAngle(c.point(M2));
		if (S1 > S2) L = M1;
		else R = M2;
	}
	pt = c.point((L + R) / 2);
	return (S1 + S2) / 2;
}

bool gao(Point &a) {
	DB minAngle = FLT_MAX;
	for (int i = 0; i < n; ++i) {
		circles[i << 1] = Circle(sheep[i], d);
		circles[i << 1 | 1] = Circle(sheep[i], D);
	}
	int m = n << 1;
	for (int i = 0; i < m; ++i) {
		int tt = 2;
		temp[0] = -PI;
		temp[1] = PI;
		for (int j = 0; j < m; ++j) {
			if (i == j) continue;
			tt += ccint(circles[i], circles[j], temp + tt);
		}
		sort(temp, temp + tt);
		//cout << i << ':' << endl; for (int j = 0; j < tt; ++j) cout << temp[j] << ' '; cout << endl;
		for (int j = 1; j < tt; ++j) {
			Point M = circles[i].point((temp[j - 1] + temp[j]) / 2);
			if (isValid(M)) {
				DB dt = (temp[j] - temp[j - 1]) / K;
				for (int t = 0; t < K; ++t) {
					DB current = ts(temp[j - 1] + t * dt, temp[j - 1] + (t + 1) * dt, M, circles[i]);
					//cout << M.x << ' ' << M.y << ' ' << minAngle << ' ' << current << endl;
					if (minAngle > current) {
						minAngle = current;
						a = M;
					}
				}
			}
		}
	}
	return sgn(minAngle - PI) <= 0 && sgn(minAngle - FLT_MAX) != 0;
}
const Point TEST(4.9749371855331, 0.5);

int run() {
	while (cin >> n >> d >> D) {
		for (int i = 0; i < n; ++i) get(sheep[i]);
		//cout << isValid(TEST) << ' ' << getAngle(TEST) << endl;
		//cout << isValid(Point(999.9969999955, 0)) << ' ' << getAngle(Point(999.9969999955, 0)) << endl;
		Point answer;
		if (gao(answer)) {
			cout << double(answer.x) << ' ' << double(answer.y) << endl;
			assert(isValid(answer));
		} else cout << "impossible" << endl;
		//cout << isValid(answer) << ' ' << getAngle(answer) << endl;
	}
	return 0;
}

int main() {
	freopen("shepherd.in", "r", stdin);
	freopen("shepherd.out", "w", stdout);
	cout << setiosflags(ios::fixed) << setprecision(10);
	ios::sync_with_stdio(0);
	return run();
}

