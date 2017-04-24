#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

#define ll long long
int n;
const int N = 888;
int a[N];
int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		ll ans = 1LL * n * (n - 1) * (n - 2) / 6;
		for (int i = 0; i < n; i++) cin >> a[i];
		ll tmp = 0;
		for (int i = 0; i < n; i++) {
			ll cnt = 0;
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				cnt += (__gcd(a[i], a[j]) == 1);
			}
			//cout << i << " " << cnt << endl;
			tmp += cnt * (n - 1 - cnt);
		}
		tmp >>= 1;
		ans -= tmp;
		cout << ans << endl;
	}
	return 0;
}		
