#include <bits/stdc++.h>
using namespace std;

const int N = 111;
const double eps = 1e-8;
int n, r, c, v, s;
int id[N][N];
bool full[N];
bool cover[N][N];
int cnt[N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool check(int x, int y) { return x >= 0 && x < r && y >= 0 && y < c; }
bool equal(double a, double b) {
	return fabs(a - b) < eps;
}

struct Rect {
	int x1, y1, x2, y2, d;
	double vol;
	void read() {
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &d);
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		vol = (x2 - x1) * (y2 - y1) * d * 10;
	}
} rect[N];

void cover_rect(int i) {
	for (int x = rect[i].x1; x < rect[i].x2; x++) {
		for (int y = rect[i].y1; y < rect[i].y2; y++) {
			cover[x][y] = true;
		}
	}
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int x = rect[i].x1; x < rect[i].x2; x++) {
			for (int y = rect[i].y1; y < rect[i].y2; y++) {
				id[x][y] = i;
			}
		}
	}
	memset(full, false, sizeof(full));
	memset(cover, false, sizeof(cover));
	int left = n - 1;
	double ans = rect[s].vol / v;
	//cout << rect[s].vol << " " << v << endl;
	rect[s].vol = 0;
	full[s] = true;
	cover_rect(s);
	//cout << ans << endl;
	while (left) {
		int sum = 0;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (cover[i][j]) {
					for (int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if (!check(x, y) || !cover[x][y]) sum++;
						else continue;
						if (check(x, y)) {
							cnt[id[x][y]]++;
						}
					}
				}
			}
		}
		double min_t = 1e30;
		for (int i = 0; i < n; i++) {
			if (full[i]) continue;
			if (cnt[i] == 0) continue;
			double vv = 1.0 * cnt[i] / sum * v;
			double tmp = rect[i].vol / vv;
			min_t = min(min_t, tmp);
		}
		//cout << "*********" << endl;
		//cout << min_t << " " << ans << endl;
		for (int i = 0; i < n; i++) {
			if (full[i]) continue;
			if (cnt[i] == 0) continue;
			double vv = 1.0 * cnt[i] / sum * v;
			double tmp = rect[i].vol / v;
			rect[i].vol -= min_t * vv;
			if (equal(min_t, tmp)) {
				//cout << left << " ";
				left--;
				cover_rect(i);
				full[i] = true;
			}
			//cout << endl;
		}
		ans += min_t;
	}
	printf("%.10f\n", ans);
}

int main() {
	while (~scanf("%d%d%d%d%d", &n, &r, &c, &s, &v)) {
		s--;
		memset(id, -1, sizeof(id));
		for (int i = 0; i < n; i++) {
			rect[i].read();
		}
		solve();
	}
	return 0;
}

