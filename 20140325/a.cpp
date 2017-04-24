#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL cal(LL n, const LL &a) {
	LL cnt = 0;
	while (n > 0) n /= a, cnt += n;
	return cnt;
}

LL work(const LL &n, LL k) {
	LL maxCnt = LLONG_MAX;
	for (LL i = 2ll; i * i <= k; ++i) {
		if (k % i) continue;
		int cnt = 0;
		while (k % i == 0) ++cnt, k /= i;
		maxCnt = min(cal(n, i) / cnt, maxCnt);
	}
	if (k > 1) maxCnt = min(cal(n, k), maxCnt);
	return maxCnt;
}

int run() {
	int _;
	cin >> _;
	while (_--) {
		LL n, k;
		cin >> n >> k;
		cout << work(n, k) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
