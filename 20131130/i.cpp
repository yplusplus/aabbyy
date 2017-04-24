#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 222222;
int q[N << 1], a[N];
int n, m;

int main() {
	int _;
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", a + i);
		}
		sort(a, a + m);
		int dt = n / m, hn = n >> 1;
		for (int i = 0; i < m; i++) {
			a[i] = a[i] - i * dt;
			if (a[i] > hn) a[i] -= n;
			if (a[i] < -hn) a[i] += n;
		}
		sort(a, a + m);
		reverse(a, a + m);
		int qh, qt;
		qh = qt = 0;
		for (int i = 0; i < m; i++) q[qt++] = a[i];
		int ans = n;
		for (int i = 0; i < n; i++) {
			while (q[qh] + i > hn) q[qt++] = q[qh++] - n;
			ans = min(ans, max(abs(q[qh] + i), abs(q[qt - 1] + i)));
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}

