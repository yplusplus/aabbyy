#include <iostream>
#include <queue>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int mod = 1000000007;
const int N = 210;
int c[N][N];
int fac[N];
int dp[N][N];
int pows[N * N];

long long mpow(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}

	return ans;
}

void add(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

void solve() {
	int n, m, ans = 0;
	cin >> n >> m;
	for (int i = 2; i <= m; i++)
		for (int j = 2; j <= m; j++) {
			long long t1 = mpow(min(i, j) - 1, 2 * n - 2);
			long long t2 = mpow(max(i, j) - 1, 2 * n - 4);
			long long t3 = mpow(m, n * n - 2 - (2 * n - 2) - (2 * n - 4));
			long long t4 = n * n * (n - 1) * (n - 1);
			add(ans, t1 * t2 % mod * t3 % mod * t4 % mod);
		}

	for (int i = 2; i <= m; i++) {
		long long t1 = mpow(i - 1, 2 * n - 2);
		long long t2 = mpow(m, n * n - 1 - (2 * n - 2));
		long long t3 = n * n;
		add(ans, t1 * t2 % mod * t3 % mod);
	}

	cout << ans << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
