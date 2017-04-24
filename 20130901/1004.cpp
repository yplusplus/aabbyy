#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define fi first
#define se second
#define mp make_pair
const int N = 30;
const int M = 11111;
const int inf = 1 << 30;
int in[N], out[N];
int eh[N], low[N], dist[N], pre[N], cur[N], tot, cnt[N];

struct Edge {
	int u, v, cap, flow, next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	assert(u >= 0 && u <= 27);
	assert(v >= 0 && v <= 27);
	add(u, v, cap, 0), add(v, u, 0, 0); 
}

int isap(int s, int t, int n) {
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(dist));
	for (u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = inf, cnt[0] = n, u = s;
	while (dist[s] < n) {

		for (now = cur[u]; now != -1; now = et[now].next) 
			if (et[now].cap > et[now].flow && dist[u] == dist[v = et[now].v] + 1) break;
		if (now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(low[u], et[now].cap - et[now].flow);
			u = v;
			if (u == t) {
				for (; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += low[t];
					et[pre[u] ^ 1].flow -= low[t];
				}
				flow += low[t];
				low[s] = inf;
			}
		} else {
			if (--cnt[dist[u]] == 0) break;
			dist[u] = n, cur[u] = eh[u];
			for (now = eh[u]; now != -1; now = et[now].next) {
				if (et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1) dist[u] = dist[et[now].v] + 1;

			}
			cnt[dist[u]]++;
			if (u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

int number;
pair<pair<int, int>, int> words[1111];
char str[30];
bool used[30];
int fa[30];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	fa[a] = b;
	return true;
}

bool solve() {
	int s = 26, t = 27;
	for (int i = 0; i < 26; i++) {
		if (abs(in[i] - out[i]) & 1) return false;
	}
	for (int i = 0; i < 26; i++) {
		if (in[i] >= out[i]) addedge(i, t, (in[i] - out[i]) / 2);
		else addedge(s, i, (out[i] - in[i]) / 2);
	}
	int flow = isap(s, t, 28);
	for (int i = eh[s]; i != -1; i = et[i].next) {
		if (et[i].cap != et[i].flow) return false;
	}
	return true;
}

void build(int a, int b) {
	init();
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	out[a]++, in[b]++;
	addedge(a, b, 1);
	for (int i = 0; i < number; i++) {
		out[words[i].fi.fi]++, in[words[i].fi.se]++;
		if (words[i].se) {
			addedge(words[i].fi.fi, words[i].fi.se, 1);
		}
	}
}

int main() {
	int T, Case = 1;
	cin >> T;
	while (T--) {
		scanf("%d", &number);
		memset(used, false, sizeof(used));
		for (int i = 0; i < 26; i++) fa[i] = i;
		for (int i = 0; i < number; i++) {
			int flag;
			scanf("%s%d", str, &flag);
			int len = strlen(str);
			int a = str[0] - 'a', b = str[len - 1] - 'a';
			words[i] = mp(mp(a, b), flag);
			used[a] = used[b] = true;
			Union(a, b);
		}
		int cnt = 0;
		for (int i = 0; i < 26; i++) {
			if (used[i] && fa[i] == i) cnt++;
		}
		printf("Case %d: ", Case++);
		if (cnt > 1) {
			puts("Poor boy!");
		} else {
			bool found = false;
			if (number == 1) found = true;
			for (int i = 0; i < 26 && !found; i++) {
				if (!used[i]) continue;
				for (int j = i; j < 26; j++) {
					if (!used[j]) continue;
					build(i, j);
					//cout << i << " " << j << endl;
					if (solve()) {
						found = true;
						break;
					}
				}
			}
			puts(found ? "Well done!" : "Poor boy!");
		}
	}
	return 0;
}

