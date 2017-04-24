#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> Point;
#define x first
#define y second
Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y);}

inline LL cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline LL dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}
inline LL veclen(Point a) { return dot(a, a);}

typedef pair<Point, Point> Node; // xx - l1  xy - l2  yx - angle  yy - lr

const int N = 22222;
Point pt[N];
Node m1[N], m2[N];

template<class T>
int cmp(T a, T b) {
	if (a == b) return 0;
	if (a < b) return -1;
	return 1;
}

inline Node angle(Point a, Point b, Point c) { return Node(Point(veclen(a - b), veclen(b - c)), Point(dot(a - b, b - c), cmp(cross(a - b, b - c), 0ll)));}

int mini(Node *a, int n) {
	int i = 0, j = 1, k = 0, t;
	while (i < n && j < n && k < n) {
		t = cmp(a[(i + k) % n], a[(j + k) % n]);
		if (!t) k++;
		else {
			if (t > 0) i += k + 1;
			else j += k + 1;
			if (i == j) j++;
			k = 0;
		}
	}
	return min(i, j);
}

bool check(int n) {
	for (int i = 0; i < n; i++) if (!(m1[i] == m2[i])) return false;
	return true;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> pt[i].x >> pt[i].y;
		pt[n] = pt[0], pt[n + 1] = pt[1];
		for (int i = 0; i < n; i++) {
			m1[i] = angle(pt[i], pt[i + 1], pt[i + 2]);
			m2[i] = angle(pt[i + 2], pt[i + 1], pt[i]);
			m2[i].y.y = -m2[i].y.y;
		}
		reverse(m2, m2 + n);
		int p; p = mini(m1, n);
		rotate(m1, m1 + p, m1 + n);
		p = mini(m2, n);
		rotate(m2, m2 + p, m2 + n);
		//for (int i = 0; i < n; i++) cout << m1[i].x.x << ' ' << m1[i].x.y << ' ' << m1[i].y.x << ' ' << m1[i].y.y << endl;
		//cout << "~~~~~~~~~~~~~" << endl;
		//for (int i = 0; i < n; i++) cout << m2[i].x.x << ' ' << m2[i].x.y << ' ' << m2[i].y.x << ' ' << m2[i].y.y << endl;
		//cout << "~~~~~~~~~~~~~" << endl;
		if (check(n)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
