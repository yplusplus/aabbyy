#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
#define fi first
#define se second
const int N = 55555;
int n, m;
int down[N][2], down_id[N][2];
int up[N], up_id[N];
vector<pii> vec[N];
bool visit[N];
int val[N];

void dfs_down(int u, int fa) {
	visit[u] = true;
	memset(down[u], 0, sizeof(down[u]));
	memset(down_id[u], 0, sizeof(down_id[u]));
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].fi;
		if (v == fa) continue;
		dfs_down(v, u);
		int t = down[v][0] + val[v] + vec[u][i].se;
		if (t > down[u][0]) {
			down[u][1] = down[u][0];
			down_id[u][1] = down_id[u][0];
			down[u][0] = t;
			down_id[u][0] = v;
		} else if (t > down[u][1]) {
			down[u][1] = t;
			down_id[u][1] = v;
		}
	}
}

void dfs_up(int u, int fa) {
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].fi;
		if (v == fa) continue;
		int t;
		if (down_id[u][0] == v) t = down[u][1];
		else t = down[u][0];
		up[v] = max(up[u], t) + val[u] + vec[u][i].se;
		dfs_up(v, u);
	}
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n >> m) {
		for (int i = 1; i <= n; i++) {
			vec[i].clear();
			cin >> val[i];
		}
		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			vec[a].push_back(make_pair(b, c));
			vec[b].push_back(make_pair(a, c));
		}
		memset(visit, false, sizeof(visit));
		for (int i = 1; i <= n; i++) {
			if (!visit[i]) {
				dfs_down(i, 0);
				up[i] = 0, up_id[i] = 0;
				dfs_up(i, 0);
			}
		}
		int ans = -1;
		int pos = 0;
		for (int i = 1; i <= n; i++) {
			int t = down[i][0] + max(up[i], down[i][1]) + val[i];
			if (t > ans) ans = t, pos = i;
		}
		dfs_down(pos, 0);
		deque<int> deq;
		deq.push_back(pos);
		int x = down_id[pos][0];
		while (x) {
			deq.push_front(x);
			x = down_id[x][0];
		}
		x = down_id[pos][1];
		while (x) {
			deq.push_back(x);
			x = down_id[x][0];
		}
		cout << ans << endl;
		cout << deq.size() << endl;
		while (!deq.empty()) {
			cout << deq.front();
			deq.pop_front();
			if (deq.empty()) cout << endl;
			else cout << ' ';
		}
	}
}

