#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 22;
const int M = 111;
char str[N][M];
bool g[N][N], visit[N], inb[N];
int match[N], pre[N], base[N];
queue<int> que;

int weight[N][N];
int dp[M][M];
int n, m;
int len[N];

int findanc(int u, int v) {
	bool inpath[N];
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
	int anc = findanc(u, v);
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
	for (int i = 1; i <= n; i++) pre[i] = -1, visit[i] = 0, base[i] = i;
	while (!que.empty()) que.pop();
	que.push(s);
	visit[s] = 1;
	while (!que.empty()) {
		int u = que.front(); que.pop();
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
	return false;
}

int Match(int n) {
	memset(match, -1, sizeof(match));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (match[i] == -1 && bfs(i, n)) ans++;
	}
	return ans;
}

int get_weight(char *s, int n, char *t, int m) {
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i] == t[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return n + m - dp[n][m];
}

bool check(int mid) {
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (weight[i][j] <= mid) {
				g[i][j] = 1;
			}
		}
	}
	//cout << "********" << endl;
	//cout << mid << endl;
	int ret = Match(n);
	//cout << ret << endl;
	return ret == n / 2;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		len[i] = strlen(str[i] + 1);
		//cout << i << " " << len[i] << endl;
	}
	//cout << n << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			//cout << i << " " << j;
			weight[i][j] = get_weight(str[i], len[i], str[j], len[j]);
			//cout << " " << weight[i][j] << endl;
		}
	}
	int l = 0, r = 2 * M;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
}

int main() {
	while (~scanf("%d", &n)) {
		n <<= 1;
		for (int i = 1; i <= n; i++) {
			scanf("%s", str[i] + 1);
		}
		solve();
	}
}
