#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> pdd;
const int N = 111111;
const int D = 50;
int a[N];
int n, length;

pdd Union(const pdd &a, const pdd &b) {
	return make_pair(max(a.first, b.first), min(a.second, b.second));
}

int main() {
	while (~scanf("%d%d", &length, &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		double ans = 0;
		for (int i = 1; i < n - 2; i++) {
			pdd seg = make_pair(a[i], a[i + 1]);
			seg = Union(seg, make_pair(2 * a[0], 2 * a[i]));
			seg = Union(seg, make_pair(2 * a[i + 1] - length, 2 * a[n - 1] - length));
			ans += max(seg.second - seg.first, 0.0);
		}
		ans = length - ans;
		printf("%d\n", (int) ceil(ans - 1e-8));
	}
}

