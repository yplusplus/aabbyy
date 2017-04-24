#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 1111;
const ll inf = 1LL << 60;
int n;
int sqr(int x) { return x * x; }
int get_dist(const pair<int, int> &a, const pair<int, int> &b) {
	return sqr(a.first - b.first) + sqr(a.second - b.second) + abs(a.first - b.second) * abs(a.second - b.first);
}

pair<int, int> point[N];
int fa[N];
bool visit[N];
vector<pair<int, ll> > vec[N];
ll maz[N][N];
ll dist[N];
ll ans;

void dfs(int u, int fa, ll t) {
	ans += t;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (v == fa) continue;
		dfs(v, u, max(t, vec[u][i].second));
	}
}

void solve() {
	memset(visit, false, sizeof(visit));
	memset(fa, -1, sizeof(fa));
	for (int i = 0; i < n; i++) dist[i] = inf;
	dist[0] = 0;
	ll sum = 0;
	while (true) {
		int u = -1;
		for (int i = 0; i < n; i++) {
			if (!visit[i] && (u == -1 || dist[u] > dist[i])) u = i;
		}
		if (u == -1) break;
		visit[u] = true;
		for (int i = 0; i < n; i++) {
			if (!visit[i]) {
				if (maz[u][i] < dist[i]) {
					dist[i] = maz[u][i];
					fa[i] = u;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) vec[i].clear();
	for (int i = 0; i < n; i++) {
		if (fa[i] != -1) {
			//cout << fa[i] << " -> " << i << " " << dist[i] << endl;
			vec[i].push_back(make_pair(fa[i], dist[i]));
			vec[fa[i]].push_back(make_pair(i, dist[i]));
		}
	}
	ans = 0;
	for (int i = 0; i < n; i++) {
		dfs(i, -1, 0);
	}
	ans >>= 1;
	cout << ans << endl;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &point[i].first, &point[i].second);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				maz[i][j] = get_dist(point[i], point[j]);
			}
		}
		solve();
	}
	return 0;
}
