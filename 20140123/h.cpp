#include <bits/stdc++.h>
using namespace std;

const int N = 555;
vector<int> vec[N];
int n, m;
int node_cnt, edge_cnt;
bool visit[N];

void dfs(int u) {
	visit[u] = true;
	node_cnt++;
	edge_cnt += vec[u].size();
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (!visit[v]) dfs(v);
	}
}

int main() {
	int Case = 1;
	while (~scanf("%d%d", &n, &m), n + m) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			vec[a].push_back(b);
			vec[b].push_back(a);
		}
		memset(visit, false, sizeof(visit));
		int tree_cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (!visit[i]) {
				node_cnt = edge_cnt = 0;
				dfs(i);
				edge_cnt >>= 1;
				if (edge_cnt + 1 == node_cnt) tree_cnt++;
			}
		}
		printf("Case %d: ", Case++);
		if (tree_cnt == 0) puts("No trees.");
		else if (tree_cnt == 1) puts("There is one tree.");
		else printf("A forest of %d trees.\n", tree_cnt);
	}
	return 0;
}
