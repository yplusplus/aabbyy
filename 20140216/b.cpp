#include <bits/stdc++.h>
using namespace std;

const int N = 111;
typedef double DB;
struct Point {
	DB x, y, z;
	Point() {}
	Point(DB x, DB y, DB z) : x(x), y(y), z(z) {}
	void get() { cin >> x >> y >> z; }
} ;
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y, a.z - b.z); }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline DB veclen(const Point &a) { return sqrt(dot(a, a)); }

int n;
Point s, t, pt[N];
DB mat[N][N], r[N];

void floyd(int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = min(mat[i][k] + mat[k][j], mat[i][j]);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(0);
	for (int cas = 1; ; cas++) {
		cin >> n;
		if (n == -1) break;
		for (int i = 1; i <= n; i++) {
			pt[i].get();
			cin >> r[i];
		}
		pt[0].get();
		pt[n + 1].get();
		r[0] = r[n + 1] = 0;
		n += 2;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = max(veclen(pt[i] - pt[j]) - r[i] - r[j], 0.0);
			}
		}
		floyd(n);
		cout << "Cheese " << cas << ": Travel time = " << mat[0][n - 1] * 10 << " sec" << endl;
	}
	return 0;
}
