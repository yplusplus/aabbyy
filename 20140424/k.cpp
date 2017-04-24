#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 12;
const int MOD = (1 << 30) - 1;
typedef pair<int, int> Factor;
#define x first
#define y second
int n, k;
int x[N], y[N];
map<Factor, int> dp[2];
void fix(Factor &a) {
	int g = __gcd(a.x, a.y);
	a.x /= g;
	a.y /= g;
}

void print(const pair<Factor, int> &pfi) { cout << pfi.x.x << ' ' << pfi.x.y << ' ' << pfi.y << endl; }

int work() {
	for (int i = 0; i < 2; ++i) dp[i].clear();
	Factor temp, buffer;
	for (int i = 0; i < y[0]; ++i) {
		temp = Factor(y[0] - i, x[0]);
		fix(temp);
		dp[0][temp] = 1;
	}
	for (int b = 1, a, c; b < k; ++b) {
		a = b - 1;
		c = b & 1;
		int my = min(y[a], y[b]);
		dp[c].clear();
		for (int i = x[a] + 1; i < x[b]; ++i) {
			for (int j = 0; j < my; ++j) {
				temp = Factor(y[a] - j, i - x[a]);
				fix(temp);
				buffer = Factor(y[b] - j, x[b] - i);
				fix(buffer);
				if (dp[c ^ 1].find(temp) != dp[c ^ 1].end()) {
					dp[c][buffer] += dp[c ^ 1][temp];
					dp[c][buffer] &= MOD;
				}
			}
		}
		//cout << "dp " << b << endl; for_each(dp[c].begin(), dp[c].end(), print);
	}
	int ans = 0;
	for (int i = 0; i < y[k - 1]; ++i) {
		temp = Factor(y[k - 1] - i, n - x[k - 1]);
		fix(temp);
		ans += dp[k - 1 & 1][temp];
		ans &= MOD;
	}
	return ans;
}

int run() {
	while (cin >> n >> k) {
		for (int i = 0; i < k; ++i) cin >> x[i] >> y[i];
		cout << work() << endl;
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
