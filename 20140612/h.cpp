#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
int n, m, k;
int a[N], b[N];
short next_a[N][N], next_b[N][N];
short dp[N][N];
short state[N][N], digit[N][N];
short pre[N];

void dfs(int pos, int cnt) {
	if (cnt == 0) return;
	dfs(state[pos][cnt], cnt - 1);
	printf("%d ", digit[pos][cnt]);
}

void solve() {
	for (int i = 1; i <= k; i++) pre[i] = n + 1;
	for (int i = n + 1; i >= 0; i--) {
		for (int j = 1; j <= k; j++) {
			next_a[i][j] = pre[j];
		}
		pre[a[i]] = i;
	}
	for (int i = 1; i <= k; i++) pre[i] = m + 1;
	for (int i = m + 1; i >= 0; i--) {
		for (int j = 1; j <= k; j++) {
			next_b[i][j] = pre[j];
		}
		pre[b[i]] = i;
	}
	//for (int i = 1; i <= k; i++) { next_a[n + 1][i] = n + 1; } for (int i = 1; i <= k; i++) { next_b[m + 1][i] = m + 1; }
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= max(n, m) + 2; j++) {
			dp[i][j] = -1;
		}
	}
	dp[0][0] = 0;
	short ans = 0;
	for (int j = 0; ; j++) {
		//cout << n + 1 << " " << j << " " << dp[n + 1][j] << endl;
		if (dp[n + 1][j] == m + 1) {
			ans = j;
			break;
		}
		for (int i = 0; i <= n + 1; i++) {
			if (dp[i][j] == -1) continue;
			for (int l = 1; l <= k; l++) {
				short ni = next_a[i][l];
				short t = next_b[dp[i][j]][l];
				if (dp[ni][j + 1] < t) {
					dp[ni][j + 1] = t;
					state[ni][j + 1] = i;
					digit[ni][j + 1] = l;
				}
				//dp[ni][j + 1] = max(dp[ni][j + 1], next_b[dp[i][j]][l]);
			}
		}
	}
	printf("%d\n", ans);
	dfs(n + 1, ans);
	puts("");
}

int main() {
	freopen("robots.in", "r", stdin);
	freopen("robots.out", "w", stdout);
	scanf("%d", &k);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
	solve();
	return 0;
}
