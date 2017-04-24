#include <bits/stdc++.h>
using namespace std;

const int N = 155555;
int mx[N], my[N];
int dx[N], dy[N], dist;
bool visit[N];
int eh[N], tot;
int h, n;
struct Edge {
	int u, v, next;
} et[N * 3];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
	//cout << u << endl;
	Edge e = {u, v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

bool bfs() {
	queue<int> que;
	dist = 1 << 30;
	memset(dx, -1, sizeof(dx));
	memset(dy, -1, sizeof(dy));
	for (int i = 1; i <= n; i++) {
		if (mx[i] == -1) {
			que.push(i);
			dx[i] = 0;
		}
	}
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		if (dx[u] > dist) break;
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (dy[v] == -1) {
				dy[v] = dx[u] + 1;
				if (my[v] == -1) dist = dy[v];
				else {
					dx[my[v]] = dy[v] + 1;
					que.push(my[v]);
				}
			}
		}
	}
	return dist != 1 << 30;
}

bool dfs(int u) {
	for (int i = eh[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (!visit[v] && dy[v] == dx[u] + 1) {
			visit[v] = true;
			if (my[v] != -1 && dy[v] == dist) continue;
			if (my[v] == -1 || dfs(my[v])) {
				my[v] = u, mx[u] = v;
				return true;
			}
		}
	}
	return false;
}

int Match() {
	memset(mx, -1, sizeof(mx));
	memset(my, -1, sizeof(my));
	int cnt = 0;
	while (bfs()) {
		memset(visit, false, sizeof(visit));
		for (int i = 1; i <= n; i++) {
			if (mx[i] == -1 && dfs(i)) cnt++;
		}
	}
	return cnt;
}

pair<int, int> wall[N];

bool equal(int a, int b, int c, int d) {
	return a == c && b == d;
}

int main() {
	while (~scanf("%d%d", &h, &n)) {
		bool found = false;
		int delta = N * 2;
		for (int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			wall[i] = make_pair(a, b);
			if (delta == N * 2) delta = b - a;
			else if (delta != b - a) { found = true; }
		}
		int offset;
		if (delta >= 0) offset = 1 << 30;
		else offset = 0;

		for (int i = 1; i <= n; i++) {
			if (delta >= 0) {
				offset = min(offset, min(wall[i].first, h - wall[i].second));
			} else {
				offset = max(offset, max(wall[i].first, h - wall[i].second));
			}
		}
		if (found) {
			puts("0");
		} else {
			//cout << delta << " " << offset << endl;
			if (delta == 0) {
				int cnt = 0;
				for (int i = 1; i <= n; i++) {
					if (wall[i].first == offset || h - wall[i].first == offset) cnt++;
				}
				if (cnt < n) {
					puts("0");
					continue;
				} else {
					for (int i = 1; i <= n; i++) {
						if (wall[i].first != offset) printf("-");
						printf("%d%c", i, i == n ? '\n' : ' ');
					}
				}
			} else {
				//cout << offset << endl;
				//cout << offset << " " << delta << endl;
				init();
				for (int i = 1; i <= n; i++) {
					//cout << "**********" << endl;
					int a = wall[i].first, b = wall[i].second, u;
					int t = a - offset;
					if (t % delta == 0) {
						u = (a - offset) / delta + 1;
						if (u >= 1 && u <= n) addedge(u, i);
						//cout << u << " " << i << endl;
					}
					t = h - b - offset;
					if (t % delta == 0) {
						u = (h - b - offset) / delta + 1;
						addedge(u, i);
						//cout << u << " " << i << endl;
					}
				}
				int ret = Match();
				if (ret != n) {
					puts("0");
					continue;
				} else {
					for (int i = 1; i <= n; i++) {
						int a = wall[mx[i]].first, b = wall[mx[i]].second;
						if (!equal(offset + (i - 1) * delta, offset + i * delta, a, b)) printf("-");
						printf("%d%c", mx[i], i == n ? '\n' : ' ');
					}
				}
			}
		}
	}
	return 0;
}
