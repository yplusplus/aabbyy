#include <bits/stdc++.h>
using namespace std;

const int N = 111111;

int sum[N], a[N], b[N];
int n;

int main() {
	int Case = 1;
	while (~scanf("%d", &n), n) {
		for (int i = 1; i <= n; i++) { scanf("%d", &a[i]); }
		for (int i = 1; i <= n; i++) { scanf("%d", &b[i]); }
		sum[0] = 0;
		int mi = 1 << 30;
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i - 1] + a[i] - b[i];
			mi = min(mi, sum[i]);
		}
		printf("Case %d:", Case++);
		for (int i = 1; i <= n; i++) {
			if (mi == 0) printf(" %d", i);
			mi -= a[i] - b[i];
		}
		puts("");
	}
	return 0;
}
