#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x, y;
	while (cin >> n >> x) {
		int l = -1111, r = 1111;
		for (int i = 0; i < n; i++) {
			cin >> y;
			if (y > 0) r = min(r, y);
			else l = max(l, y);
		}
		if (x < l || x > r) cout << "Impossible" << endl;
		else {
			if (x > 0) cout << x << " " << x + 2 * (-l) << endl;
			else cout << -x + 2 * r << " " << -x << endl;
		}
	}
	return 0;
}

