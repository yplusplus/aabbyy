#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long double DB;
typedef long long LL;
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
inline DB angle(const Point &a, const Point &b) { return acos(dot(a, b) / veclen(a) / veclen(b)); }
inline bool get(Point &a) { return cin >> a.x >> a.y; }

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() const { return t - s; }
	Point point(const DB &p) const { return s + vec() * p; }
} ;
inline Point llint(const Line &a, const Line &b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec())); }
inline DB pt2line(const Point &p, const Line &l) { return cross(l.s - p, l.t - p) / veclen(l.vec()); }

const int N = 111;
const int M = 11111;
Point pt[M], arc[N][3];
int n, m, id[M];

void input() {
	for (int i = 0; i < n; i++) {
	   for (int j = 0; j < 3; j++) get(arc[i][j]);
	}
	for (int i = 0; i < m; i++) get(pt[i]);
}

bool check(Point *smiley, const Point &p) {
	if (sgn(dot(smiley[0] - smiley[2], p - smiley[2])) <= 0) return 0;
	if (sgn(dot(smiley[2] - smiley[0], p - smiley[0])) <= 0) return 0;
	DB d = pt2line(p, Line(smiley[0], smiley[2]));
	if (sgn(d) * sgn(pt2line(smiley[1], Line(smiley[0], smiley[2]))) >= 0) return 0;
	if (sgn(fabs(d) - veclen(smiley[0] - smiley[2]) * 2) >= 0) return 0;
	return 1;
}

int filter(Point *smiley) {
	int tt = 0;
	for (int i = 0; i < m; i++) {
		if (check(smiley, pt[i])) id[tt++] = i;
	}
	return tt;
}

inline int lowbit(int x) { return x & -x; }
struct BIT {
	int a[M], t;
	void init(int sz) { t = sz + 5; for (int i = 1; i <= t; i++) a[i] = 0; }
	void add(int x, int d) { for (x += 2 ; x <= t; x += lowbit(x)) a[x] += d; }
	int sum(int x) { int s = 0; for (x += 2 ; x > 0; x -= lowbit(x)) s += a[x]; return s; }
} bit;

int L[M], R[M], tmp[M];
DB dist[M][N << 1], vec_len[N], ang[M][N << 1];
//Line std_line;
int std_line;

bool cmp(int a, int b) {
	//DB a1 = angle(pt[id[a]] - std_line.s, std_line.vec());
	//DB a2 = angle(pt[id[b]] - std_line.s, std_line.vec());
	//DB d1 = veclen(pt[id[a]] - std_line.s);
	//DB d2 = veclen(pt[id[b]] - std_line.s);
	DB a1 = ang[id[a]][std_line];
	DB a2 = ang[id[b]][std_line];
	DB d1 = dist[id[a]][std_line];
	DB d2 = dist[id[b]][std_line];
	if (sgn(a1 - a2)) return a1 < a2;
	return d1 < d2;
}

LL cal_smiley(int x) {
	int tt = filter(arc[x]);
	//for (int i = 0; i < tt; i++) cout << "id " << i << ' ' << id[i] << endl;
	LL cnt = (LL) tt * (tt - 1) >> 1;
	//cout << cnt << endl;
	for (int i = 0; i < tt; i++) tmp[i] = R[i] = i;
	//std_line = Line(arc[x][0], arc[x][2]);
	std_line = x << 1;
	sort(tmp, tmp + tt, cmp);
	for (int i = 0; i < tt; i++) L[tmp[i]] = i;
	//std_line = Line(arc[x][2], arc[x][0]);
	std_line = x << 1 | 1;
	sort(R, R + tt, cmp);
	bit.init(tt);
	for (int i = 0; i < tt; i++) bit.add(i, 1);
	for (int i = tt - 1; i >= 0; i--) {
		bit.add(L[R[i]], -1);
		cnt -= bit.sum(L[R[i]]);
		//cout << i << '~' << cnt << endl;
	}
	//for (int i = 0; i < tt; i++) cout << i << ' ' << L[i] << ' ' << R[i] << endl;
	return cnt;
}

LL work() {
	LL ans = 0;
	for (int i = 0; i < n; i++) {
		vec_len[i] = veclen(arc[i][0] - arc[i][2]);
		for (int j = 0; j < m; j++) {
			dist[j][i << 1] = veclen(pt[j] - arc[i][0]);
			dist[j][i << 1 | 1] = veclen(pt[j] - arc[i][2]);
			ang[j][i << 1] = angle(pt[j] - arc[i][0], arc[i][2] - arc[i][0]);
			ang[j][i << 1 | 1] = angle(pt[j] - arc[i][2], arc[i][0] - arc[i][2]);
		}
	}
	//for (int i = 0; i < m; i++) cout << "pt " << i << ' ' << pt[i].x << ' ' << pt[i].y << endl;
	for (int i = 0; i < n; i++) {
		LL c = cal_smiley(i);
		//cout << c << endl;
		ans += c;
	}
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	while (cin >> n >> m) {
		input();
		cout << work() << endl;
	}
	return 0;
}


