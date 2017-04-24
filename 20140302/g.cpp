#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
int cx, cy, c;
int T;
int n;

double sq(double x) {
	return x * x;
}

int main() {
	while (~scanf("%d%d%d%d", &cx, &cy, &c, &T)) {
		scanf("%d", &n);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			int x, y, dx, dy;
			scanf("%d%d%d%d", &x, &y, &dx, &dy);
			x -= cx, y -= cy;
			double l, r, mid;
			double t;
			//0-T
			l = 0, r = T;
			for (int j = 0; j < 200; j++) {
				double mid = l + (r - l) / 3.0;
				double mmid = r - (r - l) / 3.0;
				double vmid = sq(x + dx * mid) + sq(y + dy * mid) - sq(c * mid);
				double vmmid = sq(x + dx * mmid) + sq(y + dy * mmid) - sq(c * mmid);
				if (vmid < vmmid) {
					r = mmid;
				} else l = mid;
			}
			t = sq(x + dx * l) + sq(y + dy * l) - sq(c * l);
			//cout << i << " " << t << endl;
			if (t < 0 || fabs(t) < eps) {
				ans++;
				continue;
			}
			//T-2T
			l = T, r = 2 * T;
			//x += dx * T, y += dy * T;
			for (int j = 0; j < 200; j++) {
				double mid = l + (r - l) / 3.0;
				double mmid = r - (r - l) / 3.0;
				double vmid = sq(x + dx * mid) + sq(y + dy * mid) - sq(c * (2 * T - mid));
				double vmmid = sq(x + dx * mmid) + sq(y + dy * mmid) - sq(c * (2 * T - mmid));
				if (vmid < vmmid) {
					r = mmid;
				} else l = mid;
			}
			t = sq(x + dx * l) + sq(y + dy * l) - sq(c * (2 * T - l));
			//cout << i << " " << t << endl;
			if (t < 0 || fabs(t) < eps) ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
