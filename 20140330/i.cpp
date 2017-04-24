#include <bits/stdc++.h>
using namespace std;

const int N = 1222;
const double EPS = 1e-10;
int x[N], y[N];
int color[N];
double mid;
double g[N][N];
int n;

double sq(double x) { return x * x; }
double get_dist(int a, int b) { return sqrt(sq(x[a] - x[b]) + sq(y[a] - y[b])); }

bool dfs(int u) {
	for (int v = 0; v < n; v++) {
		if (u == v) { continue; }
		if (g[u][v] + EPS < 2 * mid) {
			if (color[v] == -1) {
				color[v] = color[u] ^ 1;
				if (!dfs(v)) return false;
			} else if (color[v] == color[u]) return false;
		}
	}
	return true;
}

bool check() {
	memset(color, -1, sizeof(color));
	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			color[i] = 0;
			if (!dfs(i)) return false;
		}
	}
	return true;
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = get_dist(i, j);
		}
	}
	double l = 0, r = 1e10;
	double ans = -1;
	for (int i = 0; i < 88; i++) {
		mid = (l + r) / 2;
		if (check()) {
			ans = mid;
			l = mid;
		} else {
			r = mid;
		}
	}
	mid = ans;
	check();
	printf("%.10f\n", ans);
	for (int i = 0; i < n; i++) {
		printf("%d%c", color[i] + 1, i == n - 1 ? '\n' : ' ');
	}
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &x[i], &y[i]);
		}
		solve();
	}
	return 0;
}
