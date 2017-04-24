#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

double ua, u0, u1, t1, k;
double cal(double x) { return k * log((u0 - ua) / (x - ua));}

int main() {
	//freopen("in", "r", stdin);
	int T, n;
	cin >> T;
	for (int cas = 1;  cas <= T; cas++) {
		cin >> ua >> u0 >> u1 >> t1 >> n;
		cout << "Case " << cas << ":" << endl;
		k = t1 / log((u0 - ua) / (u1 - ua));
		while (n--) {
			int op, x;
			cin >> op >> x;
			if (op) {
				double l = ua, r = u0, mid;
				for (int i = 0; i < 50; i++) {
					mid = (l + r) / 2;
					if (cal(mid) < x) r = mid;
					else l = mid;
				}
				printf("%.2f\n", mid);
			} else {
				printf("%.2f\n", cal(x));
			}
		}
		cout << endl;
	}
	return 0;
}

