#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

const int N = 151;
const int M = 4444;
int eh[N], tot;
int dist[N], cur[N];
int n, m, k;
struct Edge {
	int u, v;
	long long cap, flow;
	int next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, long long cap, long long flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, long long cap) {
	add(u, v, cap, 0), add(v, u, cap, 0);
}

bool bfs(int s, int t) {
	queue<int> que;
	que.push(s);
	memset(dist, -1, sizeof(dist));
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (dist[v] == -1 && et[i].cap > et[i].flow) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

long long dfs(int u, int t, long long d) {
	if (u == t) return d;
	long long l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (dist[v] == dist[u] + 1 && et[i].cap > et[i].flow) {
			long long tmp = dfs(v, t, min(l, 0LL + et[i].cap - et[i].flow));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

long long Dinic(int s, int t) {
	long long res = 0;
	while (bfs(s, t)) {
		memcpy(cur, eh, sizeof(cur));
		res += dfs(s, t, 1LL << 60);
	}
	return res;
}

vector<pair<int, pair<int, int> > > edge;
void solve() {
    edge.clear();
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--, b--;
        edge.push_back(make_pair(c, make_pair(a, b)));
    }
    if(n == 1) {
        cout << 0 << endl;
        return ;
    }
    sort(edge.begin(), edge.end());
    reverse(edge.begin(), edge.end());
    long long ans = 1LL << 60;
    for (int mask = 0; mask < 1 << n; mask++) {
        if (mask & 1) continue;
        if (~mask >> (n - 1) & 1) continue;
        int cnt = k;
        init();
        for (int i = 0; i < m; i++) {
            int a = edge[i].second.first, b = edge[i].second.second;
            if (cnt && ((mask >> a & 1) ^ (mask >> b & 1))) cnt--;
            else {
                addedge(a, b, edge[i].first);
            }
        }
        ans = min(ans, Dinic(0, n - 1));
    }
	cout << ans << endl;
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &k)) {
		solve();
	}
	return 0;
}


