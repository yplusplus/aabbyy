#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 312345;
const double EPS = 1e-6;
double c[N];

int main() {
	//cout << setiosflags(ios::fixed) << setprecision(10);
	//cout << sqrt(1000001.0) << endl;
	int m, n;
	double r;
	while (~scanf("%d%d%lf", &m, &n, &r)) {
		r = sqrt(r * r - 1);
		for (int i = 1; i <= m; i++) scanf("%lf", c + i);
		double ans = 0, cur = c[1], x;
		int it;
		for (int i = 1; i <= n; i++) {
			scanf("%lf", &x);
			if (x - r - EPS <= cur && cur <= x + r + EPS) continue;
			if (x > cur) {
				x -= r;
				it = (int) (lower_bound(c + 1, c + m + 1, x - EPS) - c);
				ans += fabs(cur - c[it]);
				cur = c[it];
			} else {
				x += r;
				it = (int) (upper_bound(c + 1, c + m + 1, x + EPS) - c) - 1;
				ans += fabs(cur - c[it]);
				cur = c[it];
			}
			//cout << x << ' ' << cur << endl;
		}
		printf("%.3f\n", ans);
	}
	return 0;
}


