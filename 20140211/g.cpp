#include <bits/stdc++.h>
using namespace std;

const int N = 111;
int a[N];
int n;

int calc(int x) {
	int res = 0;
	while (x % 2 == 0) {
		res++;
		x >>= 1;
	}
	return res;
}

int fac(int x) {
	int res = 0;
	for (int i = 1; i <= x; i++) {
		res += calc(i);
	}
	return res;
}

int C(int n, int m) {
	m = min(m, n - m);
	int res = 0;
	for (int i = 0; i < m; i++) {
		res += calc(n - i);
		res -= calc(i + 1);
	}
	return res;
}

void solve1() {
	int sum = 0;
	for (int i = 0; i < n; i++) sum += a[i];
	if (sum == n) {
		cout << -1 << endl;
		cout << 0 << endl;
		return ;
	}
	int ans = 0;
	cout << n + 1 << endl;
	for (int i = 0; i < n; i++) {
		ans += calc(i + 1);
		ans += calc(a[i]);
	}
	for (int i = 0; i < n; i++) ans -= calc(sum - i);
	cout << ans << endl;
}

void solve2() {
	sort(a, a + n);
	reverse(a, a + n);
	int sum = 0, mi = 111, cnt = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
		if (mi > a[i]) mi = a[i], cnt = 1;
		else if (mi == a[i]) cnt++;
	}
	int b = sum - mi + 1;
	int ans = 0;
	int t = 0;
	//cout << sum << " " << mi << " " << cnt << endl;
	for (int i = 0; i < n - 1; i++) {
		ans += fac(a[i]);
		t += a[i];
		ans += C(t, a[i]);
	}
	//cout << ans << endl;
	ans += calc(mi);
	//cout << ans << endl;
	ans += calc(cnt);
	//cout << ans << endl;
	for (int i = 0; i < b; i++) {
		ans -= calc(sum - i);
	}
	cout << b << endl;
	cout << ans << endl;
}

int main() {
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> a[i];
		solve1();
		solve2();
	}
	return 0;
}
