#include <bits/stdc++.h>
using namespace std;

const int N = 111;
int n;
map<string, int> id;
string name[N];

int g[N][N];
vector<int> vec;
int dist[N];
int dp[N];
bool visit[N];

void solve(int len) {
	queue<int> que;
	for (int i = 1; i <= n; i++) dist[i] = 155, dp[i] = 155;
	memset(visit, 0, sizeof(visit));
	dist[1] = len;
	dp[1] = len;
	que.push(1);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int v = 1; v <= n; v++) {
			if (g[u][v]) {
			int t = dist[u] + name[u].length() + 6;
				if (dp[v] > dist[u] || dist[v] > t) {
					dp[v] = min(dp[v], dist[u]);
					dist[v] = min(dist[v], t);
					if (!visit[v]) {
						visit[v] = true;
						que.push(v);
					}
				}
			}
		}
	}
	vector<int> vec;
	for (int i = 1; i <= n; i++) {
		if (dp[i] <= 140) {
			vec.push_back(i);
		}
	}
	cout << vec.size() << endl;
	for (int i = 0; i < vec.size(); i++) {
		cout << name[vec[i]] << endl;
	}
}

int main() {
	//freopen("in_j", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n;
	id.clear();
	string str;
	int tot = 0;
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++) {
		int u = 0, v;
		cin >> str;
		if (id.count(str) == 0) {
			id[str] = ++tot;
			name[tot] = string(str);
		}
		u = id[str];
		int k;
		cin >> k;
		while (k--) {
			cin >> str;
			if (id.count(str) == 0) {
				id[str] = ++tot;
				name[tot] = string(str);
			}
			v = id[str];
			g[u][v] = 1;
		}
	}
	getline(cin, str);
	getline(cin, str);
	//cout << str.length() << endl;
	solve(str.length());
	return 0;
}

