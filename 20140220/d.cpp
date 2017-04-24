#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const int N = 1 << 10;
const int INF = 100000000;
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { 1, 0, -1, 0 };

int dist[N][N], n, m, k;
Point a[N], b[N];
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }
inline void get(Point &a) { cin >> a.x >> a.y; }

inline Point cal_x(const Point &a, const Point &b, const DB &x) {
	DB k = (x - a.x) / b.x;
	if (sgn(k) < 0) return Point(INF, INF);
	return Point(a.x + b.x * k, a.y + b.y * k);
}

inline Point cal_y(const Point &a, const Point &b, const DB &y) {
	DB k = (y - a.y) / b.y;
	if (sgn(k) < 0) return Point(INF, INF);
	return Point(a.x + b.x * k, a.y + b.y * k);
}

void print_mat(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cerr << dist[i][j] << ' ';
		cerr << endl;
	}
}

bool work() {
	queue<int> qx, qy;
	for (int x = 0; x < n; x++) {
		for (int i = 0; i < k; i++) {
			if (sgn(b[i].x) == 0) continue;
			DB y = cal_x(a[i], b[i], x).y;
			if (sgn(y) < 0 || sgn(y - m) >= 0) continue;
			int iy = (int) y + EPS;
			qx.push(x);
			qy.push(iy);
			dist[x][iy] = 0;
			if (sgn(iy - y)) {
				qx.push(x);
				qy.push(iy + 1);
				dist[x][iy + 1] = 0;
			}
		}
	}
	for (int y = 0; y < m; y++) {
		for (int i = 0; i < k; i++) {
			if (sgn(b[i].y) == 0) continue;
			DB x = cal_y(a[i], b[i], y).x;
			if (sgn(x) < 0 || sgn(x - n) >= 0) continue;
			int ix = (int) x + EPS;
			qx.push(ix);
			qy.push(y);
			dist[ix][y] = 0;
			if (sgn(ix - x)) {
				qx.push(ix + 1);
				qy.push(y);
				dist[ix + 1][y] = 0;
			}
		}
	}
	//print_mat(n, m);
	int x, y, nx, ny, ans = 0;
	while (!qx.empty()) {
		x = qx.front(); qx.pop();
		y = qy.front(); qy.pop();
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (!inmat(nx, ny)) continue;
			if (dist[nx][ny] == INF) {
				qx.push(nx);
				qy.push(ny);
			}
			ans = max(dist[nx][ny] = min(dist[x][y] + 1, dist[nx][ny]), ans);
		}
	}
	if (ans == 0) return 0;
	bool pnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dist[i][j] == ans) {
				if (pnt) cout.put(' ');
				cout << "(" << i << ", " << j << ")";
				pnt = 1;
			}
		}
	}
	cout << endl;
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	while (cin >> n >> m >> k) {
		for (int i = 0; i < k; i++) { get(a[i]); get(b[i]); }
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) dist[i][j] = INF;
		if (!work()) cout << "MISS!" << endl;
	}
	return 0;
}