#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int mx[N], my[N];
int dx[N], dy[N], dist;
vector<int> vec[N];
bool visit[N];
int in[N], insz;
int out[N], outsz;
int a, b, n;

bool bfs() {
	queue<int> que;
	dist = 1 << 30;
	memset(dx, -1, sizeof(dx));
	memset(dy, -1, sizeof(dy));
	for (int i = 0; i < insz; i++) {
		if (mx[i] == -1) {
			que.push(i);
			dx[i] = 0;
		}
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		if (dx[u] > dist) break;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i];
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
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
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
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < insz; i++) {
			if (mx[i] == -1 && dfs(i)) cnt++;
		}
	}
	return cnt;
}

void solve() {
	if (insz != outsz) {
		puts("Liar");
		return;
	}
	for (int i = 0; i < insz; i++) {
		for (int j = 0; j < outsz; j++) {
			if (in[i] > out[j]) continue;
			int delta = out[j] - in[i];
			if (!(delta < a && delta > b)) {
				vec[i].push_back(j);
				//cout << i << " -> " << j << endl;
			}
		}
	}
	int ret = Match();
	if (ret < insz) {
		puts("Liar");
		return;
	} else {
		puts("No reason");
		for (int i = 0; i < insz; i++) {
			cout << in[i] << " " << out[mx[i]] << endl;
		}
	}
}

int main() {
	while (~scanf("%d%d", &a, &b)) {
		scanf("%d", &n);
		insz = outsz = 0;
		for (int i = 0; i < n; i++) {
			vec[i].clear();
		}
		for (int i = 0; i < n; i++) {
			int ti, type;
			scanf("%d%d", &ti, &type);
			if (type) out[outsz++] = ti;
			else in[insz++] = ti;
		}
		solve();
	}
}
