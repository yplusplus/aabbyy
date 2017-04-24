#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const long long inf = 1LL << 60;
int g[N][N];
map<char, int> mp;
int n;
int type[N];
long long dist[N];
bool visit[N];
int m;

int get_id(char ch) {
	if (mp.count(ch) == 0) mp[ch] = n++;
	if (islower(ch)) type[mp[ch]] = 0;
	else type[mp[ch]] = 1;
	return mp[ch];
}

void solve(int d, char S, char T) {
	int s = mp[S], t = mp[T];
	for (int i = 0; i < n; i++) { dist[i] = inf; }
	queue<int> que;
	que.push(s);
	dist[s] = d;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int v = 0; v < n; v++) {
			if (g[u][v] == 0) continue;
			if (type[u]) {
				//int l = 0, r = 1 << 28;
				long long y = dist[u];
				long long x = (y / 19) * 20;
				if (y % 19 > 0) x += (y % 19) + 1;
				if (dist[v] > x) {
					dist[v] = x;
					if (!visit[v]) {
						visit[v] = true;
						que.push(v);
					}
				}
			} else {
				if (dist[v] > dist[u] + 1) {
					dist[v] = dist[u] + 1;
					if (!visit[v]) {
						visit[v] = true;
						que.push(v);
					}
				}
			}
		}
	}
	printf("%lld\n", dist[t]);
}

int main() {
	int Case = 1;
	while (~scanf("%d", &m)) {
		if (m == -1) break;
		n = 0;
		mp.clear();
		char u[20], v[20];
		memset(g, 0, sizeof(g));
		for (int i = 0; i < m; i++) {
			scanf("%s%s", u, v);
			int uid = get_id(u[0]);
			int vid = get_id(v[0]);
			g[uid][vid] = g[vid][uid] = 1;
		}
		int d;
		scanf("%d%s%s", &d, u, v);
		printf("Case %d: ", Case++);
		solve(d, v[0], u[0]);
	}
	return 0;
}
