#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
int sum[N];
int main() {
	int n, x, y;
	while (~scanf("%d", &n)) {
		sum[0] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &sum[i]);
			sum[i] += sum[i - 1];
		}
		scanf("%d%d", &x, &y);
		int ans;
		if (x == y) {
			ans = max(sum[x], sum[n] - sum[x - 1]);
		} else if (x < y) {
			int mid = x + y >> 1;
			ans = sum[mid];
		} else {
			int mid = x + y >> 1;
			if ((x - y + 1) % 2) mid--;
			ans = sum[n] - sum[mid];
		}
		printf("%d %d\n", ans, sum[n] - ans);
	}
	return 0;
}
