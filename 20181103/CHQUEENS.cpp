#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

int get_tot(int i, int j, int n, int m) {
    int ans = n + m - 1;
	ans += min(i - 1, j - 1);
	ans += min(n - i, m - j);
	ans += min(i - 1, m - j);
	ans += min(n - i, j - 1);
	return ans;
}

void solve() {
	int n, m, x, y;
	scanf("%d%d%d%d", &n, &m, &x, &y);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == x && j == y) continue;
			int tot = get_tot(i, j, n, m);
			if (i == x) {
				if (j < y) tot -= m - y;
				else tot -= y - 1;
			} else if (j == y) {
				if (i < x) tot -= n - x;
				else tot -= x - 1;
			} else if (x > i && y > j && x - i == y - j) {
				tot -= min(n - x, m - y);
			} else if (x < i && y < j && i - x == j - y) {
				tot -= min(x - 1, y - 1);
			} else if (x - i == j - y && x > i && j > y) {
				/*
				 * (3, 3) (5, 1)
				 */
	            tot -= min(n - x, y - 1);
			} else if (i - x == y - j && x < i && y > j) {
	            tot -= min(x - 1, m - y);
			} else tot++;
			ans += n * m - tot;
		}
	}

	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) solve();
	return 0;
}
