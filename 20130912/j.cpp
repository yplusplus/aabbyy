#pragma comment(linker,"/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
#define ll long long

const int N = 111111;
int eh[N], tot;
int val[N];
ll up[N], down[N];
ll cost_up[N], cost_down[N];
int n;

struct Edge {
	int v, w, next;
} et[N << 1];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void addedge(int u, int v, int w) {
	Edge e = {v, w, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void dfs_down(int u, int fa) {
	cost_down[u] = val[u];
	down[u] = 0;
	for (int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v, w = et[i].w;
		if (v == fa) continue;
		//cout << u << " -> " << v << endl;
		dfs_down(v, u);
		//cout << v << " " << cost_down[v] << endl;
		//cout << v << " " << down[v] << endl;
		cost_down[u] += cost_down[v];
		down[u] += down[v] + cost_down[v] * w;
	}
	//cout << u << " " << down[u] << " " << cost_down[u] << endl;
}

void dfs_up(int u, int fa) {
	//cost_up[u] = 0;
	//up[u] = 0;
	//cout << u << " " << fa << endl;
	for (int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v, w = et[i].w;
		if (v == fa) continue;
		//cout << u << " " << v << " " << w << endl;
		cost_up[v] = cost_up[u] + cost_down[u] - cost_down[v];
		up[v] = up[u] + down[u] - down[v] - cost_down[v] * w + cost_up[v] * w;
		dfs_up(v, u);
	}
}

int main() {
	while (~scanf("%d", &n)) {
		init();
		for (int i = 1; i <= n; i++) {
			scanf("%d", &val[i]);
			down[i] = up[i] = 0;
			cost_down[i] = cost_up[i] = 0;
		}
		for (int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addedge(a, b, c);
			addedge(b, a, c);
		}
		dfs_down(1, 0);
		dfs_up(1, 0);
		ll ans = 1LL << 60;
		//for (int i = 1; i <= n; i++) {
			//cout << i << endl;
			//cout << down[i] << " " << cost_down[i] << " " << up[i] << " " << cost_up[i] << endl;
		//}
		for (int i = 1; i <= n; i++) {
			ans = min(ans, up[i] + down[i]);
		}
		cout << ans << endl;
	}
	return 0;
}

