#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB PI = acos(-1.0);
const DB EPS = 1e-10;
const int N = 1 << 6;
const int M = 1 << 12;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
bool operator < (const Point &a, const Point &b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y; }
template <class T> inline T sqr(const T &x) { return x * x; }

inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * a.x + a.y * b.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }

struct Circle {
	Point p;
	DB r;
	Circle() {}
	Circle(Point p, DB r) : p(p), r(r) {}
	Point point(const DB &a) const { return Point(p.x + r * cos(a), p.y + r * sin(a)); }
	void get() { cin >> p.x >> p.y >> r; }
} cir[N];

struct Node {
	Point p;
	int id;
	Node() {}
	Node(Point p, int id) : p(p), id(id) {}
} ;
bool operator < (const Node &a, const Node &b) { return a.p < b.p; }
Node keyPoints[M], ch[M];
int cntKeyPoints;

void getPoint(const int &a, const int &b) {
	if (a == b) return ;
	Circle &ca = cir[a], &cb = cir[b];
	DB dist = veclen(ca.p - cb.p), dr = fabs(ca.r - cb.r), da = asin(min(dr / dist, 1.0));
	DB ang = angle(cb.p - ca.p);
	if (ca.r > cb.r) {
		keyPoints[cntKeyPoints++] = Node(ca.point(ang + PI / 2 - da), a);
		keyPoints[cntKeyPoints++] = Node(ca.point(ang - PI / 2 + da), a);
	} else {
		keyPoints[cntKeyPoints++] = Node(ca.point(ang + PI / 2 + da), a);
		keyPoints[cntKeyPoints++] = Node(ca.point(ang - PI / 2 - da), a);
	}
}

inline DB getLength(const int id, const Point &a, const Point &b) {
	DB ta = angle(a - cir[id].p), tb = angle(b - cir[id].p);
	while (sgn(ta - tb) > 0) tb += PI * 2;
	return cir[id].r * (tb - ta);
}

int andrew(Node *pt, int n, Node *ch) {
	int m = 0;
	sort(pt, pt + n);
	//for (int i = 0; i < n; ++i) cout << pt[i].p.x << ' ' << pt[i].p.y << ' ' << pt[i].id << endl;
	for (int i = 0; i < n; ++i) {
		while (m > 1 && sgn(cross(pt[i].p - ch[m - 2].p, ch[m - 1].p - ch[m - 2].p)) >= 0) --m;
		ch[m++] = pt[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; --i) {
		while (m > k && sgn(cross(pt[i].p - ch[m - 2].p, ch[m - 1].p - ch[m - 2].p)) >= 0) --m;
		ch[m++] = pt[i];
	}
	if (n > 0) --m;
	return m;
}

DB work(int n) {
	if (n < 0) return 0;
	if (n == 1) return 2 * PI * cir[0].r;
	cntKeyPoints = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) getPoint(i, j);
	DB sum = 0;
	int m = andrew(keyPoints, cntKeyPoints, ch);
	ch[m] = ch[0];
	for (int i = 0; i < m; ++i) {
		//cout << ch[i].p.x << ' ' << ch[i].p.y << ' ' << ch[i].id << endl;
		if (ch[i].id == ch[i + 1].id) sum += getLength(ch[i].id, ch[i].p, ch[i + 1].p);
		else sum += veclen(ch[i].p - ch[i + 1].p);
	}
	return sum;
}

int run() {
	int _, n;
	cin >> _;
	while (_--) {
		cin >> n;
		for (int i = 0; i < n; ++i) cir[i].get();
		cout << work(n) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_g", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	return run();
}
