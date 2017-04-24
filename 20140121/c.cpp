#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
typedef vector<int> VI;
typedef pair<int, int> PII;
#define x first
#define y second
VI to[N], from[N];
int in[N];
bool vis[N];

int main() {
	ios::sync_with_stdio(0);
	int _, n, m, cas, u, v;
	cin >> _;
	while (_--) {
		cin >> cas >> n >> m;
		for (int i = 1; i <= n; i++) to[i].clear();
		for (int i = 1; i <= n; i++) from[i].clear();
		for (int i = 1; i <= n; i++) in[i] = 0;
		for (int i = 1; i <= n; i++) vis[i] = 0;
		for (int i = 0; i < m; i++) {
			cin >> u >> v;
			in[v]--;
			to[u].push_back(v);
		}
		priority_queue<PII> q;
		for (int i = 1; i <= n; i++) q.push(PII(in[i], i));
		int ans = 0;
		while (!q.empty()) {
			PII cur = q.top();
			q.pop();
			if (vis[cur.y]) continue;
			vis[cur.y] = 1;
			int e;
			if (from[cur.y].size()) {
				sort(from[cur.y].begin(), from[cur.y].end());
				e = from[cur.y][from[cur.y].size() - 1];
				int k = upper_bound(from[cur.y].begin(), from[cur.y].end(), e) - lower_bound(from[cur.y].begin(), from[cur.y].end(), e);
				if (k > 1) e++;
			} else e = 1;
			for (VI::iterator vi = to[cur.y].begin(); vi != to[cur.y].end(); vi++) {
				q.push(PII(++in[*vi], *vi));
				from[*vi].push_back(e);
			}
			//cout << cur.y << ' ' << e << endl;
			ans = max(e, ans);
		}
		cout << cas << ' ' << ans << endl;
	}
	return 0;
}
