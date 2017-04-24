#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	int n, k, x, ans1, ans2;
	while (cin >> n >> k) {
		ans1 = ans2 = 0;
		for (int i = 0; i < n; i++) {
			cin >> x;
			ans1 += max(x - k, 0);
			ans2 += max(k - x, 0);
		}
		cout << ans1 << ' ' << ans2 << endl;
	}
	return 0;
}
