#include <bits/stdc++.h>
using namespace std;

typedef long double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
istream &operator >> (istream &in, Point &a) { return in >> a.x >> a.y; }
ostream &operator << (ostream &out, const Point &a) { return out << (double) a.x << ' ' << (double) a.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }
inline Point vecunit(const Point &a) { return a / veclen(a); }

const DB EPS = 1e-10;
const DB BOUND = 1e6;
inline int sgn(const DB &a, const DB &eps = EPS) { return (a > eps) - (a < -eps); }

struct Line {
	Point s, t;
	DB ang;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) { ang = angle(t - s); }
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
	bool operator < (const Line &a) const { return ang < a.ang; }
	DB getAngle() { return ang = angle(t - s); }
	Line move(DB d = -1e-8) {
		Point v = normal(vec()) * d;
		return Line(s + v, t + v);
	}
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }

inline bool onLeft(const Line &L, const Point &p) { return cross(L.vec(), p - L.s) > 0; }
int halfPlane(Line *const L, int n, Point *const pt) {
	for (int i = 0; i < n; ++i) {
		L[i].getAngle();
	}
	sort(L, L + n);
	//cerr << "~~~~~~~~~~~~~~~~~" << endl; for (int i = 0; i < n; ++i) { cerr << L[i].s << ' ' << L[i].t << endl; }
	int fi, la;
	Point *p = new Point[n];
	Line *q = new Line[n];
	q[fi = la = 0] = L[0];
	for (int i = 1; i < n; ++i) {
		while (fi < la && !onLeft(L[i], p[la - 1])) --la;
		while (fi < la && !onLeft(L[i], p[fi])) ++fi;
		q[++la] = L[i];
		if (sgn(cross(q[la].vec(), q[la - 1].vec())) == 0) {
			--la;
			if (onLeft(q[la], L[i].s)) q[la] = L[i];
		}
		if (fi < la) {
			p[la - 1] = llint(q[la - 1], q[la]);
		}
	}
	while (fi < la && !onLeft(q[fi], p[la - 1])) --la;
	if (la - fi <= 1) return 0;
	p[la] = llint(q[la], q[fi]);
	int m = 0;
	for (int i = fi; i <= la; ++i) {
		pt[m++] = p[i];
	}
	return m;
}

vector<Point> black, white;
const int dx[4] = { 1, 1, -1, -1 };
const int dy[4] = { -1, 1, 1, -1 };

Line getMid(const Point &in, const Point &out) {
	//cerr << "getMid " << in << ' ' << out << endl;
	Point M = (in + out) / 2;
	//cerr << M << endl;
	Point v = normal(out - in);
	return Line(M, M + v);
}

DB getRadius(const Point &a, const vector<Point> &pt) {
	int n = pt.size();
	DB r = 0;
	for (int i = 0; i < n; ++i) {
		r = max(r, veclen(pt[i] - a));
	}
	return r;
}

bool checkIn(const Point &c, const DB &r, const vector<Point> &pt) {
	for (int i = 0; i < pt.size(); ++i) {
		if (sgn(veclen(pt[i] - c) - r, 1e-8) > 0) return 0;
	}
	return 1;
}

bool checkOut(const Point &c, const DB &r, const vector<Point> &pt) {
	for (int i = 0; i < pt.size(); ++i) {
		if (sgn(veclen(pt[i] - c) - r, 1e-8) < 0) return 0;
	}
	return 1;
}

inline bool check(const Point &c, const DB &r, const vector<Point> &a, const vector<Point> &b) { return checkIn(c, r, a) && checkOut(c, r, b) || checkOut(c, r, a) && checkIn(c, r, b); }

bool test(const vector<Point> &in, const vector<Point> &out, Point &answer) {
	int n = in.size() * out.size() + 4;
	Line *line = new Line[n];
	Point *pt = new Point[n];
	int tt = 0;
	for (int i = 0; i < 4; ++i) {
		line[tt++] = Line(Point(dx[i], dy[i]) * BOUND, Point(dx[i + 1 & 3], dy[i + 1 & 3]) * BOUND);
	}
	for (int i = 0; i < in.size(); ++i) {
		for (int j = 0; j < out.size(); ++j) {
			line[tt++] = getMid(in[i], out[j]).move();
		}
	}
	int m = halfPlane(line, n, pt);
	if (m == 0) return 0;
	answer = Point(0, 0);
	for (int i = 0; i < m; ++i) {
		if (check(pt[i], getRadius(pt[i], in), in, out)) {
			answer = pt[i];
			return 1;
		}
		answer = answer + pt[i];
	}
	//cerr << m << endl; for (int i = 0; i < m; ++i) cerr << pt[i] << endl;
	answer = answer / m;
	return check(answer, getRadius(answer, in), in, out);
}

void work() {
	Point answer;
	if (test(black, white, answer)) {
		double r = getRadius(answer, black);
		assert(check(answer, r, black, white));
		cout << "YES" << endl;
		cout << answer << ' ' << r << endl;
		return ;
	}
	if (test(white, black, answer)) {
		double r = getRadius(answer, white);
		assert(check(answer, r, black, white));
		cout << "YES" << endl;
		cout << answer << ' ' << r << endl;
		return ;
	}
	cout << "NO" << endl;
	return ;
}

int run() {
	int n, m;
	while (cin >> n >> m) {
		black.resize(n);
		white.resize(m);
		for (int i = 0; i < n; ++i) {
			cin >> black[i];
		}
		for (int i = 0; i < m; ++i) {
			cin >> white[i];
		}
		work();
	}
	return 0;
}

int main() {
	freopen("wall.in", "r", stdin);
	freopen("wall.out", "w", stdout);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(20);
	return run();
}
