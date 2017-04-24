#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Point;
#define x first
#define y second
void get(Point &a) { cin >> a.x >> a.y; }
Point normal(const Point &a) { return Point(-a.y, a.x); }

int main() {
	int _;
	ios::sync_with_stdio(0);
	cin >> _;
	for (int i = 1; i <= _; i++) {
		Point a, b;
		get(a); get(b);
		b = normal(Point(a.x - b.x, a.y - b.y));
		int gcd = __gcd(abs(b.x), abs(b.y));
		if (gcd) b.x /= gcd, b.y /= gcd;
		a = Point(0, 0);
		if (b.x < 0) a.x -= b.x, b.x = 0;
		if (b.y < 0) a.y -= b.y, b.y = 0;
		cout << "Case " << i << ": " << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << endl;
	}
	return 0;
}
