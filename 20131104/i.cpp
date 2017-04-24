#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1111;
typedef long long LL;
template<class T> T sqr(T x) { return x * x; }
int n, r, k, d, t[N], x[N], y[N];
bool rel[N][N], vis[N];

int convert(int x) { return x / d + (x % d != 0); }

int bfs() {
	int cur_time = 0;
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(0);
	vis[0] = 1;
	while (!q.empty()) {
		cur_time++;
		int sz = q.size();
		while (sz--) {
			int u = q.front(); q.pop();
			for (int i = 0; i < n; i++) {
				if (vis[i]) continue;
				if (rel[u][i]) {
					if (i == n - 1) return cur_time;
					q.push(i);
					vis[i] = 1;
				}
			}
		}
	}
	return -1;
}

bool work() {
	int c = 0, s = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0) continue;
		if (rel[i][n - 1]) {
			s += t[i];
			c++;
		}
	}
	if (c == 0) {
		if (rel[0][n - 1] && t[n - 1] <= 1) return 1;
		return 0;
	}
	if (!rel[0][n - 1]) s--;
	t[n - 1]--;
	if (t[n - 1] > s) return 0;
	int u = bfs();
	if (~u) {
		k -= u;
		if (t[n - 1] * 2 <= k) return 1;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	int _;
	scanf("%d", &_);
	while (_--) {
		scanf("%d%d%d%d", &n, &r, &k, &d);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", x + i, y + i, t + i);
			t[i] = convert(t[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) rel[i][j] = 0;
				else rel[i][j] = (sqr((LL) x[i] - x[j]) + sqr((LL) y[i] - y[j]) <= sqr((LL) r));
			}
		}
		if (work()) puts("YES");
		else puts("NO");
		puts("");
	}
	return 0;
}


