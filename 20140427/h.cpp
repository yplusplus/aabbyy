#include <bits/stdc++.h>
using namespace std;

const int N = 222;
queue<int> que;
bool g[N][N];
bool visit[N], inb[N];
int pre[N], base[N], match[N];
int n;

int find_ancestor(int u, int v) {
	bool inpath[N] = {0};
	memset(inpath, false, sizeof(inpath));
	while (1) {
		u = base[u];
		inpath[u] = true;
		if (match[u] == -1) break;
		u = pre[match[u]];
	}
	while (1) {
		v = base[v];
		if (inpath[v]) return v;
		v = pre[match[v]];
	}
}

void reset(int u, int anc) {
	while (u != anc) {
		int v = match[u];
		inb[base[u]] = inb[base[v]] = true;
		v = pre[v];
		if (base[v] != anc) pre[v] = match[u];
		u = v;
	}
}

void contract(int u, int v, int n) {
	int anc = find_ancestor(u, v);
	memset(inb, 0, sizeof(inb));
	reset(u, anc), reset(v, anc);
	if (base[u] != anc) pre[u] = v;
	if (base[v] != anc) pre[v] = u;
	for (int i = 1; i <= n; i++) {
		if (inb[base[i]]) {
			base[i] = anc;
			if (!visit[i]) {
				que.push(i);
				visit[i] = 1;
			}
		}
	}
}

bool bfs(int s, int n) {
	for (int i = 0; i <= n; i++) { pre[i] = -1, visit[i] = 0, base[i] = i; }
	while (!que.empty()) que.pop();
	que.push(s);
	visit[s] = 1;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int v = 1; v <= n; v++) {
			if (g[u][v] && base[v] != base[u] && match[u] != v) {
				if (v == s || (match[v] != -1 && pre[match[v]] != -1)) contract(u, v, n);
				else if (pre[v] == -1) {
					pre[v] = u;
					if (match[v] != -1) que.push(match[v]), visit[match[v]] = 1;
					else {
						u = v;
						while (u != -1) {
							v = pre[u];
							int w = match[v];
							match[u] = v;
							match[v] = u;
							u = w;
						}
						return true;
					}
				}
			}
		}
	}
}

int Match(int n) {
	memset(match, -1, sizeof(match));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (match[i] == -1 && bfs(i, n)) {
			ans++;
		}
	}
	return ans;
}

int main() {
	freopen("perfect.in", "r", stdin);
	freopen("perfect.out", "w", stdout);
	while (cin >> n) {
		bool a[N][N];
		memset(a, 0, sizeof(a));
		memset(g, 0, sizeof(g));
		for (int i = 1, cnt, x; i <= n; i++) {
			cin >> cnt;
			for (int j = 0; j < cnt; j++) {
				cin >> x;
				a[i][x] = true;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				g[i][j] = a[i][j] & a[j][i];
			}
		}
		int ret = Match(n);
		//cout << ret << endl;
		puts(ret * 2 == n ? "YES" : "NO");
	}
	return 0;
}
