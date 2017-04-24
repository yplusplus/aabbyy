#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> Point;
typedef pair<Point, Point> Line;
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
istream &operator >> (istream &in, Point &a) { in >> a.x >> a.y; return in; }
ostream &operator << (ostream &out, Point &a) { out << a.x << ' ' << a.y; return out; }
inline LL cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline LL dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

/*
   inline Point fix(const Point &a) {
   LL g = __gcd(abs(a.x), abs(a.y));
   if (a.y == 0) return Point(1, 0);
   else if (a.y < 0) return Point(-a.x / g, -a.y / g);
   else return Point(a.x / g, a.y / g);
   }
 */

struct Linear {
	LL a, b, c;
	Linear() {}
	Linear(const Line &l) {
		const Point &p1 = l.x, &p2 = l.y;
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		c = -a * p1.x - b * p1.y;
	}
} ;

inline bool isparallel(const Line &a, const Line &b) { return 0 == cross(a.x - a.y, b.x - b.y); }
bool llint(const Line &a, const Line &b, Point &ip) {
	Linear l1(a), l2(b);
	if (isparallel(a, b)) return 0;
	LL A = l1.b * l2.c - l1.c * l2.b;
	LL B = l1.a * l2.b - l1.b * l2.a;
	LL C = l1.a * l2.c - l1.c * l2.a;
	LL D = l1.b * l2.a - l1.a * l2.b;
	if (abs(A) % abs(B) || abs(C) % abs(D)) return 0;
	ip.x = A / B;
	ip.y = C / D;
	if (dot(a.x - ip, a.y - ip) > 0) return 0;
	if (dot(b.x - ip, b.y - ip) > 0) return 0;
	return 1;
}

bool merge(Line &a, Line &b) {
	if (!isparallel(a, b)) return 0;
	if (a.y < b.x || b.y < a.x) return 0;
	if (!isparallel(Line(a.x, b.x), Line(a.x, b.y))) return 0;
	if (!isparallel(Line(a.y, b.x), Line(a.y, b.y))) return 0;
	a.x = min(b.x, a.x);
	a.y = max(b.y, a.y);
	return 1;
}

typedef vector<Line> VL;
typedef vector<bool> VB;
LL get_pt(const Line &a) {
	Point v = a.x - a.y;
	v.x = abs(v.x);
	v.y = abs(v.y);
	return __gcd(v.x, v.y) + 1;
}

int run() {
	int n;
	while (cin >> n) {
		VL seg(n);
		for (int i = 0; i < n; ++i) {
			cin >> seg[i].x >> seg[i].y;
			if (seg[i].x > seg[i].y) swap(seg[i].x, seg[i].y);
		}
		VB vis(n, 0);
		sort(seg.begin(), seg.end());
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			for (int j = i + 1; j < n; ++j) {
				if (vis[j]) continue;
				if (merge(seg[i], seg[j])) vis[j] = 1;
			}
		}
		LL ans = 0;
		Point ip;
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			//cout << seg[i].x << ' ' << seg[i].y << endl;
			set<Point> has;
			ans += get_pt(seg[i]);
			for (int j = 0; j < i; ++j) {
				if (vis[j]) continue;
				if (!llint(seg[i], seg[j], ip)) continue;
				has.insert(ip);
				//cout << "ip1 " << ip << endl;
			}
			for (int j = i + 1; j < n; ++j) {
				if (vis[j]) continue;
				if (!llint(seg[i], seg[j], ip)) continue;
				ans -= has.find(ip) == has.end();
				//cout << "ip2 " << ip << endl;
			}
			//cout << ans << endl;
		}
		cout << ans << endl;
	}
	return 0;
}

int main() {
	//freopen("in_e", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
