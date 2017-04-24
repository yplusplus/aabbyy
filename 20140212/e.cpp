#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
Point pt[4];
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
void get(Point &a) { cin >> a.x >> a.y; }

void solve(DB a1, DB b1, DB c1, DB a2, DB b2, DB c2, DB &x, DB &y) {
	x = - (c1 * b2 - b1 * c2) / (a1 * b2 - b1 * a2);
	y = - (c1 * a2 - a1 * c2) / (b1 * a2 - a1 * b2);
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	DB W, H;
	int _;
	cin >> _;
	while (_--) {
		cin >> W >> H;
		for (int i = 0; i < 4; i++) get(pt[i]);
		Point v1 = pt[1] - pt[0], v2 = pt[3] - pt[0];
		DB A1 = v1.x / W - 1, B1 = v2.x / H, C1 = pt[0].x;
		DB A2 = v1.y / W, B2 = v2.y / H - 1, C2 = pt[0].y;
		DB x, y;
		solve(A1, B1, C1, A2, B2, C2, x, y);
		cout << x << ' ' << y << endl;
	}
	return 0;
}
