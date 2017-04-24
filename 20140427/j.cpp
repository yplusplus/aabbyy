#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 9;
typedef long long LL;
typedef pair<LL, int> PLI;
typedef pair<PLI, int> Node;
#define x first
#define y second
PLI operator - (const PLI &a) { return PLI(-a.x, -a.y); }
vector<int> nx[N], d[N];
PLI mat[N][N];
bool confirm[N];

void spfa(int x, PLI *const dist) {
	priority_queue<Node> q;
	memset(confirm, 0, sizeof confirm);
	for (int i = 0; i < N; ++i) dist[i].x = LLONG_MAX;
	dist[x] = PLI(0, 0);
	q.push(Node(-dist[x], x));
	while (!q.empty()) {
		int x = q.top().y;
		q.pop();
		if (confirm[x]) continue;
		confirm[x] = 1;
		for (int i = 0, sz = nx[x].size(); i < sz; ++i) {
			int y = nx[x][i], dt = d[x][i];
			PLI temp(dist[x].x + dt, dist[x].y + 1);
			if (temp < dist[y]) {
				dist[y] = temp;
				q.push(Node(-dist[y], y));
			}
		}
	}
}

int run() {
	int n, m;
	int x, y, z;
	while (cin >> n >> m) {
		for (int i = 1; i <= n; ++i) nx[i].clear();
		for (int i = 0; i < m; ++i) {
			cin >> x >> y >> z;
			nx[x].push_back(y);
			d[x].push_back(z);
			nx[y].push_back(x);
			d[y].push_back(z);
		}
		for (int i = 1; i <= n; ++i) {
			spfa(i, mat[i]);
		}
		double ans = 0;
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				ans += mat[i][j].y;
				++cnt;
			}
		}
		cout << (ans / cnt) << endl;
	}
	return 0;
}

int main() {
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
	cout << setiosflags(ios::fixed) << setprecision(10);
	ios::sync_with_stdio(0);
	return run();
}
