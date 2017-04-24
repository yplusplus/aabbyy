#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 555;
vector<int> vec[N];
int d[N];
int visit[N];
int circle;
int cc;
int n, m;

void dfs(int u, int fa) {
	visit[u] = true;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		if (visit[v]) {
			circle++;
			//cout << u << "->" << v << endl;
		} else {
			dfs(v, u);
		}
	}
}


int cnt[5];
vector<int> vvv;
void _dfs(int u, int fa, int dep, int s) {
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		if (d[v] == 1) {
			vvv.push_back(dep + 1);
		} else if (v == s) {
			vvv.push_back(dep + 1);
		} else {
			_dfs(v, u, dep + 1, s);
		}
	}
}

vector<pair<int, int> > ans;
void solve() {
	ans.clear();
	if (n < 3) return;
	if (cc > 1) return;
	int d2 = 0, d1 = 0, d3 = 0;
	int v31, v32;
	for (int i = 1; i <= n; i++) {
		if (d[i] == 1) d1++;
		if (d[i] == 2) d2++;
		if (d[i] == 3) {
			d3++;
			if (d3 == 1) v31 = i;
			if (d3 == 2) v32 = i;
		}
	}
	if (d1 + d2 + d3 != n) return;
	vvv.clear();
	//cout << circle << endl;
	//cout << d1 << " " << d2 << " " << d3 << endl;
	if (circle == 0) {
		//1
		int t = n - 3;
		if (d1 == 2 && d2 == n - 2 && t % 2 == 0) {
			ans.push_back(make_pair(1, t / 2));
		}
		//2 5
		t = n - 6;
		if (d1 == 2 && d2 == n - 2 && t % 5 == 0) {
			ans.push_back(make_pair(2, t / 5));
			ans.push_back(make_pair(5, t / 5));
		}
		//7
		t = n - 4;
		if (d1 == 2 && d2 == n - 2 && t % 3 == 0) {
			ans.push_back(make_pair(7, t / 3));
		}
		//3 4
		//cout << d1 << " " << d2 << " " << d3 << endl;
		//cout << v31  << endl;
		if (d3 == 1 && d1 == 3) {
			_dfs(v31, 0, 0, v31);
			sort(vvv.begin(), vvv.end());
			//cout << vvv.size() << endl;
			//for (int i = 0; i < vvv.size(); i++) {
			//cout << vvv[i] << endl;
			//}
			//4
			if (vvv[0] == vvv[1] && vvv[0] * 2 == vvv[2]) {
				ans.push_back(make_pair(4, vvv[0] - 1));
			}
			//3
			if (vvv[1] == vvv[2] && vvv[0] * 2 == vvv[2]) {
				ans.push_back(make_pair(3, vvv[0] - 1));
			}
		}
	} else if (circle == 2) {
		//0
		if (d2 == n) {
			int t = n - 6;
			if (t % 6 == 0) {
				ans.push_back(make_pair(0, t / 6));
			}
		}
		//6 9
		if (d3 == 1 && d1 == 1) {
			_dfs(v31, 0, 0, v31);
			sort(vvv.begin(), vvv.end());
			if (vvv[0] * 2 == vvv[1]) {
				ans.push_back(make_pair(6, (vvv[0] - 2) / 2));
				ans.push_back(make_pair(9, (vvv[0] - 2) / 2));
			}
		}

	} else if (circle == 4 && d3 == 2 && d2 == n - 2) {
		//8
		_dfs(v31, 0, 0, v32);
		sort(vvv.begin(), vvv.end());
		if (vvv[0] * 3 == vvv[1] && vvv[1] == vvv[2]) {
			ans.push_back(make_pair(8, vvv[0] - 1));
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int Case = 1; Case <= T; Case++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) { vec[i].clear(); }
		memset(d, 0, sizeof(d));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			vec[a].push_back(b);
			vec[b].push_back(a);
			d[a]++, d[b]++;
		}
		circle = cc = 0;
		memset(visit, false, sizeof(visit));
		//dfs(3, 0);
		for (int i = 1; i <= n; i++) {
			if (!visit[i]) {
				cc++;
				dfs(i, 0);
			}
		}
		//cout << circle << " " << cc << endl;
		solve();
		sort(ans.begin(), ans.end());
		printf("Case %d: %d\n", Case, (int) ans.size());
		for (int i = 0; i < ans.size(); i++) {
			printf("%d %d\n", ans[i].first, ans[i].second);
		}
		if (Case < T) puts("");
	}
	return 0;
}
