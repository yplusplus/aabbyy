#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef long long LL;
typedef pair<LL, LL> Point;
typedef pair<DB, DB> Node;
typedef pair<Point, Point> Line;
#define x first
#define y second

const int N = 1111;
const DB PI = acos(-1.0);
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Line l1[N], l2[N];
int n1, n2;
bool vis[N];

Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Node operator - (const Point &a, const Node &b) { return Node(a.x - b.x, a.y - b.y); }
inline LL cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline LL dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline LL veclen(const Point &a) { return dot(a, a); }
inline DB dot(const Node &a, const Node &b) { return a.x * b.x + a.y * b.y; }
inline DB veclen(const Node &a) { return sqrt(dot(a, a)); }
inline DB angle(const Node &a) { return atan2(a.y, a.x); }
inline Point vec(const Line &a) { return a.y - a.x; }

bool overlap(Line &a, Line &b) {
	if (cross(vec(a), vec(b))) return 0;
	if (cross(a.x - b.x, a.y - b.x)) return 0;
	if (cross(a.x - b.y, a.y - b.y)) return 0;
	if (a.y < b.x) return 0;
	if (a.x > b.x) a.x = b.x;
	if (a.y < b.y) a.y = b.y;
	return 1;
}

bool get_pattern(Line *l, int &n) {
	n = 0;
	char op[3];
	int cx, cy, dx, dy;
	cx = cy = dx = dy = 0;
	scanf("%s", op);
	if (*op == 'Q') return 0;
	do {
		scanf("%d%d", &dx, &dy);
		if (*op == 'L') l[n].x = Point(cx, cy);
		cx += dx; cy += dy;
		if (*op == 'L') {
			l[n].y = Point(cx, cy);
			if (l[n].x != l[n].y) n++;
		}
	} while (~scanf("%s", op) && *op != 'E');
	for (int i = 0; i < n; i++) if (l[i].x > l[i].y) swap(l[i].x, l[i].y);
	sort(l, l + n);
	for (int i = 0; i < n; i++) vis[i] = 0;
	for (int i = 0; i < n; i++) {
		if (vis[i]) continue;
		for (int j = i + 1; j < n; j++) if (overlap(l[i], l[j])) vis[j] = 1;
	}
	int nn = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) l[nn++] = l[i];
	n = nn;
	//for (int i = 0; i < n; i++) cout << l[i].x.x << ' ' << l[i].x.y << ' ' << l[i].y.x << ' ' << l[i].y.y << endl;
	//cout << "~~~ " << n << " ~~~" << endl;
	return 1;
}

typedef pair<Node, Node> Event;
bool operator == (const Node &a, const Node &b) { return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0; }
bool operator == (const Event &a, const Event &b) { return a.x == b.x && a.y == b.y; }
Event ev1[N], ev2[N];
Event rel1[N], rel2[N];
LL len1[N], len2[N];

inline LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
inline Node get(const Point &a, const Node &b) { return Node(angle(a - b), veclen(a - b)); }
void fix(Event &e) {
	if (e.x > e.y) swap(e.x, e.y);
	if (e.y.x - e.x.x > PI) e.x.x += PI * 2;
	if (e.x > e.y) swap(e.x, e.y);
}

bool compare(Line *l1, int n1, Line *l2, int n2) {
	if (n1 != n2) return 0;
	int n = n1;
	for (int i = 0; i < n; i++) len1[i] = veclen(vec(l1[i]));
	for (int i = 0; i < n; i++) len2[i] = veclen(vec(l2[i]));
	sort(len1, len1 + n);
	sort(len2, len2 + n);
	LL GCD = gcd(len1[0], len2[0]);
	DB k = sqrt((len2[0] / GCD) * 1.0 / (len1[0] / GCD));
	for (int i = 0; i < n; i++) {
		LL TMP = gcd(len1[i], len2[i]);
		if (len1[0] / GCD != len1[i] / TMP) return 0;
		if (len2[0] / GCD != len2[i] / TMP) return 0;
	}
	Point s1, s2;
	s1 = s2 = Point(0, 0);
	for (int i = 0; i < n; i++) s1 = s1 + l1[i].x, s1 = s1 + l1[i].y;
	for (int i = 0; i < n; i++) s2 = s2 + l2[i].x, s2 = s2 + l2[i].y;
	Node center1, center2;
	center1 = Node(s1.x * 1.0 / (n * 2), s1.y * 1.0 / (n * 2));
	center2 = Node(s2.x * 1.0 / (n * 2), s2.y * 1.0 / (n * 2));
	//cout << center1.x << ' ' << center1.y << endl;
	//cout << center2.x << ' ' << center2.y << endl;
	for (int i = 0; i < n; i++) {
		ev1[i] = Event(get(l1[i].x, center1), get(l1[i].y, center1));
		fix(ev1[i]);
	}
	for (int i = 0; i < n; i++) {
		ev2[i] = Event(get(l2[i].x, center2), get(l2[i].y, center2));
		fix(ev2[i]);
	}
	sort(ev1, ev1 + n); ev1[n] = ev1[0]; ev1[n].x.x += PI * 2; ev1[n].y.x += PI * 2;
	sort(ev2, ev2 + n); ev2[n] = ev2[0]; ev2[n].x.x += PI * 2; ev2[n].y.x += PI * 2;
	//cout << "K " << k << endl;
	for (int i = 0; i < n; i++) {
		rel1[i] = ev1[i]; rel1[i].x.x = ev1[i].y.x - ev1[i].x.x; rel1[i].y.x = ev1[i + 1].x.x - ev1[i].x.x;
		rel1[i].x.y *= k, rel1[i].y.y *= k;
		rel2[i] = ev2[i]; rel2[i].x.x = ev2[i].y.x - ev2[i].x.x; rel2[i].y.x = ev2[i + 1].x.x - ev2[i].x.x;
	}
	sort(rel1, rel1 + n);
	sort(rel2, rel2 + n);
	//for (int i = 0; i < n; i++) cout << rel1[i].x.x << ' ' << rel1[i].y.x << ' ' << rel2[i].x.x << ' ' << rel2[i].y.x << endl;
	//for (int i = 0; i < n; i++) cout << rel1[i].x.y << '~' << rel1[i].y.y << ' ' << rel2[i].x.y << '~' << rel2[i].y.y << endl;
	for (int i = 0; i < n; i++) if (!(rel1[i] == rel2[i])) return 0;
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (get_pattern(l1, n1)) {
		get_pattern(l2, n2);
		if (compare(l1, n1, l2, n2)) puts("YES");
		else puts("NO");
	}
	return 0;
}