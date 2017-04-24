#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 55;
int mat[N][N], n, m;
bool dif[N][N], mk[N][N];
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m;}
typedef pair<int, int> PII;
typedef pair<PII, PII> PPP; 
PPP ans[N * N];
int cnt;

void expand(int x, int y) {
	int lx, ly, rx, ry, nx, ny;
	lx = rx = x, ly = ry = y;
	while (true) {
		bool ok = true;
		nx = lx - 1;
		for (int i = ly - 1; i <= ry + 1; i++) {
			if (inmat(nx, i) && dif[nx][i]) {
				lx--;
				ok = false;
				break;
			}
		}
		nx = rx + 1;
		for (int i = ly - 1; i <= ry + 1; i++) {
			if (inmat(nx, i) && dif[nx][i]) {
				rx++;
				ok = false;
				break;
			}
		}
		ny = ly - 1;
		for (int i = lx - 1; i <= rx + 1; i++) {
			if (inmat(i, ny) && dif[i][ny]) {
				ly--;
				ok = false;
				break;
			}
		}
		ny = ry + 1;
		for (int i = lx - 1; i <= rx + 1; i++) {
			if (inmat(i, ny) && dif[i][ny]) {
				ry++;
				ok = false;
				break;
			}
		}
		if (ok) break;
	}
	ans[cnt] = PPP(PII(lx + 1, ly + 1), PII(rx + 1, ry + 1));
	for (int i = lx; i <= rx; i++) for (int j = ly; j <= ry; j++) mk[i][j] = true;
}

int work() {
	cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dif[i][j] && !mk[i][j]) {
				expand(i, j);
				cnt++;
			}
		}
	}
	return cnt;
}

#define x first
#define y second

bool vis[N * N];
inline bool inside(PII p, PPP a) { return a.x.x <= p.x && p.x <= a.y.x && a.x.y <= p.y && p.y <= a.y.y;}

bool merge(int &n) {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++) {
		if (vis[i]) continue;
		for (int j = i + 1; j < n; j++) {
			if (inside(ans[i].x, ans[j]) || inside(ans[i].y, ans[j]) || inside(ans[j].x, ans[i]) || inside(ans[j].y, ans[i])) {
				ans[i].x.x = min(ans[i].x.x, ans[j].x.x);
				ans[i].x.y = min(ans[i].x.y, ans[j].x.y);
				ans[i].y.x = max(ans[i].y.x, ans[j].y.x);
				ans[i].y.y = max(ans[i].y.y, ans[j].y.y);
				vis[j] = true;
			}
		}
	}
	int tt = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) ans[tt++] = ans[i];
	if (n != tt) {
		n = tt;
		return true;
	} else return false;
}

int main() {
	//freopen("in", "r", stdin);
	while (cin >> n >> m) {
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> mat[i][j];
		memset(mk, 0, sizeof(mk));
		memset(dif, 0, sizeof(dif));
		int x;
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
			cin >> x;
			dif[i][j] = (x != mat[i][j]);
		}
		int c = work();
		while (merge(c)) ;
		cout << c << endl;
		sort(ans, ans + c);
		for (int i = 0; i < c; i++) cout << ans[i].x.x << ' ' << ans[i].x.y << ' ' << ans[i].y.x << ' ' << ans[i].y.y << endl;
	}
	return 0;
}
