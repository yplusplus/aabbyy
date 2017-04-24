#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <set>

using namespace std;

const long double EPS = 1e-10;
const long double PI = acos(-1.0);
inline int sgn(long double x) { return (x > EPS) - (x < -EPS);}

typedef pair<long double, long double> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, long double p) { return Point(a.x * p, a.y * p);}
Point operator / (Point a, long double p) { return Point(a.x / p, a.y / p);}

inline long double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline long double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline long double veclen(Point a) { return dot(a, a);}
inline long double angle(Point a) { return atan2(a.y, a.x);}

const int N = 55555;
struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() { return t - s;}
	Point point(long double p) { return s + vec() * p;}
} line[N];
int n;
inline Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}

Line cur;
Point lamp;
long double getdis(int id) {
	Line &l = line[id];
	if (sgn(cross(cur.vec(), l.vec())) == 0) return min(veclen(l.s - lamp), veclen(l.t - lamp));
	Point ip = llint(cur, l);
	return veclen(ip - lamp);
}

struct Node {
	int id;
	Node() {}
	Node(int id) : id(id) {}
	bool operator < (Node p) const {
		long double da = getdis(id), db = getdis(p.id);
		return sgn(da - db) < 0;
	}
	bool operator == (Node p) const { return id == p.id;}
} ;

typedef pair<long double, int> Event;
bool operator < (Event a, Event b) { return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && a.y < b.y;}
Event event[N << 2];
int cnt_event;

void getevent(int id) {
	long double a = angle(line[id].s - lamp);
	long double b = angle(line[id].t - lamp);
	if (sgn(a - b) == 0) return ;
	if (a > b) swap(a, b);
	long double da = fabs(b - a);
	if (da > PI) {
		if (sgn(-PI - a)) event[cnt_event++] = Event(-PI, id), event[cnt_event++] = Event(a, -id);
		if (sgn(b - PI)) event[cnt_event++] = Event(b, id), event[cnt_event++] = Event(PI, -id);
	} else event[cnt_event++] = Event(a, id), event[cnt_event++] = Event(b, -id);
}

const long double D = 10000;

void print(Point &a) { cout << a.x << ' ' << a.y << endl;}
void print(Line &a) { print(a.s), print(a.t);}

double work() {
	long double ans = 0;
	cnt_event = 0;
	for (int i = 1; i <= n; i++) getevent(i);
	int tt = cnt_event;
	sort(event, event + tt);
	set<Node> stat;
	assert(event[0].y > 0);
	stat.insert(Node(event[0].y));
	//cout << "Event " << event[0].x << ' ' << event[0].y << endl;
	cur.s = lamp;
	Point ip1, ip2;
	for (int i = 1; i < tt; i++) {
		Event &e = event[i], &p = event[i - 1];
		//cout << "Event " << e.x << ' ' << e.y << endl;
		if (e.y > 0) cur.t = lamp + Point(cos(e.x + EPS), sin(e.x + EPS)) * D;
		else cur.t = lamp + Point(cos(e.x - EPS), sin(e.x - EPS)) * D;
		int cid = stat.begin()->id;
		if (e.y > 0) stat.insert(Node(e.y));
		else stat.erase(Node(-e.y));
		if (sgn(event[i - 1].x - event[i].x) == 0) continue;
		ip1 = llint(line[cid], Line(lamp, lamp + Point(cos(p.x), sin(p.x)) * D));
		ip2 = llint(line[cid], Line(lamp, lamp + Point(cos(e.x), sin(e.x)) * D));
		ans += cross(ip1 - lamp, ip2 - lamp);
		//cout << "id " << cid << ' ' << stat.size() << endl;
		//print(ip1), print(ip2);
		//cout << cross(ip1 - lamp, ip2 - lamp) / 2 << endl;
	}
	return (double) (ans / 2);
}

Point room[N];

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> lamp.x >> lamp.y >> n) {
		lamp.x *= 10000;
		lamp.y *= 10000;
		for (int i = 0; i < n; i++) {
			cin >> room[i].x >> room[i].y;
			room[i].x *= 10000;
			room[i].y *= 10000;
		}
		room[n] = room[0];
		for (int i = 1; i <= n; i++) line[i] = Line(room[i - 1], room[i]);
		cout << work() / 100000000 << endl;
	}
	return 0;
}


