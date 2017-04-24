#include <bits/stdc++.h>
using namespace std;

const int N = 25 * 25 * 2 * 500;
const int M = 4888888;
char board[30][30];
int dx[] = {0, 0, 1, -1, 0};
int dy[] = {1, -1, 0, 0, 0};
int n;
int dist[N];
int all;
struct Edge {
	int u, v, cap, flow, next;
} et[M];

int eh[N], tot;
int cur[N], pre[N];

int get_id(int x, int y) { return x * n + y; }
bool inmat(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }
int que[N * 2];

void init() {
	//memset(eh, -1, sizeof(eh));
	for (int i = 0; i < all + 10; i++) {
		eh[i] = -1;
	}
	tot = 0;
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

int aug(int s, int t) {
	for (int i = 0; i < all + n; i++) { dist[i] = -1; }
	int head = 0, tail = 0;
	dist[s] = 0;
	pre[s] = -1;
	que[tail++] = s;
	while (head < tail) {
		int u = que[head++];
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			if (dist[v] == -1 && et[i].cap > et[i].flow) {
				dist[v] = dist[u] + 1;
				pre[v] = i;
				que[tail++] = v;
			}
		}
	}
	if (dist[t] == -1) return 0;
	int x = pre[t];
	while (x != -1) {
		et[x].flow++;
		et[x ^ 1].flow--;
		x = pre[et[x].u];
	}
	return 1;
}

/*
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
*/

int Dinic(int s, int t) {
	int flow = 0;
	while (true) {
		int ret = aug(s, t);
		if (ret == 0) break;
		flow += ret;
	}
	/*
	while (bfs(s, t)) {
		for (int i = 0; i < all; i++) {
			cur[i] = eh[i];
		}
		flow += dfs(s, t, n);
	}
	*/
	return flow;
}

bool check(int mid) {
	all = n * n * (mid + 1) * 2;
	int s = all;
	int t = s + 1;
	all += 2;
	init();
	for (int i = 0; i < n; i++) {
		int u;
		u = get_id(i, 0) * (mid + 1) * 2;
		addedge(s, u, 1);
		u = get_id(i, n - 1) * (mid + 1) * 2;
		addedge(u + mid * 2 + 1, t, 1);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'X') continue;
			int u = get_id(i, j) * (mid + 1) * 2;
			for (int l = 0; l <= mid; l++) {
				addedge(u + l * 2, u + l * 2 + 1, 1);
			}
			for (int k = 0; k < 5; k++) {
				int x = i + dx[k], y = j + dy[k];
				if (!inmat(x, y) || board[x][y] == 'X') continue;
				int v = get_id(x, y) * (mid + 1) * 2;
				for (int l = 0; l < mid; l++) {
					addedge(u + l * 2 + 1, v + (l + 1) * 2, 1);
				}
			}
		}
	}
	return Dinic(s, t) == n;
}

int visit[25][25];
int bfs2(int sx, int sy) {
	memset(visit, -1, sizeof(visit));
	int head = 0, tail = 0;
	visit[sx][sy] = 0;
	que[tail++] = sx;
	que[tail++] = sy;
	while (head < tail) {
		int x = que[head++];
		int y = que[head++];
		if (y == n - 1) return visit[x][y];
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (!inmat(nx, ny) || board[nx][ny] == 'X' || visit[nx][ny] != -1) continue;
			visit[nx][ny] = visit[x][y] + 1;
			que[tail++] = nx;
			que[tail++] = ny;
		}
	}
	return -1;
}

void solve(int Case) {
	int tmp = n * n * n;
	for (int i = 0; i < n; i++) {
		int ret = bfs2(i, 0);
		tmp = min(ret, tmp);
	}
	int l = tmp, r = tmp + n;
	int ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("Case %d: %d\n", Case++, ans);
}

int main() {
	int Case = 1;
	//freopen("in.txt", "r", stdin);
	while (~scanf("%d", &n), n) {
		for (int i = 0; i < n; i++) { scanf("%s", board[i]); }
		solve(Case++);
	}
	return 0;
}
