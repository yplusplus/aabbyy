#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define ll long long
unsigned long long P, Q;
ll k;
int X, Y;
ll dp[25][25][25];
int digit[25];
ll dfs(int i, int x, int y, bool e) {
	//cout << i << endl;
	if (x > X || y > Y) return 0;
	if (i == -1) return x == X && y == Y;
	if (!e && dp[i][x][y] != -1) return dp[i][x][y];
	ll res = 0;
	int u = e ? digit[i] : 9;
	for (int d = 0; d <= u; d++) {
		res += dfs(i - 1, x + (d == 4), y + (d == 7), e & (d == u));
	}
	return e ? res : dp[i][x][y] = res;
}

ll calc(unsigned long long x) {
	int tot = 0;
	while (x) {
		digit[tot++] = x % 10;
		x /= 10;
	}
	return dfs(tot - 1, 0, 0, 1);
}

int main() {
	ios::sync_with_stdio(false);
	int T, Case = 1;
	cin >> T;
	while (T--) {
		memset(dp, -1, sizeof(dp));
		cin >> P >> Q >> X >> Y;
		ll t = calc(P);
		cout << "Case #" << Case++ << ":" << endl;
		//cout << t << endl;
		int q;
		cin >> q;
		while (q--) {
			cin >> k;
			ll ans = -1;
			unsigned long long l = P + 1, r = Q;
			while (l <= r) {
				unsigned long long mid = l + (r - l) / 2;
				//cout << mid << endl;
				if (calc(mid) - t >= k) ans = mid, r = mid - 1;
				else l = mid + 1;
			}
			if (ans == -1) cout << "Nya!" << endl;
			else cout << ans << endl;
		}
	}
	return 0;
}