#include <bits/stdc++.h>
using namespace std;

typedef long double DB;
typedef pair<DB, DB> Point;
typedef vector<Point> Points;
#define x first
#define y second
const DB EPS = 1e-8;
const DB PI = acos(-1.0);
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
istream &operator >> (istream &in, Point &a) { return in >> a.x >> a.y; }
ostream &operator << (ostream &out, const Point &a) { return out << a.x << ' ' << a.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }

struct Line {
	Point s, t;
	DB ang;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
	DB getAngle() { return ang = angle(vec()); }
} ;
ostream &operator << (ostream &out, const Line &a) { return out << a.s << ' ' << a.t; }
typedef vector<Line> Lines;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }
bool operator < (const Line &a, const Line &b) {
	if (a.s == b.s) {
		return a.t < b.t;
	}
	return a.s < b.s;
}
bool operator == (const Line &a, const Line &b) { return a.s == b.s && a.t == b.t; }

inline bool onLeft(const Line &l, const Point &p) { return cross(l.vec(), p - l.s) > 0; }
inline bool cmp(const Line &a, const Line &b) { return a.ang < b.ang; }
struct HalfPlane {
	static Lines L;
	static Points result;
	static void clear() { L.clear(); }
	static void push_back(const Line &l) { L.push_back(l); }
	static Points run() {
		//cerr << "Half Plane" << endl; for (int i = 0; i < L.size(); ++i) { cerr << L[i].s << ' ' << L[i].t << endl; }
		for (int i = 0; i < L.size(); ++i) {
			L[i].getAngle();
		}
		result.clear();
		sort(L.begin(), L.end(), cmp);
		int fi, la;
		Points p(L.size());
		Lines q(L.size());
		q[fi = la = 0] = L[0];
		for (int i = 1; i < L.size(); ++i) {
			while (fi < la && !onLeft(L[i], p[la - 1])) --la;
			while (fi < la && !onLeft(L[i], p[fi])) ++fi;
			q[++la] = L[i];
			if (sgn(cross(q[la].vec(), q[la - 1].vec())) == 0) {
				--la;
				if (onLeft(q[la], L[i].s)) {
					q[la] = L[i];
				}
			}
			if (fi < la) {
				p[la - 1] = llint(q[la - 1], q[la]);
			}
		}
		while (fi < la && !onLeft(q[fi], p[la - 1])) --la;
		if (fi + 1 >= la) return result;
		p[la] = llint(q[la], q[fi]);
		for (int i = fi; i <= la; ++i) {
			result.push_back(p[i]);
		}
		return result;
	}
} ;

inline void fix(Points &pt) {
	DB sum = cross(pt[pt.size() - 1], pt[0]);
	for (int i = 1; i < pt.size(); ++i) {
		sum += cross(pt[i - 1], pt[i]);
	}
	if (sum < 0) {
		reverse(pt.begin(), pt.end());
	}
}

Lines HalfPlane::L;
Points HalfPlane::result;
Lines edge;

Line convert(const Line &a, const Line &b) {
	if (sgn(cross(a.vec(), b.vec())) == 0) {
		Point m = (a.s + b.s) / 2;
		return Line(m, m + b.vec());
	}
	Line ra = a;
	swap(ra.s, ra.t);
	//cerr << ra.s << ' ' << ra.t << ' ' << b.s << ' ' << b.t << endl; cerr << a1 << ' ' << a2 << endl;
	Point ip = llint(ra, b);
	Point ep = (ra.vec() / veclen(ra.vec()) + b.vec() / veclen(b.vec())) * 10 + ip;
	return Line(ip, ep);
}

void find(const Points &pt) {
	Lines side(pt.size());
	side[0] = Line(pt[pt.size() - 1], pt[0]);
	for (int i = 1; i < pt.size(); ++i) {
		side[i] = Line(pt[i - 1], pt[i]);
	}
	for (int i = 0; i < side.size(); ++i) {
		HalfPlane::clear();
		HalfPlane::push_back(side[i]);
		for (int j = 0; j < side.size(); ++j) {
			if (i == j) {
				continue;
			}
			HalfPlane::push_back(convert(side[i], side[j]));
		}
		//cerr << HalfPlane::L.size() << endl;
		HalfPlane::run();
		int n = HalfPlane::result.size();
		for (int i = 1; i < n; ++i) {
			edge.push_back(Line(HalfPlane::result[i - 1], HalfPlane::result[i]));
		}
		//cerr << "Points" << endl; for (int i = 0; i < n; ++i) { cerr << HalfPlane::result[i] << endl; } cerr << endl;
		edge.push_back(Line(HalfPlane::result[n - 1], HalfPlane::result[0]));
	}
}

int run() {
	int n;
	while (cin >> n) {
		Points pt(n);
		for (int i = 0; i < n; ++i) {
			cin >> pt[i];
		}
		fix(pt);
		edge.clear();
		DB answer = -veclen(pt[0] - pt[pt.size() - 1]);
		for (int i = 1; i < n; ++i) {
			answer -= veclen(pt[i] - pt[i - 1]);
		}
		find(pt);
		/*
		for (int i = 0; i < edge.size(); ++i) {
			if (edge[i].s < edge[i].t) continue;
			swap(edge[i].s, edge[i].t);
		}
		sort(edge.begin(), edge.end());
		edge.resize(unique(edge.begin(), edge.end()) - edge.begin());
		*/
		for (int i = 0; i < edge.size(); ++i) {
			//cerr << "Edge" << i << ' ' << edge[i] << endl;
			answer += veclen(edge[i].vec());
		}
		cout << double(answer / 2) << endl;
	}
	return 0;
}

int main() {
	freopen("roof.in", "r", stdin);
	freopen("roof.out", "w", stdout);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(20);
	return run();
}
