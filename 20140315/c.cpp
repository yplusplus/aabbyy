#include <bits/stdc++.h>
using namespace std;

int run() {
	int n;
	while (cin >> n) {
		int r = n % 14;
		if (n / 14 == 1 && n == 21) cout << 1 << endl;
		else if (n / 14 >= 2 && 2 <= r && r <= 12) cout << n / 14 << endl;
		else cout << -1 << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	return run();
}
