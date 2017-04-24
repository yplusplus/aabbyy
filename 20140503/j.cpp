#include <bits/stdc++.h>
using namespace std;

const int N = 222;
const int M = 1111;
int n, m, t;
vector<pair<int, int> > vec[N];
bool terminal[N];
int ans[M];
int path[M], tot;
int suffix[M][M];
int len;

void dfs(int u) {
	if (terminal[u] && tot) {
		len = max(len, tot);
		for (int i = 1; i <= tot; i++) {
			suffix[tot][i] = path[tot - i];
		}
	}
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		path[tot++] = vec[u][i].second;
		dfs(v);
		tot--;
	}
}

int main() {
	freopen("suffix.in", "r", stdin);
	freopen("suffix.out", "w", stdout);
	ios::sync_with_stdio(false);
	while (cin >> n >> m >> t) {
		memset(terminal, 0, sizeof(terminal));
		for (int i = 0, x; i < t; i++) {
			cin >> x;
			terminal[x] = true;
		}
		for (int i = 0; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			vec[u].push_back(make_pair(v, i));
		}
		int alloc = 0;
		len = tot = 0;
		dfs(1);
		memset(ans, -1, sizeof(ans));
		//for (int i = 1; i <= len; i++) { for (int j = 1; j <= i; j++) { cout << suffix[i][j] << " "; } cout << endl; }
		for (int i = 1; i <= len; i++) {
			int tmp = -1;
			for (int j = i; j <= len; j++) {
				if (ans[suffix[j][i]] != -1) {
					assert(tmp == -1 || tmp == ans[suffix[j][i]]);
					tmp = ans[suffix[j][i]];
				}
			}
			if (tmp == -1) tmp = ++alloc;
			for (int j = i; j <= len; j++) {
				ans[suffix[j][i]] = tmp;
			}
			//cout << i << " " << tmp << endl;
		}
		cout << len << " " << alloc << endl;
		for (int i = 1; i <= len; i++) {
			cout << ans[suffix[len][len + 1 - i]] << " ";
		}
		cout << endl;
		for (int i = 0; i < m; i++) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
