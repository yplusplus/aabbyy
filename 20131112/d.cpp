#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 11;
const LL LINF = 0x7777777777777777ll;
int dg[N], n, k;
LL ans;

bool check(LL n) {
	if (k == 0 && n == 0) return 0;
	n = abs(n);
	while (n != 0) {
		if (n % 10 == k) return 0;
		n /= 10;
	}
	return 1;
}

void dfs(LL cur, int p) {
	cur = abs(cur);
	if (p >= n) {
		if (check(cur)) ans = max(ans, cur);
		return ;
	}
	dfs(cur + dg[p], p + 1);
	dfs(cur - dg[p], p + 1);
	dfs(cur * dg[p], p + 1);
	if (dg[p]) dfs(cur / dg[p], p + 1);
}

int main() {
	int _;
	cin >> _;
	while (_--) {
		cin >> n >> k;
		for (int i = 0; i < n; i++) cin >> dg[i];
		ans = -LINF;
		dfs(dg[0], 1);
		if (ans == -LINF) cout << "No result" << endl;
		else cout << ans << endl;
	}
	return 0;
}
