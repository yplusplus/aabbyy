#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

/*
--------
--------
--------
*/

long long cal(long long x, long long y) {
	return (x + y) * (y - x + 1) / 2;
}

long long cal2(long long x) {
	return x * (x + 1) * (2 * x + 1) / 6;
}

long long cal2(long long x, long long y) {
    return cal2(y) - cal2(x - 1);
}

void solve() {
	long long n, m;
	cin >> n >> m;
	long long ans = 0;
	for (long long x = 1; x <= n; x++) {
		long long r = min(m - x, n - x);
		long long l = 0;
		if (r < l) continue;
		long long p = n - x + 1, q = m - x + 1;
		/*
		 * (p - l) * (q - l) + ... (p - r) * (q - r)
		 * (p * q - l * (p + q) + l^2)
		 * (r - l + 1) * p * q -
		 */
		ans += p * q * (r - l + 1) - (p + q) * cal(l, r) + cal2(l, r);
		/*
		for (long long y = 0; y + x <= m; y++) {
			if (!x && !y) continue;
			if (x > y) continue;
			long long p = x + y;
			ans += (n - p + 1) * (m - p + 1);
		}*/
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
