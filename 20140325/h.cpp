#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
const long long inf = 1LL << 60;
struct Track {
	int t, a, b, c, d;
	void read() { scanf("%d%d%d%d%d", &t, &a, &b, &c, &d); }
} track[N];

int n;
long long t;

long long dp[N][2];
int pre[N][2];
string ans_str;
long long ans;

void check_min(int a, int b, long long c, int d) {
	if (dp[a][b] > c) {
		dp[a][b] = c;
		pre[a][b] = d;
	}
}

void calc(int flag) {
	memset(pre, -1, sizeof(pre));
	for (int i = 0; i < n; i++) { dp[i][0] = dp[i][1] = inf; }
	dp[0][flag] = 0;
	for (int i = 0; i < n - 1; i++) {
		check_min(i + 1, 0, dp[i][0] + track[i].c, 0);
		check_min(i + 1, 0, dp[i][1] + track[i].a, 1);
		check_min(i + 1, 1, dp[i][0] + track[i].d, 0);
		check_min(i + 1, 1, dp[i][1] + track[i].b, 1);
	}
	if (flag == 0) {
		long long a = dp[n - 1][0] + track[n - 1].c;
		long long b = dp[n - 1][1] + track[n - 1].a;
		if (min(a, b) > t) return;
		string tmp;
		if (a < b) tmp += 'F';
		else tmp += 'B';
		int x = (a >= b);
		for (int i = n - 1; i; i--) {
			x = pre[i][x];
			if (x == 0) tmp += 'F';
			else tmp += 'B';
		}
		if (min(a, b) < ans) {
			ans = min(a, b);
			ans_str = tmp;
		}
	} else {
		long long a = dp[n - 1][0] + track[n - 1].d;
		long long b = dp[n - 1][1] + track[n - 1].b;
		if (min(a, b) > t) return;
		string tmp;
		if (a < b) tmp += 'F';
		else tmp += 'B';
		int x = (a >= b);
		for (int i = n - 1; i; i--) {
			x = pre[i][x];
			if (x == 0) tmp += 'F';
			else tmp += 'B';
		}
		if (min(a, b) < ans) {
			ans = min(a, b);
			ans_str = tmp;
		}
	}
}

void solve() {
	ans = inf;
	ans_str = string(n, 'Z');
	calc(0);
	calc(1);
	reverse(ans_str.begin(), ans_str.end());
	if (ans_str == string(n, 'Z')) puts("IMPOSSIBLE");
	else cout << ans_str << endl;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		cin >> n >> t;
		for (int i = 0; i < n; i++) { track[i].read(); t -= track[i].t; }
		solve();
	}
	return 0;
}
