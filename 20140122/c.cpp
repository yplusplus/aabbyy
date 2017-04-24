#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-10;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator * (const DB &p, const Point &a) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline Point normal(const Point &a) { return Point(-a.y, a.x) / veclen(a); }

struct Line {
	Point s, t;
	DB ang;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	void get_ang() { ang = angle(t - s); }
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
	void move() {
		Point v = normal(vec()) * (-1e-6);
		s = s + v; t = t + v;
	}
	bool operator < (const Line &a) const { return ang < a.ang; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline bool onleft(const Line &a, const Point &p) { return cross(p - a.s, a.vec()) < 0; }

bool hp(Line *l, int n) {
	for (int i = 0; i < n; i++) l[i].move();
	for (int i = 0; i < n; i++) l[i].get_ang();
	sort(l, l + n);
	//for (int i = 0; i < n; i++) cout << l[i].s.x << ' ' << l[i].s.y << ' ' << l[i].t.x << ' ' << l[i].t.y << endl;
	int fi, la;
	Point *p = new Point[n];
	Line *q = new Line[n];
	q[fi = la = 0] = l[0];
	for (int i = 1; i < n; i++) {
		if (fi < la) {
			bool end = 1;
			for (int j = fi; j < la; j++) {
				if (onleft(l[i], p[j])) {
					end = 0;
					break;
				}
			}
			Point ip = llint(l[i], q[fi]);
			if (end && (sgn(cross(l[i].vec(), q[fi].vec())) == 0 || sgn(dot(ip - p[fi], q[fi].vec())) > 0)) return 0;
		}
		while (fi < la && !onleft(l[i], p[la - 1])) la--;
		while (fi < la && !onleft(l[i], p[fi])) fi++;
		q[++la] = l[i];
		if (sgn(cross(q[la].vec(), q[la - 1].vec())) == 0) {
			la--;
			if (onleft(q[la], l[i].s)) q[la] = l[i];
		}
		if (fi < la) p[la - 1] = llint(q[la - 1], q[la]);
	}
	while (fi < la && !onleft(q[fi], p[la - 1])) la--;
	//cout << fi << ' ' << la << endl;
	//for (int i = fi; i <= la; i++) cout << q[i].s.x << ' ' << q[i].s.y << ' ' << q[i].t.x << ' ' << q[i].t.y << endl;
	return fi < la;
}

Line make_line(int a, int b, int c) {
	Line l;
	assert(a || b);
	if (a) l.s = Point(-1.0 * c / a, 0.0);
	else l.s = Point(0.0, -1.0 * c / b);
	l.t = Point(l.s.x + b, l.s.y - a);
	return l;
}


const int N = 111;
const int M = 3;
const DB FINF = 1e5;
int A[N][M], n;
const DB px[4] = { -FINF, FINF, FINF, -FINF };
const DB py[4] = { -FINF, -FINF, FINF, FINF };
Line line[N];
bool check(int x) {
	bool ok;
	for (int a = 0; a < M; a++) {
		int b = (a + 1) % M, c = (a + 2) % M, tt;
		ok = 1; tt = 0;
		for (int i = 0; i < n; i++) {
			if (i == x) continue;
			if (A[i][a] - A[x][a] == 0 && A[i][b] - A[x][b] == 0) {
				if (A[i][c] - A[x][c] < 0) {
					ok = 0;
					break;
				} else continue;
			}
			line[tt++] = make_line(A[i][a] - A[x][a], A[i][b] - A[x][b], A[i][c] - A[x][c]);
		}
		for (int i = 0; i < 4; i++) line[tt++] = Line(Point(px[i], py[i]), Point(px[i + 1 & 3], py[i + 1 & 3]));
		if (ok && hp(line, tt)) return 1;
		ok = 1; tt = 0;
		for (int i = 0; i < n; i++) {
			if (i == x) continue;
			if (A[x][a] - A[i][a] == 0 && A[x][b] - A[i][b] == 0) {
				if (A[x][c] - A[i][c] < 0) {
					ok = 0;
					break;
				} else continue;
			}
			line[tt++] = make_line(A[x][a] - A[i][a], A[x][b] - A[i][b], A[x][c] - A[i][c]);
		}
		for (int i = 0; i < 4; i++) line[tt++] = Line(Point(px[i], py[i]), Point(px[i + 1 & 3], py[i + 1 & 3]));
		if (ok && hp(line, tt)) return 1;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(6);
	ios::sync_with_stdio(0);
	int _; cin >> _;
	while (_--) {
		cin >> n;
		for (int i = 0; i < n; i++) for (int j = 0; j < M; j++) cin >> A[i][j];
		for (int i = 0; i < n; i++) cout << (check(i) ? 'T' : 'F'); cout << endl;
	}
	return 0;
}
