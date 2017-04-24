#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
const int N = 55555;
int rmq[N * 2][20], rn;
int pos[N], B[N * 2], F[N * 2];
vector<pii> vec[N];
int dist[N];
int n;
void dfs(int u, int fa, int dep, int w) {
	F[++rn] = u, B[rn] = dep, pos[u] = rn;
	dist[u] = w;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (v == fa) continue;
		dfs(v, u, dep + 1, w + vec[u][i].second);
		F[++rn] = u, B[rn] = dep;
	}
}

void init_RMQ() {
	for (int i = 1; i <= rn; i++) rmq[i][0] = i;
	for (int j = 1; (1 << j) <= rn; j++) {
		for (int i = 1; i + (1 << j) - 1 <= rn; i++) {
			int a = rmq[i][j - 1], b = rmq[i + (1 << (j - 1))][j - 1];
			if (B[a] < B[b]) rmq[i][j] = a;
			else rmq[i][j] = b;
		}
	}
}

int RMQ(int a, int b) {
	int k = log(1.0 + b - a) / log(2.0);
	int u = rmq[a][k], v = rmq[b - (1 << k) + 1][k];
	if (B[u] < B[v]) return F[u];
	else return F[v];
}

int LCA(int a, int b) {
	a = pos[a], b = pos[b];
	if (a > b) return RMQ(b, a);
	else return RMQ(a, b);
}

int main() {
	int flag = false;
	while (~scanf("%d", &n)) {
		if (flag) puts("");
		else flag = true;
		rn = 0;
		for (int i = 0; i < n; i++) vec[i].clear();
		for (int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(make_pair(b, c));
			vec[b].push_back(make_pair(a, c));
		}
		dfs(0, -1, 0, 0);
		init_RMQ();
		int q, a, b, c;
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d%d", &a, &b, &c);
			int ans = 0;
			int ablca = LCA(a, b);
			int aclca = LCA(a, c);
			int bclca = LCA(b, c);
			int lca = LCA(ablca, c);
			ans += dist[a] + dist[b] + dist[c] - 3 * dist[lca];
			if (ablca != lca) ans -= dist[ablca] - dist[lca];
			if (bclca != lca) ans -= dist[bclca] - dist[lca];
			if (aclca != lca) ans -= dist[aclca] - dist[lca];
			printf("%d\n", ans);
		}
	}
	return 0;
}
