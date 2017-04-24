#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
const int N = 111111;
const int M = N << 1;
const int inf = 1 << 25;
pair<int, int> edge[M];
int n, m;
int deg[N], root;
bool f[N], g[N];
int brother[N];

int calc(int a) {
	if (f[a]) return 1;
	if (g[a] && f[brother[a]]) return 2;
	return inf;
}

void solve() {
	char cmd[15];
	int a, b, x;
	while (~scanf("%s", cmd)) {
		if (cmd[0] == 'D') {
			scanf("%d", &x);
			int a = edge[x].fi, b = edge[x].se;
			if (a == root) f[b] = 0;
			else if (b == root) f[a] = 0;
			else g[a] = g[b] = 0;
		} else {
			scanf("%d%d", &a, &b);
			if (a == b) {
				puts("0");
				continue;
			}
			int ans = inf;
			if (a == root) ans = min(ans, calc(b));
			else if (b == root) ans = min(ans, calc(a));
			else ans = min(ans, calc(a) + calc(b));
			if (brother[a] == b && g[a]) ans = 1;
			if (ans == inf) ans = -1;
			printf("%d\n", ans);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	memset(deg, 0, sizeof(deg));
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		edge[i] = make_pair(a, b);
		deg[a]++, deg[b]++;
	}
	memset(f, true, sizeof(f));
	memset(g, true, sizeof(g));
	deg[0] = root = 0;
	for (int i = 1; i <= n; i++) {
		if (deg[i] > deg[root]) root = i;
	}
	for (int i = 1; i <= m; i++) {
		if (edge[i].fi != root && edge[i].se != root) {
			int a = edge[i].fi, b = edge[i].se;
			brother[a] = b;
			brother[b] = a;
		}
	}
	solve();
	return 0;
}