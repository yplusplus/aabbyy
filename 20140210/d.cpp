#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
typedef pair<Point, int> Node;
#define x first
#define y second
const DB EPS = 1e-6;
const int N = 1111;
const int N2 = N << 1;

inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }

int next[N], n, m[2];
Point star[2][N], center[2];

void get_center(int x) {
	center[x] = Point(0, 0);
	for (int i = 0; i < n; i++) {
		center[x].x += star[x][i].x;
		center[x].y += star[x][i].y;
	}
	center[x].x /= n;
	center[x].y /= n;
}

void fix(int x) {
	m[x] = 0;
	for (int i = 0; i < n; i++) {
		if (center[x] == star[x][i]) continue;
		star[x][m[x]++] = star[x][i];
	}
}

Node rel[2][N << 1];
Point pivot;
bool cmp(const Point &a, const Point &b) {
	DB a1 = angle(a - pivot), d1 = veclen(a - pivot);
	DB a2 = angle(b - pivot), d2 = veclen(b - pivot);
	if (sgn(a1 - a2)) return a1 < a2;
	return d1 < d2;
}

const DB PI = acos(-1.0);
const DB PI2 = PI * 2;
const DB FINF = 1e66;
inline double fix(const DB &a) { return sgn(a) < 0 ? a + PI2 : a; }

void convert(int x) {
	pivot = center[x];
	sort(star[x], star[x] + n, cmp);
	star[x][n] = star[x][0];
	star[x][n + 1] = star[x][1];
	for (int i = 0; i < n; i++) {
		rel[x][i] = Node(Point(fix(angle(star[x][i + 2] - star[x][i + 1]) - angle(star[x][i + 1] - star[x][i])), veclen(star[x][i + 1] - star[x][i])), i);
		//cout << star[x][i].x << ' ' << star[x][i].y << endl;
	}
	DB min_dist = FINF;
	for (int i = 0; i < n; i++) min_dist = min(rel[x][i].x.y, min_dist);
	for (int i = 0; i < n; i++) rel[x][i].x.y /= min_dist;
	//for (int i = 0; i < n; i++) cout << i << ' ' << rel[x][i].x.x << ' ' << rel[x][i].x.y << endl;
}

void get_next(const Node *s, int n) {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < n) {
		while (~j && !(s[i].x == s[j].x)) j = next[j];
		i++, j++;
		next[i] = j;
	}
}

double fix2(DB a) {
	if (sgn(a) < 0) a += PI2;
	return sgn(a - PI) > 0 ? PI2 - a : a;
}

DB get_angle() {
	if (n == 0) return 0;
	get_next(rel[1], n);
	for (int i = 0; i < n; i++) rel[0][n + i] = rel[0][i];
	int i = 0, j = 0, n2 = n << 1;
	DB ans = PI;
	while (i < n2 && j < n) {
		while (~j && !(rel[0][i].x == rel[1][j].x)) j = next[j];
		i++, j++;
		if (j >= n) {
			int i1 = rel[0][i - n].y, i2 = rel[1][j - n].y;
			ans = min(fix2(angle(star[0][i1] - center[0]) - angle(star[1][i2] - center[1])), ans);
			j = next[j];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> n) {
		for (int i = 0; i < 2; i++) for (int j = 0; j < n; j++) cin >> star[i][j].x >> star[i][j].y;
		for (int i = 0; i < 2; i++) {
			get_center(i);
			fix(i);
		}
		assert(m[0] == m[1]);
		n = m[0];
		for (int i = 0; i < 2; i++) convert(i);
		cout << get_angle() << endl;
	}
	return 0;
}
/*
3  
-1 0
0 0
1 0
0 0 
0 1
0 2
*/
