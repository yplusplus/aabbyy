#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 11111;
const int INF = 0x77777777;
LL a[N], x[N];

LL cal(LL a, LL b) {
	LL ret;
	if (a >= 0) {
		ret = a / b;
		if (a % b) ret++;
	} else {
		ret = (-a) / b;
		ret = -ret;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	int n, m;
	while (cin >> n >> m) {
		for (int i = 0; i < n + m - 1; i++) cin >> a[i];
		LL cur = 0;
		for (int i = 0; i < n; i++) {
			LL mx = -INF;
			for (int j = 0; j < m; j++) mx = max(cal(a[i + j] - cur, j + 1ll), mx);
			//cout << i << ' ' << cur << endl;
			cur += mx;
			x[i] = mx;
		}
		for (int i = 0; i < n; i++) {
			if (i) cout << ' ';
			cout << x[i];
		}
		cout << endl;
	}
	return 0;
}



