#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
typedef long long LL;
LL n, m, k;
LL a[N], b[N];

LL cal(const LL &x) {
	LL sum = 0;
	for (int i = 0; i < n; i++) {
		LL t = x / a[i];
		sum += upper_bound(b, b + m, t) - b;
	}
	return sum;
}

LL work() {
	LL l = 0, r = (LL) N * N, mid, mk;
	while (l <= r) {
		mid = l + r >> 1;
		if (cal(mid) >= k) mk = mid, r = mid - 1;
		else l = mid + 1;
	}
	return mk;
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n >> m >> k) {
		k = n * m - k + 1;
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < m; i++) cin >> b[i];
		sort(b, b + m);
		cout << work() << endl;
	}
	return 0;
}
