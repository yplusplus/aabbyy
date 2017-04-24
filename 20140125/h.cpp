nclude <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 100010;
const int M = 888888;
const int inf = 1 << 25;
int bit[1 << 18];

vector<int> vec[N];
int eh[N], tot, cur[N], dist[N], pre[N];
int color[N];
vector<int> vv;
struct Edge {
	int u, v, cap, cost, flow, next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int cost, int flow) {
	Edge e = {u, v, cap, cost, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap, int cost) {
	add(u, v, cap, cost, 0), add(v, u, 0, -cost, 0);
}

bool bfs(int s, int t) {
	queue<int> que;
	for (int i = 0; i < vv.size(); i++) dist[vv[i]] = -1;
	dist[t] = -1;
	dist[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

int dfs(int u, int t, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap > et[i].flow && dist[u] + 1 == dist[v]) {
			int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

int Dinic(int s, int t) {
	int res = 0;
	while (bfs(s, t)) {
		for (int i = 0; i < vv.size(); i++) cur[vv[i]] = eh[vv[i]];
		res += dfs(s, t, 1 << 25);
	}
	return res;
}

void find_color(int u, int c) {
	color[u] += c;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (~color[v] & c) find_color(v, c);
	}
}

void solve(int A, int B) {
	memset(color, 0, sizeof(color));
	find_color(A, 1);
	find_color(B, 2);
	int S = 0;
	vv.clear();
	for (int i = A; i <= B; i++) { if (color[i] == 3) vv.push_back(i); }
	vv.push_back(S);
	init();
	for (int i = 0; i < vv.size(); i++) {
		for (int j = 0; j < vec[vv[i]].size(); j++) {
			int u = vv[i], v = vec[vv[i]][j];
			if (u > v) continue;
			if (u >= A && v <= B && color[u] == 3 && color[v] == 3) {
				addedge(u, v, 1, 1);
			}
		}
	}
	addedge(S, A, 150, 0);
	int ret = Dinic(S, B);
	cout << ret << endl;
}

int main() {
	bit[0] = 0;
	for (int i = 1; i < 1 << 18; i++) { bit[i] = bit[i >> 1] + (i & 1); }
	vector<int> node;
	for(int i = 50001; i < N; i ++) if (bit[i] > 11) node.push_back(i);
	for (int i = 0; i < node.size(); i++) {
		for (int j = i + 1; j < node.size(); j++) {
			int u = node[i], v = node[j];
			if (bit[u & v] > 11 && (u & v) % 2 == 0 && (u & v) > 50000) {
				vec[u].push_back(v);
				vec[v].push_back(u);
			}
		}
	}
	int A, B;
	while (~scanf("%d%d", &A, &B)) {
		if (B < A) cout << 0 << endl;
		else if (A == B) cout << 150 << endl;
		else solve(A, B);
	}
	return 0;
}
