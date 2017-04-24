#include <bits/stdc++.h>
using namespace std;

const int N = 55555;
const long long inf = 1LL << 60;
int n;
int sum[N];
int s1, e1, s2, e2;
long long ans;

void update(long long tmp, int a, int b, int c, int d) {
	if (tmp < ans) {
		ans = tmp;
		s1 = a, e1 = b, s2 = c, e2 = d;
	}
}

int main() {
	int first = 1;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		if (first) first = 0;
		else puts("");
		sum[1] = 0;
		for (int i = 2; i <= n; i++) {
			scanf("%d", &sum[i]);
		}
		if (n <= 3) {
			puts("0");
			continue;
		}
		ans = inf;
		for (int i = 2; i < n - 1; i++) {
			long long tmp = sum[n] - sum[i];
			tmp += sum[i + 1] - sum[1];
			update(tmp, i + 1, 1, n, i);
		}
		cout << ans << endl;
		cout << s1 << " " << e1 << " " << s2 << " " << e2 << endl;
	}
	return 0;
}
