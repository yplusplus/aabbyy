#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;
typedef vector<VB> VVB;

VI cost;
VVI path;
const int INF = 1e8;

void work(const VI &tp, int max_id) {
	int n = tp.size(), m = cost.size();
	VVI dist(n + 1, VI(max_id, INF)), ticket(n + 1, VI(max_id));
	VVI px(n + 1, VI(max_id)), py(n + 1, VI(max_id));
	VVB inq(n + 1, VB(max_id, 0));
	queue<int> qx, qy;
	dist[0][tp[0]] = 0;
	qx.push(0);
	qy.push(tp[0]);
	inq[0][tp[0]] = 1;
	while (!qx.empty()) {
		int x, y, nx, ny;
		x = qx.front();
		y = qy.front();
		//cerr << x << ' ' << y << endl;
		qx.pop();
		qy.pop();
		inq[x][y] = 0;
		if (x >= n) continue;
		for (int i = 0; i < m; ++i) {
			if (path[i][0] != y) continue;
			int sz = path[i].size();
			nx = x;
			for (int j = 0; j < sz; ++j) {
				if (nx < n && tp[nx] == path[i][j]) ++nx;
				ny = path[i][j];
				//cerr << "to " << nx << ' ' << ny << endl;
				if (dist[nx][ny] > dist[x][y] + cost[i]) {
					dist[nx][ny] = dist[x][y] + cost[i];
					px[nx][ny] = x;
					py[nx][ny] = y;
					ticket[nx][ny] = i + 1;
					if (inq[nx][ny]) continue;
					qx.push(nx);
					qy.push(ny);
					inq[nx][ny] = 1;
				}
			}
		}
	}
	int t = tp[n - 1];
	cout << "Cost = " << dist[n][t] << endl;
	int x = n, y = t, nx, ny;
	stack<int> ans;
	while (x != 0 || y != tp[0]) {
		ans.push(ticket[x][y]);
		nx = px[x][y], ny = py[x][y];
		x = nx, y = ny;
	}
	cout << "  Tickets used:";
	while (!ans.empty()) {
		cout << ' ' << ans.top();
		ans.pop();
	}
	cout << endl;
}

int run() {
	int n, m, k, cas = 1;
	while (cin >> n && n) {
		cost.resize(n);
		path.resize(n);
		map<int, int> id;
		for (int i = 0; i < n; ++i) {
			cin >> cost[i];
			cin >> k;
			path[i].resize(k);
			for (int j = 0; j < k; ++j) cin >> path[i][j];
			for (int j = 0; j < k; ++j) id[path[i][j]] = 1;
		}
		int tt = -1;
		for (map<int, int>::iterator mi = id.begin(); mi != id.end(); ++mi) mi->second = ++tt;
		for (int i = 0; i < n; ++i) for (int j = 0, sz = path[i].size(); j < sz; ++j) path[i][j] = id[path[i][j]];
		cin >> m;
		for (int i = 1; i <= m; ++i) {
			cin >> k;
			VI trip(k);
			for (int j = 0; j < k; ++j) cin >> trip[j];
			for (int j = 0; j < k; ++j) trip[j] = id[trip[j]];
			cout << "Case " << cas << ", Trip " << i << ": ";
			work(trip, id.size());
		}
		++cas;
	}
	return 0;
}

int main() {
	//freopen("in_a", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
