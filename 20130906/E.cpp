#include <iostream>
#include <cstdio>
#include <cstring> 
#include <queue>
#include <vector>
using namespace std;

const int N = 3333;
const int M = 77777;
int eh[N], tot;
vector<int> vec[N];
vector<int> protect[N];
vector<pair<int, int> > rev[N];
struct Edge {
	int u, v, w, next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void addedge(int u, int v, int w) {
	Edge e = {u, v, w, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

bool visit[N];
long long dp[N];
int n, m;
long long spfa() {
	queue<int> que;
	for (int i = 1; i <= n; i++) dp[i] = 1LL << 60;
	dp[1] = 0;
	que.push(1);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		//cout << "now node = " << u << " " << dp[u] << endl;
		visit[u] = false;
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, w = et[i].w;
			long long t = 0;
			for (int j = 0; j < vec[v].size(); j++) t = max(t, dp[vec[v][j]]);
			t = max(t, dp[u] + w);
			if (dp[v] > t) {
				dp[v] = t;
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
		//u
		for (int i = 0; i < protect[u].size(); i++) {
			int v = protect[u][i];
			//if (visit[v]) continue;
			long long t = 0, tt = 1LL << 60;
			for (int j = 0; j < vec[v].size(); j++) t = max(t, dp[vec[v][j]]);
			for (int j = 0; j < rev[v].size(); j++) {
				tt = min(tt, dp[rev[v][j].first] + rev[v][j].second);
			}
			t = max(t, tt);
			if (dp[v] > t) {
				dp[v] = t;
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	return dp[n];
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		scanf("%d%d", &n, &m);
		init();
		for (int i = 1; i <= n; i++) vec[i].clear(), protect[i].clear(), rev[i].clear();
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
			rev[v].push_back(make_pair(u, w));
		}
		for (int i = 1; i <= n; i++) {
			int k, x;
			scanf("%d", &k);
			while (k--) {
				scanf("%d", &x);
				vec[i].push_back(x);
				protect[x].push_back(i);
			}
		}
		cout << spfa() << endl;
	}
	return 0;
}