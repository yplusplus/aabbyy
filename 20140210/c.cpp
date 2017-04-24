#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second

const DB EPS = 1e-6;
const DB FINF = 1e66;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
bool onseg(const Point &p, const Point &a, const Point &b) { return sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0; }

const int N = 1111;
const int M = N << 4;

int n;
DB vw, vc;
Point pts[N];

struct Edge {
	int u, v, nx;
	DB d;
	Edge() {}
	Edge(int u, int v, DB d, int nx) : u(u), v(v), d(d), nx(nx) {}
} edge[M];
int eh[N], ec;

#define FOR(i, u) for (int i = u; ~i; i = edge[i].nx)
void init() {
	memset(eh, -1, sizeof eh);
	ec = 0;
}

void addedge(int u, int v, DB d) {
	//cout << u << ' ' << v << ' ' << d << endl;
	edge[ec] = Edge(u, v, d, eh[u]);
	eh[u] = ec++;
}

void foreward(int x) {
	DB &h = pts[x].y;
	Line l(Point(0, h), Point(100, h));
	if (sgn(pts[x].y - pts[x + 1].y) >= 0) return ;
	Point ip;
	for (int i = x + 1; i < n; i++) {
		if (sgn(cross(l.vec(), pts[i] - pts[i + 1])) == 0) continue;
		ip = llint(Line(pts[i], pts[i + 1]), l);
		if (onseg(ip, pts[i], pts[i + 1])) {
			addedge(x, i + 1, veclen(pts[x] - ip) / vc + veclen(ip - pts[i + 1]) / vw);
			return ;
		}
	}
}

void backward(int x) {
	DB &h = pts[x].y;
	Line l(Point(0, h), Point(100, h));
	if (sgn(pts[x].y - pts[x - 1].y) >= 0) return ;
	Point ip;
	for (int i = x - 2; i >= 1; i--) {
		if (sgn(cross(l.vec(), pts[i] - pts[i + 1])) == 0) continue;
		ip = llint(Line(pts[i], pts[i + 1]), l);
		if (onseg(ip, pts[i], pts[i + 1])) {
			addedge(i, x, veclen(ip - pts[i]) / vw + veclen(pts[x] - ip) / vc);
			return ;
		}
	}
}

DB dist[N];
bool inq[N];
DB spfa(int s, int t) {
	for (int i = 0; i < N; i++) dist[i] = FINF;
	memset(inq, 0, sizeof inq);
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	inq[s] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		inq[cur] = 0;
		FOR(i, eh[cur]) {
			Edge &e = edge[i];
			if (sgn(dist[cur] + e.d - dist[e.v]) < 0) {
				dist[e.v] = dist[cur] + e.d;
				if (inq[e.v]) continue;
				q.push(e.v);
				inq[e.v] = 1;
			}
		}
	}
	return dist[t];
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> n >> vw >> vc) {
		init();
		for (int i = 1; i <= n; i++) cin >> pts[i].x >> pts[i].y;
		for (int i = 1; i <= n; i++) {
			if (i != n) foreward(i);
			if (i != 1) backward(i);
		}
		for (int i = 1; i < n; i++) addedge(i, i + 1, veclen(pts[i] - pts[i + 1]) / vw);
		cout << spfa(1, n) << endl;
	}
	return 0;
}
