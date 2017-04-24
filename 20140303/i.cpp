#include <bits/stdc++.h>
using namespace std;

map<string, int> mp;
int tot;
const int inf = 333;
const int N = 55;
int g[N][N];
int n, m;
int get_id(string name) {
	if (mp.count(name)) return mp[name];
	return mp[name] = tot++;
}

void floyd() {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j || j == k || i == k) continue;
				if (g[i][k] != -1 && g[k][j] != -1) {
					if (g[i][j] == -1) g[i][j] = g[i][k] + g[k][j];
					else g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
				}
			}
		}
	}
}

char name[111111];
int main() {
	int Case = 1;
	while (~scanf("%d%d", &n, &m), n + m) {
		mp.clear();
		tot = 0;
		memset(g, -1, sizeof(g));
		for (int i = 0; i < m; i++) {
			scanf("%s", name);
			int u = get_id(name);
			scanf("%s", name);
			int v = get_id(name);
			g[u][v] = g[v][u] = 1;
		}
		for (int i = 0; i < N; i++) g[i][i] = 0;
		assert(n >= tot);
		floyd();
		int ans = 0;
		bool found = false;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				assert(g[i][j] == g[j][i]);
				if (g[i][j] == -1) found = true;
				else ans = max(ans, g[i][j]);
			}
		}
		printf("Network %d: ", Case++);
		if (found) puts("DISCONNECTED");
		else printf("%d\n", ans);
		puts("");
	}
	return 0;
}
