#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
const DB EPS = 1e-2;
const DB PI = acos(-1.0);
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
template<class T> inline T sqr(T x) { return x * x; }
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline bool get(Point &a) { return cin >> a.x >> a.y; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }
inline DB angle(const DB &a, const DB &b, const DB &c) { return acos(min(1.0, max(-1.0, (sqr(b) + sqr(c) - sqr(a)) / (2 * b * c)))); }

const int N = 22;
const int M = N << 2;
typedef vector<Point> VP;
int n, m;
VP tri[N], tri2[M];
bool vis[N][M][M];
bool visit[M];
bool g[M][M], inblossom[M];
int match[M], pre[M], base[M];
queue<int> que;

bool check(VP &a, VP &b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	for (int i = 0; i < 3; i++) if (sgn(veclen(a[i] - b[i]))) return 0;
	return 1;
}

bool check(VP a, VP b, VP c) {
	VP tmp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (sgn(a[i].x - b[j].x)) continue;
			for (int k = 0; k < 3; k++) {
				if (i == k) continue;
				for (int l = 0; l < 3; l++) {
					if (j == l) continue;
					if (sgn(a[k].y - b[l].y)) continue;
					int p = 0, q = 0;
					while (p == i || p == k) p++;
					while (q == j || q == l) q++;
					tmp.clear();
					tmp.push_back(Point(a[k].x, b[j].y));
					tmp.push_back(Point(a[p].x - b[q].x, a[p].y - b[q].y));
					tmp.push_back(Point(PI - b[l].x, a[i].y));
					if (check(tmp, c)) return 1;
				}
			}
		}
	}
	return 0;
}

int find(int u, int v) {
	bool inpath[M];
	memset(inpath, false, sizeof(inpath));
	while (1) {
		u = base[u];
		inpath[u] = true;
		if (match[u] == -1) break;
		u = pre[match[u]];
	}
	while (1) {
		v = base[v];
		if (inpath[v]) return v;
		v = pre[match[v]];
	}
}

void reset(int u, int anc) {
	while (u != anc) {
		int v = match[u];
		inblossom[base[u]] = inblossom[base[v]] = true;
		v = pre[v];
		if (base[v] != anc) pre[v] = match[u];
		u = v;
	}
}

void contract(int u, int v, int n) {
	int anc = find(u, v);
	memset(inblossom, 0, sizeof(inblossom));
	reset(u, anc), reset(v, anc);
	if (base[u] != anc) pre[u] = v;
	if (base[v] != anc) pre[v] = u;
	for (int i = 0; i < n; i++) {
		if (inblossom[base[i]]) {
			base[i] = anc;
			if (!visit[i]) {
				que.push(i);
				visit[i] = 1;
			}
		}
	}
}

bool bfs(int s, int n) {
	for (int i = 0; i <= n; i++) pre[i] = -1, visit[i] = 0, base[i] = i;
	while (!que.empty()) que.pop();
	que.push(s);
	visit[s] = 1;
	while (que.size()) {
		int u = que.front(); que.pop();
		for (int v = 0; v < n; v++) {
			if (g[u][v] && base[v] != base[u] && match[u] != v) {
				if (v == s || (match[v] != -1 && pre[match[v]] != -1)) contract(u, v, n);
				else if (pre[v] == -1) {
					pre[v] = u;
					if (match[v] != -1) que.push(match[v]), visit[match[v]] = 1;
					else {
						u = v;
						while (u != -1) {
							v = pre[u];
							int w = match[v];
							match[u] = v, match[v] = u;
							u = w;
						}
						return true;
					}
				}
			}
		}
	}
	return  false;
}

int Match(int n) {
	memset(match, -1, sizeof(match));
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (match[i] == -1 && bfs(i, n)) ans++;
	}
	return ans;
}

int main() {
	//freopen("ina", "r", stdin);
	int Case = 0;
	//ios::sync_with_stdio(0);
	while (cin >> n && n) {
		if (Case) cout << endl;
		//if (cas) cout << endl;
		Point pt[3], pa[3];
		for (int i = 0; i < n; i++) {
			tri[i].clear();
			for (int j = 0; j < 3; j++) get(pt[j]);
			for (int j = 0; j < 3; j++) pa[j].y = veclen(pt[j] - pt[(j + 1) % 3]);
			for (int j = 0; j < 3; j++) pa[j].x = angle(pa[j].y, pa[(j + 1) % 3].y, pa[(j + 2) % 3].y);
			for (int j = 0; j < 3; j++) tri[i].push_back(pa[j]);
			sort(tri[i].begin(), tri[i].end());
		}
		m = n << 1;
		for (int i = 0; i < m; i++) {
			tri2[i].clear();
			for (int j = 0; j < 3; j++) get(pt[j]);
			for (int j = 0; j < 3; j++) pa[j].y = veclen(pt[j] - pt[(j + 1) % 3]);
			for (int j = 0; j < 3; j++) pa[j].x = angle(pa[j].y, pa[(j + 1) % 3].y, pa[(j + 2) % 3].y);
			for (int j = 0; j < 3; j++) tri2[i].push_back(pa[j]);
			sort(tri2[i].begin(), tri2[i].end());
		}
		//for (int i = 0; i < n; i++) { for (int j = 0; j < 3; j++) cout << tri[i][j].x << '~' << tri[i][j].y << ' '; cout << endl; }
		//for (int i = 0; i < m; i++) { for (int j = 0; j < 3; j++) cout << tri2[i][j].x << '~' << tri2[i][j].y << ' '; cout << endl; }
		//cout << "Case " << ++cas << ":" << endl;
		memset(vis, 0, sizeof vis);
		memset(g, false, sizeof(g));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < m; k++) {
					if (j == k) continue;
					vis[i][j][k] = check(tri[i], tri2[j], tri2[k]);
					if (vis[i][j][k]) {
						//cerr << i << ' ' << j << ' ' << k << endl;
						g[j][k] = g[k][j] = true;
					}
				}
			}
		}
		int ans = Match(m);
		//cout << ans << endl;
		vector<pair<int, int> > bag;
		for (int i = 0; i < m; i++) {
			int a = i, b = match[i];
			if (a > b) swap(a, b);
			//a++, b++;
			bag.push_back(make_pair(a, b));
		}
		sort(bag.begin(), bag.end());
		bag.erase(unique(bag.begin(), bag.end()), bag.end());
		printf("Case %d:\n", ++Case);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (vis[i][bag[j].first][bag[j].second]) {
					printf("Hole %d: %d, %d\n", i + 1, bag[j].first + 1, bag[j].second + 1);
					break;
				}
			}
		}
	}
	return 0;
}
