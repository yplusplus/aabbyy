#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const int N = 111;
const DB PI = acos(-1.0);
const DB EPS = 1e-4;
Point ans[N];
int tt;

inline int sgn(const DB &a) { return (a > EPS) - (a < EPS); }
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point &a, const DB &p) { return Point(a.x * p, a.y * p); }
Point operator / (const Point &a, const DB &p) { return Point(a.x / p, a.y / p); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return dot(a, a); }

bool check(int n) {
	int c = 0;
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (sgn(veclen(ans[i] - ans[j]) - 1.0) == 0) c++;
	return c == n;
}

inline Point rotate(const Point &a, DB p) { return Point(a.x * cos(p) - a.y * sin(p), a.x * sin(p) + a.y * cos(p)); }

void test() {
	int n = 3;
	DB ang = PI / n, r, area;
	r = 0.5 / sin(ang);
	area = r * sin(ang) * r * cos(ang) * n;
	cout << r << ' ' << area << ' ' << r * r * PI << endl;
	for (int i = 0; i < 30; i++) cout << r * cos(1.0 / N * i) << ' ' << r * sin(1.0 / N * i) << endl;
	exit(0);
}

void PRE() {
	ans[0] = Point(0.0, 0.0);
	ans[1] = Point(1.0, 0.0);
	ans[2] = rotate(ans[1], PI / 3);
	Point ori = rotate(ans[1], PI / 6);
	for (int i = 3; i < N; i++) ans[i] = ori, rotate(ori, PI / N * i / 20);
}

int main() {
	cout << setiosflags(ios::fixed) << setprecision(6);
	//test();
	PRE();
	int _, n; cin >> _;
	while (_--) {
		cin >> n;
		if (n >= 4) {
			cout << "Yes" << endl;
			for (int i = 0; i < n; i++) cout << ans[i].x << ' ' << ans[i].y << endl;
		} else cout << "No" << endl;
	}
	return 0;
}