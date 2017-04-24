#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1111;
const int M = 222222;
int eh[N], tot;
int eh2[N], tot2;
int cur[N];
int dist[N], n, m;
struct Edge {
	int u, v, cap, flow, t, next;
} et[M], et2[M];

void init() {
	memset(eh, -1, sizeof(eh));
	memset(eh2, -1, sizeof(eh2));
	tot = tot2 = 0;
}

void add(int u, int v, int cap, int flow, int t, Edge et[], int eh[], int &tot) {
	//cout << eh << " " << eh << endl;
	Edge e = {u, v, cap, flow, t, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

bool bfs(int s, int t) {
	queue<int> que;
	memset(dist, -1, sizeof(dist));
	que.push(s);
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
			if (et[i].cap > et[i].flow && dist[et[i].v] == -1) {
				dist[et[i].v] = dist[u] + 1;
				que.push(et[i].v);
			}
		}
	}
	return dist[t] != -1;
}

int dfs(int u, int t, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
			int tmp = dfs(v, t, min(l, et[i].cap - et[i].flow));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

int Dinic(int s, int t) {
	int flow = 0;
	//cout << bfs(s, t) << endl;
	while (bfs(s, t)) {
		//cout << "##########" << endl;
		for (int i = 0; i < n; i++) cur[i] = eh[i];
		flow += dfs(s, t, 1 << 30);
		//cout << "##########" << endl;
	}
	return flow;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < m; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			add(a, b, c, 0, d, et, eh, tot);
			add(b, a, d ? c : 0, 0, d, et, eh, tot);
		}
		int tmp = Dinic(0, n - 1);
		//cout << tmp << endl;
		/*
		for (int i = 0; i < n; i++) {
			cout << i << " " << dist[i] << endl;
		}
		*/
		for (int i = 0; i < tot; i += 2) {
			int a = et[i].u, b = et[i].v;
			if (et[i].t) {
				if (et[i].cap == et[i].flow || et[i + 1].cap == et[i + 1].flow) {
					add(et[i].u, et[i].v, 1, 0, et[i].t, et2, eh2, tot2);
					add(et[i].v, et[i].u, 1, 0, et[i].t, et2, eh2, tot2);
				} else {
					add(et[i].u, et[i].v, 2 * n, 0, et[i].t, et2, eh2, tot2);
					add(et[i].v, et[i].u, 2 * n, 0, et[i].t, et2, eh2, tot2);
				}
			} else {
				if (et[i].cap == et[i].flow) {
					add(et[i].u, et[i].v, 1, 0, et[i].t, et2, eh2, tot2);
					add(et[i].v, et[i].u, 0, 0, et[i].t, et2, eh2, tot2);
				} else {
					add(et[i].u, et[i].v, 2 * n, 0, et[i].t, et2, eh2, tot2);
					add(et[i].v, et[i].u, 0, 0, et[i].t, et2, eh2, tot2);
				}
			}
			/*
			//cout << a << " " << b << " " << et[i].cap << " " << et[i].flow << endl;
			if (dist[a] != dist[b] && (dist[a] == -1 || dist[b] == -1)) {
			if (et[i].t) {
			ans += et[i].flow == et[i].cap;
			} else {
			ans += (et[i].flow == et[i].cap || et[i + 1].flow == et[i + 1].cap);
			}
			}
			//ans += (dist[a] >= 0 && dist[b] == -1);
			 */
		}
		memcpy(eh, eh2, sizeof(eh2));
		memcpy(et, et2, sizeof(et2));
		printf("Case %d: %d\n", Case++, Dinic(0, n - 1));
	}
	return 0;

}

