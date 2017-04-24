#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> V2I;

V2I nx;
VI in_arc, ans, tmp;

void init(int n) {
	nx.clear();
	in_arc.clear();
	nx.resize(n + 1);
	in_arc.resize(n + 1);
	ans.clear();
}

bool topoSort(int n) {
	priority_queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (in_arc[i]) continue;
		q.push(i);
	}
	int cnt = 0, cur;
	while (!q.empty()) {
		cur = q.top();
		q.pop();
		++cnt;
		ans.push_back(cur);
		for (int i = 0, sz = nx[cur].size(); i < sz; ++i) {
			int y = nx[cur][i];
			if (--in_arc[y] == 0) {
				q.push(y);
			}
		}
	}
	return cnt == n;
}

int run() {
	int _, n, m;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> n >> m;
		init(n);
		int x, y;
		for (int i = 0; i < m; ++i) {
			cin >> x >> y;
			nx[y].push_back(x);
			++in_arc[x];
		}
		if (topoSort(n)) {
			reverse(ans.begin(), ans.end());
			tmp.resize(n);
			for (int i = 0; i < n; ++i) tmp[i] = ans[i];
			for (int i = 0; i < n; ++i) ans[tmp[i] - 1] = i + 1;
			for (int i = 0; i < n; ++i) {
				if (i) cout.put(' ');
				cout << ans[i];
			}
			cout << endl;
		} else cout << -1 << endl;
		cout << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
