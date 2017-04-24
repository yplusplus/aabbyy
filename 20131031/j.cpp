#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 11111;

struct Program {
	int x, y, d, t;
	Program(int x, int y, int d, int t) : x(x), y(y), d(d), t(t) {}
};

vector<Program> vec[N];
ll dp[N][2];

void update(ll &x, ll y) {
	if (x == -1 || x > y) x = y;
}

int main() {
	char str[30];
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int x, y, d;
			scanf("%d%d%d%s", &x, &y, &d, str);
			if (str[0] == 'P') {
				vec[x].push_back(Program(x, y, d, 0));
			} else if (str[0] == 'C') {
				vec[x].push_back(Program(x, y, d, 1));
			} else if (str[0] == 'L') {
				vec[x].push_back(Program(x, y, d, 2));
			}
		}
		memset(dp, -1, sizeof(dp));
		dp[1][1] = 0;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < vec[i].size(); j++) {
				int x = vec[i][j].x, y = vec[i][j].y, d = vec[i][j].d, t = vec[i][j].t;
				if (t == 0) {
					if (dp[x][0] != -1) update(dp[y][0], dp[x][0] + d);
					if (dp[x][1] != -1) update(dp[y][0], dp[x][1] + d);
				} else if (t == 1) {
					if (dp[x][0] != -1) update(dp[y][0], dp[x][0] + d);
					if (dp[x][1] != -1) update(dp[y][1], dp[x][1] + d);
				} else if (t == 2) {
					if (dp[x][1] != -1) update(dp[y][1], dp[x][1] + d);
				}
			}
		}
		ll ans = -1;
		if (dp[n][0] != -1) update(ans, dp[n][0]);
		if (dp[n][1] != -1) update(ans, dp[n][1]);
		if (ans == -1) puts("Offline");
		else {
			puts("Online");
			cout << ans << endl;
		}
	}
	return 0;
}

