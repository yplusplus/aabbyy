// by lys
#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 9;
const int M = 1 << 5;
const int INF = INT_MAX >> 1;
int n, m, dist[N][N], mat[M][M], h, w;
int lx[N], ly[N], mch[N], sl[N], mm[N];
bool vx[N], vy[N];

bool dfs(int x) {
	vx[x] = 1;
	for (int y = 1; y <= m; ++y) {
		if (vy[y]) continue;
		int t = lx[x] + ly[y] - dist[x][y];
		if (t) sl[y] = min(t, sl[y]);
		else {
			vy[y] = 1;
			if (~mch[y] && !dfs(mch[y])) continue;
			mch[y] = x;
			return 1;
		}
	}
	return 0;
}

int km() {
	for (int i = 1; i <= n; ++i) {
		lx[i] = -INF;
		for (int j = 1; j <= m; ++j) lx[i] = max(dist[i][j], lx[i]);
	}
	for (int i = 1; i <= m; ++i) {
		mch[i] = -1;
		ly[i] = 0;
	}
	for (int x = 1; x <= n; ++x) {
		for (int i = 1; i <= m; ++i) sl[i] = INF;
		int msl;
		while (1) {
			for (int i = 1; i <= n; ++i) vx[i] = 0;
			for (int i = 1; i <= m; ++i) vy[i] = 0;
			if (dfs(x)) break;
			msl = INF;
			for (int i = 1; i <= m; ++i) if (!vy[i]) msl = min(sl[i], msl);
			for (int i = 1; i <= n; ++i) {
				if (vx[i]) lx[i] -= msl;
			}
			for (int i = 1; i <= m; ++i) {
				if (vy[i]) ly[i] += msl;
				else sl[i] -= msl;
			}
		}
	}
	int sum = 0;
	for (int i = 1; i <= m; ++i) {
		//cout << i << ' ' << mch[i] << ' ' << (mch[i] > 0 ? dist[mch[i]][i] : 0) << endl;
		if (~mch[i]) {
			sum += dist[mch[i]][i];
			mm[mch[i]] = i;
		}
	}
	return sum;
}

void showMat(int a, int b) {
	cout << "Mat " << a << ' ' << b << endl;
	for (int i = 1; i <= a; ++i) {
		for (int j = 1; j <= b; ++j) cout << mat[i][j] << ' ';
		cout << endl;
	}
}

void showDist(int a, int b) {
	cout << "Dist " << a << ' ' << b << endl;
	for (int i = 1; i <= a; ++i) {
		for (int j = 1; j <= b; ++j) cout << dist[i][j] << ' ';
		cout << endl;
	}
}

int inArc[N];
vector<int> nxVex[N];

inline bool inMat(int a, int b) { return 1 <= a && a <= h && 1 <= b && b <= w; }
void topoSort() {
	queue<int> q;
	int cnt = n;
	for (int i = 1; i <= n; ++i) {
		if (inArc[i]) continue;
		q.push(i);
	}
	bool pnt = 0;
	while (!q.empty()) {
		int x = q.front();
		--cnt;
		q.pop();
		if (pnt) cout.put(' ');
		else pnt = 1;
		cout << x;
		for (int i = 0, sz = nxVex[x].size(); i < sz; ++i) {
			int y = nxVex[x][i];
			if (--inArc[y] == 0) q.push(y);
		}
	}
	cout << endl;
	if (cnt) while (1);
}

void work() {
	int id = 0;
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			if (mat[i][j]) {
				if (mat[i][j] == INF) mat[i][j] = 0;
			} else mat[i][j] = --id;
		}
	}
	m = -id;
	//showMat(h, w);
	for (int a = 1; a <= h; ++a) {
		for (int b = 1; b <= w; ++b) {
			if (mat[a][b] <= 0) continue;
			for (int c = 1; c <= h; ++c) {
				for (int d = 1; d <= w; ++d) {
					if (mat[c][d] >= 0) continue;
					dist[mat[a][b]][-mat[c][d]] = -(abs(a - c) + abs(b - d));
				}
			}
		}
	}
	//showDist(n, m);
	int ans = km();
	//cout << ans << endl;
	for (int i = 1; i <= n; ++i) inArc[i] = 0;
	for (int i = 1; i <= n; ++i) nxVex[i].clear();
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			if (mat[i][j] <= 0) continue;
			int x = mat[i][j], y, d = -dist[x][mm[x]], nx, ny;
			bool ok = 0;
			for (int t = 1; t <= d; ++t) {
				for (int dx = -t, dy; !ok && dx <= t; ++dx) {
					dy = t - abs(dx);
					//cout << i << ' ' << j << ' ' << dx << ' ' << dy << endl;
					for (int p = -1; !ok && p <= 1; ++p, ++p) {
						if (dy == 0 && p >= 1) break;
						nx = i + dx, ny = j + dy * p;
						if (inMat(nx, ny)) {
							//cout << nx << ' ' << ny << ' ' << mat[nx][ny] << endl;
							if (mat[nx][ny] >= 0) continue;
							y = -mat[nx][ny];
							if (~mch[y] && mch[y] != x) {
								//cout << x << '&' << y << ' ' << mch[y] << endl;
								nxVex[mch[y]].push_back(x);
								++inArc[x];
							} else ok = 1;
						}
					}
				}
			}
		}
	}
	//for (int i = 1; i <= n; ++i) {
	//	cout << i << ' ' << inArc[i] << ": ";
	//	for (int j = 0, sz = nxVex[i].size(); j < sz; ++j) cout << nxVex[i][j] << ' ';
	//	cout << endl;
	//}
	topoSort();
}

int run() {
	int k, s;
	while (cin >> h >> w >> k >> s) {
		n = k;
		int x, y;
		memset(mat, 0, sizeof mat);
		for (int i = 1; i <= k; ++i) {
			cin >> x >> y;
			mat[x][y] = i;
		}
		for (int i = 0; i < s; ++i) {
			cin >> x >> y;
			mat[x][y] = INF;
		}
		work();
	}
	return 0;
}

int main() {
	freopen("agrarian.in", "r", stdin);
	freopen("agrarian.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}