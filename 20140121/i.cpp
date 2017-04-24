#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-8;
const DB PI = acos(-1.0);
const DB K = 0.75;
const DB FINF = 1e10;
const DB D = 1e3;
const int T = 111;
const int P = 1000;
const int C = 8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline DB torad(const DB &a) { return a * PI / 180; }
inline Point get_vec(const DB &a) { return Point(cos(a), sin(a)); }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

const int N = 3;
DB A[N], cl[N];
const Point station[3] = { Point(0.0, 0.0), Point(3.715, 1.761), Point(2.894, -2.115) };
inline Point rd_pt() { DB a = (rand() % P) * 2.0 * PI / P; return Point(cos(a), sin(a)); }
Point ans;
Line l[N];

template<class T> T sqr(T x) { return x * x; }
inline DB pt2line(const Point &p, const Line &l) { return fabs(cross(l.s - p, l.t - p) / veclen(l.vec())); } 
inline DB pt2line(const Point &p, int id) {
	DB r = torad(90 - A[id]);
	DB a = sin(r);
	DB b = - cos(r);
	DB c = - (a * station[id].x + b * station[id].y);
	return fabs(p.x * a + p.y * b + c);
}

DB cal(const Point &p) {
	DB sum = 0;
	for (int i = 0; i < N; i++) sum += sqr(pt2line(p, l[i])) * (cl[i] + 0.2);
	return sum * 100;
}

void SAA() {
	for (int i = 0; i < N; i++) {
		Point v = get_vec(torad(90 - A[i]));
		//cout << v.x << ' ' << v.y << endl;
		l[i] = Line(station[i], station[i] + v);
		//cout << l[i].s.x << ' ' << l[i].s.y << ' ' << l[i].t.x << ' ' << l[i].t.y << endl;
	}
	Point p(0.0, 0.0), np;
	DB s, ns, d = D;
	int c = 0;
	for (int i = 0; i < N; i++) {
		if (sgn(cross(l[i].vec(), l[(i + 1) % N].vec()))) {
			p = p + llint(l[i], l[(i + 1) % N]);
			c++;
		}
	}
	if (c) p = p / c;
	s = cal(p);
	//cout << p.x << ' ' << p.y << endl;
	while (d > EPS) {
		bool ok = 1;
		for (int i = 0; i < C; i++) {
			np = p + d * rd_pt();
			ns = cal(np);
			if (ns < s) {
				ok = 0;
				p = np;
				s = ns;
				break;
			}
		}
		if (ok) d *= K;
	}
	//cout << "ans " << cal(p) << endl;
	//cout << cal(Point(1.847, 1.877)) << endl;
	//cout << cal(Point(1.440, 1.511)) << endl;
	//cout << cal(Point(2.073, 2.021)) << endl;
	ans = p;
}

int main() {
	ios::sync_with_stdio(0);
	srand(time(0));
	cout << setiosflags(ios::fixed) << setprecision(3);
	//freopen("in", "r", stdin);
	int _, cas;
	cin >> _;
	while (_--) {
		cin >> cas;
		for (int i = 0; i < N; i++) cin >> A[i] >> cl[i];
		SAA();
		cout << cas << ' ' << ans.x << ' ' << ans.y << endl;
	}
	return 0;
}
