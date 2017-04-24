#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 111111;
ll w[N], sum[N], t[N];
int n, m, k;

ll bs(int pos) {
	int res = 0, l = 0, r = pos;
	while (l <= r) {
		int mid = l + r >> 1;
		if (sum[pos] - sum[mid] > k) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> m >> k) {
		sum[0] = 0;
		for (int i = 1; i <= n; i++) cin >> w[i], sum[i] = sum[i - 1] + w[i];
		for (int i = 0; i < m; i++) cin >> t[i];
		ll pos = 0;
		ll ans = 0, now = 0;
		t[m++] = 1LL << 60;
		for (int i = 0; i < m; i++) {
			ll next = t[i];
			ll tmp = next - 1 - now;
			if (tmp + pos >= n) {
				ans = now + (n - pos);
				break;
			} else {
				pos += tmp;
				if (sum[pos] <= k) pos = 0;
				else {
					pos = bs(pos);
				}
				now = next;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
