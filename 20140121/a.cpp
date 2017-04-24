#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	int _, x, y;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> x;
		x = y = 0;
		int ans = 0;
		for (int i = 0; i < 15; i++) {
			cin >> y;
			if (x > y) ans++;
			x = y;
		}
		cout << cas << ' ' << ans << endl;
	}
	return 0;
}
