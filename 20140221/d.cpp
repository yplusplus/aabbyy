#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB PI = acos(-1.0);
const DB PI2 = PI * 2;

Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB angle(const Point &a) { return atan2(a.y, a.x); }
inline DB to_rad(const DB &a) { return a * PI / 180; }
inline void get(Point &a) { cin >> a.x >> a.y; }

int cal(const vector<DB> &a, int n, const DB &f) {
	int cnt = 1;
	DB last = a[0];
	for (int i = 0; i < n; i++) {
		if (a[i] - last > f) cnt++, last = a[i];
	}
	return cnt;
}

int main() {
	int n, cas = 0;
	ios::sync_with_stdio(0);
	while (cin >> n) {
		DB f;
		Point ori, dest;
		get(ori);
		cin >> f;
		if (fabs(n + ori.x + ori.y + f) < 1e-8) break;
		vector<DB> ang;
		f = to_rad(f);
		for (int i = 0; i < n; i++) {
			get(dest);
			ang.push_back(angle(dest - ori));
		}
		sort(ang.begin(), ang.end());
		int ans = n;
		for (int i = 0; i < n; i++) {
			ans = min(cal(ang, n, f), ans);
			ang[0] += PI2;
			rotate(ang.begin(), ang.begin() + 1, ang.end());
		}
		cout << "Case " << ++cas << ": " << ans << endl;
	}
	return 0;
}
