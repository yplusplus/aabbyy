#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	int c, d, n;
	while (cin >> c >> d >> n) {
		ll ans = 0;
		int i = 0;
		while (i < n) {
			int j;
			for (j = i; j < n; j++) {
				if (i / c != j / c) break;
			}
			int now = -1;
			ll cnt = 0, sum = 0;
			for (int k = i; k < j; k++) {
				if (k / d != now) {
					ans += sum * cnt;
					sum += cnt;
					cnt = 1;
					now = k / d;
				} else {
					cnt++;
				}
			}
			ans += sum * cnt;
			i = j;
		}
		cout << ans << endl;
	}
	return 0;
}