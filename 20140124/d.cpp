#include <bits/stdc++.h>
using namespace std;

const int N = 5555;
typedef vector<int> VI;

struct Graph {
	VI nx[N], lk[N];
	int dis[N], m;
	bool vis[N];
	void init(int _) {
		m = _;
		for (int i = 1; i <= m; i++) nx[i].clear();
		for (int i = 1; i <= m; i++) lk[i].clear();
	}
	void addnx(int u, int v) { nx[u].push_back(v); }
	void addlk(int u, int v) { lk[u].push_back(v); }
	void spfa() {
		for (int i = 1; i <= m; i++) vis[i] = 0;
		for (int i = 1; i <= m; i++) dis[i] = N << 1;
		queue<int> q;
		dis[1] = 0;
		q.push(1);
		vis[1] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (VI::iterator vi = nx[u].begin(); vi != nx[u].end(); vi++) {
				int v = *vi;
				if (dis[v] > dis[u] + 1) {
					dis[v] = dis[u] + 1;
					if (vis[v]) continue;
					q.push(v);
					vis[v] = 1;
				}
			}
			for (VI::iterator vi = lk[u].begin(); vi != lk[u].end(); vi++) {
				int v = *vi;
				if (dis[v] > dis[u] + 2) {
					dis[v] = dis[u] + 2;
					if (vis[v]) continue;
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
} go, back;

VI rel[N];
int dep[N];

void init(int n) { for (int i = 1; i <= n; i++) rel[i].clear(); }
void addrel(int u, int v) {
	//cout << u << ' ' << v << endl;
	rel[u].push_back(v);
}

void dfs(int u, int d) {
	dep[u] = d;
	for (VI::iterator vi = rel[u].begin(); vi != rel[u].end(); vi++) {
		dfs(*vi, d + 1);
	}
}

const int M = 111111;
char buf[M];
map<string, int> id;

int find(const string &a) {
	//cout << a << endl;
	if (id.find(a) != id.end()) return id[a];
	int k = (id[a] = id.size());
	return k;
}

char tmp[66];
int get(const string &s) {
	strcpy(tmp, s.c_str());
	if (tmp[4] == ':') {
		tmp[4] = 0;
		if (strcmp(tmp, "Link") == 0) return -find(tmp + 5);
		tmp[4] = ':';
	}
	return find(tmp);
}

int main() {
	//freopen("in", "r", stdin);
	int a, b, n;
	while (~scanf("%d%d%d", &a, &b, &n)) {
		gets(buf);
		go.init(n);
		back.init(n);
		id.clear();
		init(n);
		for (int i = 1; i <= n; i++) {
			gets(buf);
			vector<string> name;
			char *p = strtok(buf, " ");
			while (p) {
				name.push_back(p);
				p = strtok(0, " ");
			}
			int sz = name.size();
			int u = find(name[0]);
			//cout << u << ':';
			for (int j = 1; j < sz; j++) {
				int v = get(name[j]);
				//cout << v << ' ';
				if (v > 0) {
					go.addlk(u, v);
					go.addnx(v, u);
					back.addlk(v, u);
					back.addnx(u, v);
					addrel(u, v);
				} else {
					v = -v;
					go.addlk(u, v);
					back.addlk(v, u);
				}
			}
			//cout << endl;
			//cout << name.size() << endl;
		}
		go.spfa();
		back.spfa();
		dfs(1, 0);
		int ans = 0;
		a *= b;
		for (int i = 1; i <= n; i++) {
			if (go.dis[i] + back.dis[i] <= a) ans = max(dep[i], ans);
			//cout << i << ' ' << dep[i] << ' ' << go.dis[i] << ' ' << back.dis[i] << endl;
		}
		printf("%d\n", ans);
	}
	return 0;
}
