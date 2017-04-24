#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 10000000000007LL;

ll l, m, n;

int main() {
	int T, Case = 1;
	cin >> T;
	while (T--) {
		cin >> l >> m >> n;
		ll ans = 0;
		ll tmp = 1;
		ll l2 = l * l;
		for (int i = 0; i < m; i++) {
			tmp = (tmp * (l2 - i)) % MOD;
		}
		for (int i = m; i <= n; i++) {
			ans = (ans + tmp) % MOD;
			tmp = (tmp * (l2 - i)) % MOD;
		}
		printf("Case %d: ", Case++);
		cout << ans << endl;
	}
}

