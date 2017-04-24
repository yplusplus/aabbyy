#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int inf = 1 << 30;

const int N = 222;
const int M = 222222;
int eh[N], tot;
int n, m, k, dig;

struct Edge {
	int u, v, next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void addedge(int u, int v) {
	Edge e = {u, v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

bool visit[N];
int match[N];
bool dfs(int u) {
	for (int i = eh[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (visit[v]) continue;
		visit[v] = true;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int Match() {
	int cnt = 0;
	memset(match, -1, sizeof(match));
	for (int i = 1; i <= n; i++) {
		memset(visit, false, sizeof(visit));
		if (dfs(i)) cnt++;
	}
	return cnt;
}

int ti[N][N];

bool check(int mid) {
	init();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (ti[i][j] + dig <= mid) addedge(i, j);
			if (ti[i][j] <= mid) addedge(i, m + j);
		}
	}
	return Match() >= k;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &n, &m, &k, &dig);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &ti[i][j]);
			}
		}
		int l = 0, r = 22222222;
		int ans = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}

