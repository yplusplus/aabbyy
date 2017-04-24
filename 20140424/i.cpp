#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int total[N], cnt;
bool vis[N];
vector<int> ans[N];

void dfs(int p, int hn, int n, int last) {
	if (p >= hn) {
		for (int i = 0; i < n; ++i) {
			if (vis[i]) {
				ans[i].push_back(cnt);
				//cout << i << ' ';
			}
		}
		//cout << endl;
		--cnt;
		return ;
	}
	for (int i = last; i < n && cnt; ++i) {
		if (vis[i]) continue;
		vis[i] = 1;
		dfs(p + 1, hn, n, i + 1);
		vis[i] = 0;
	}
}

int run() {
	int n;
	for (int i = 1; i < N; ++i) {
		int j = i + 1 >> 1;
		total[i] = 1;
		for (int k = 0; k < j; ++k) {
			total[i] *= i - k;
			total[i] /= k + 1;
		}
		//cout << i << ' ' << total[i] << endl;
	}
	while (cin >> n) {
		int mk = 1;
		while (total[mk] < n) ++mk;
		cnt = n;
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < mk; ++i) ans[i].clear();
		dfs(0, mk + 1 >> 1, mk, 0);
		cout << mk << endl;
		for (int i = 0; i < mk; ++i) {
			for (int j = 0, size = ans[i].size(); j < size; ++j) {
				if (j) cout.put(' ');
				cout << ans[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
