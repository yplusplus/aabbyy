#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <functional>
using namespace std;

const int N = 111;
int g[N][N], h[N][N];
int n;
struct Node {
	int id, d;
	Node(int id, int d) : id(id), d(d) {}
	Node() {}
	bool operator < (const Node &x) const {
		return d > x.d;
	}
} node[N];

bool check() {
	for (int i = 0; i < n; i++) {
		sort(node + i, node + n);
		int d = node[i].d;
		for (int j = i + 1; j < n && d; j++, d--) {
			if (--node[j].d < 0) return false;
			g[node[i].id][node[j].id] = g[node[j].id][node[i].id] = 1;
		}
		if (d) return false;
	}
	return true;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			int d;
			scanf("%d", &d);
			node[i] = Node(i, d);
		}
		memset(g, 0, sizeof(g));
		if (!check()) puts("IMPOSSIBLE");
		else {
			memset(h, -1, sizeof(h));
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) continue;
					for (int k = 0; k < n; k++) {
						if (k == i || k == j) continue;
						if (g[i][k] && !g[k][j]) {
							h[i][j] = k;
							break;
						}
					}
				}
			}
			bool found = false;
			int a, b, c, d;
			for (int i = 0; i < n && !found; i++) {
				for (int j = 0; j < n && !found; j++) {
					if (h[i][j] != -1 && h[j][i] != -1) {
						found = true;
						a = i, b = j;
						c = h[i][j], d = h[j][i];
					}
				}
			}
			vector<pair<int, int> > edge;
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (g[i][j]) edge.push_back(make_pair(i, j));
				}
			}
			int m = edge.size();
			if (!found) {
				puts("UNIQUE");
				printf("%d %d\n", n, m);
				for (int i = 0; i < m; i++) {
					printf("%d%c", edge[i].first + 1, i == m - 1 ? '\n' : ' ');
				}
				if (!m) puts("");
				for (int i = 0; i < m; i++) {
					printf("%d%c", edge[i].second + 1, i == m - 1 ? '\n' : ' ');
				}
				if (!m) puts("");
			} else {
				puts("MULTIPLE");
				vector<pair<int, int> > edge2;
				for (int i = 0; i < m; i++) {
					if (edge[i] == make_pair(a, c) || edge[i] == make_pair(c, a)) edge2.push_back(make_pair(b, c));
					else if (edge[i] == make_pair(b, d) || edge[i] == make_pair(d, b)) edge2.push_back(make_pair(a, d));
					else edge2.push_back(edge[i]);
				}
				printf("%d %d\n", n, m);
				for (int i = 0; i < m; i++) {
					printf("%d%c", edge[i].first + 1, i == m - 1 ? '\n' : ' ');
				}
				for (int i = 0; i < m; i++) {
					printf("%d%c", edge[i].second + 1, i == m - 1 ? '\n' : ' ');
				}
				printf("%d %d\n", n, m);
				for (int i = 0; i < m; i++) {
					printf("%d%c", edge2[i].first + 1, i == m - 1 ? '\n' : ' ');
				}
				for (int i = 0; i < m; i++) {
					printf("%d%c", edge2[i].second + 1, i == m - 1 ? '\n' : ' ');
				}
			}
		}
	}
	return 0;
}
