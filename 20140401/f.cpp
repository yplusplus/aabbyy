#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
const int inf = 1 << 25;
int cost[N][N];
int dp[55][N];
int n, m, d;

struct BIT {
	int c[N];
	void clear() { memset(c, 0, sizeof(c)); }
	void add(int x, int v) { for (int i = x; i <= n; i += lowbit(i)) { c[i] += v; } }
	int sum(int x) { int res = 0; for (int i = x; i > 0; i -= lowbit(i)) { res += c[i]; } return res; }
	int lowbit(int x) { return x & (-x); }
} bit;

struct Person {
	int pos, id;
	void read(int _id) {
		scanf("%d", &pos);
		id = _id;
	}
	bool operator <(const Person &x) const {
		if (pos != x.pos) return pos < x.pos;
		return id > x.id;
	}
} p[N];

void solve() {
	sort(p + 1, p + 1 + n);
	memset(cost, 0, sizeof(cost));
	for (int i = 1; i <= m; i++) {
		bit.clear();
		int q = 1;
		while (q <= n && p[q].pos < i) q++;
		int sum = 0;
		for (int j = i; j <= m; j++) {
			if (q > n || p[q].pos != j) {
				cost[i][j] = sum;
				continue;
			}
			int k = q;
			while (k + 1 <= n && p[k + 1].pos == j) k++;
			for (int l = q; l <= k; l++) {
				sum += bit.sum(p[l].id);
				bit.add(p[l].id, 1);
			}
			q = k + 1;
			cost[i][j] = sum;
			//cout << "cost " << i << " " << j << " " << cost[i][j] << endl;
		}
	}
	//memset(dp, -1, sizeof(dp));
	for (int i = 0; i <= m; i++) dp[0][i] = inf;
	dp[0][0] = 0;
	for (int i = 1; i <= d; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = inf;
			for (int k = 0; k <= j - 1; k++) {
				dp[i][j] = min(dp[i][j], dp[i - 1][k] + cost[k + 1][j]);
			}
			//cout << i << " " << j << " " << dp[i][j] << endl;
		}
	}
	printf("%d\n", dp[d][m]);
}

int main() {
	freopen("flight.in", "r", stdin);
	freopen("flight.out", "w", stdout);
	while (~scanf("%d%d%d", &n, &m, &d)) {
		for (int i = 1; i <= n; i++) { p[i].read(i); }
		solve();
	}
	return 0;
}
