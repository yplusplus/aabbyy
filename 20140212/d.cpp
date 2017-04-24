#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef long long LL;
const DB EPS = 1e-5;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
typedef pair<DB, LL> Point;
#define x first
#define y second
Point operator + (const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
bool operator < (const Point &a, const Point &b) {
	if (sgn(a.x - b.x)) return a.x < b.x;
	return a.y < b.y;
}
bool operator > (const Point &a, const Point &b) {
	if (sgn(a.x - b.x)) return a.x > b.x;
	return a.y > b.y;
}
bool operator == (const Point &a, const Point &b) { return sgn(a.x - b.x) == 0 && a.y == b.y; }
bool operator != (const Point &a, const Point &b) { return !(a == b); }

const int N = 111;
const int INF = 0x33333333;
const DB FINF = 1e20;
const Point PINF(FINF, -INF);
const Point O(0, 0);
int n, m;
Point mat[N][N];
Point lx[N], ly[N], sl[N];
int mch[N];
bool vx[N], vy[N];

bool dfs(int x) {
	vx[x] = 1;
	for (int y = 0; y < m; y++) {
		if (vy[y]) continue;
		Point t = lx[x] + ly[y] - mat[x][y];
		if (t != O) sl[y] = min(t, sl[y]);
		else {
			vy[y] = 1;
			if (~mch[y] && !dfs(mch[y])) continue;
			mch[y] = x;
			return 1;
		}
	}
	return 0;
}

Point km() {
	for (int i = 0; i < n; i++) {
		lx[i] = O - PINF;
		for (int j = 0; j < m; j++) lx[i] = max(mat[i][j], lx[i]);
	}
	for (int i = 0; i < m; i++) mch[i] = -1;
	for (int i = 0; i < m; i++) ly[i] = O;
	for (int x = 0; x < n; x++) {
		for (int i = 0; i < m; i++) sl[i] = PINF;
		Point min_sl;
		while (1) {
			for (int i = 0; i < n; i++) vx[i] = 0;
			for (int i = 0; i < m; i++) vy[i] = 0;
			if (dfs(x)) break;
			min_sl = PINF;
			for (int i = 0; i < m; i++) if (!vy[i]) min_sl = min(sl[i], min_sl);
			for (int i = 0; i < n; i++) if (vx[i]) lx[i] = lx[i] - min_sl;
			for (int i = 0; i < m; i++) {
				if (vy[i]) ly[i] = ly[i] + min_sl;
				else sl[i] = sl[i] - min_sl;
			}
		}
	}
	Point ans(0, 0);
	for (int i = 0; i < m; i++) if (~mch[i]) ans = ans + mat[mch[i]][i];
	return ans;
}

template<class T> inline T sqr(T x) { return x * x; }
int x[N], y[N], h[N], w[N];
DB cal(DB x, DB y, DB z, DB I) {
	DB r = sqrt(sqr(x) + sqr(y) + sqr(z));
	DB cosi = z / r;
	return I / sqr(r) * cosi;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(3);
	int _;
	cin >> _;
	while (_-- && cin >> n >> m) {
		for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> h[i] >> w[i];
		int I, M, C;
		for (int i = 0; i < m; i++) {
			cin >> I >> M >> C;
			for (int j = 0; j < n; j++) {
				if (M > w[j]) mat[j][i] = Point(0, 0);
				else mat[j][i] = Point(cal(x[j], y[j], h[j], I), -C);
			}
		}
		Point ans = km();
		cout << ans.x << ' ' << -ans.y << endl;
	}
	return 0;
}
