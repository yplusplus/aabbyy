#include <bits/stdc++.h>
using namespace std;

int cal(int x) {
	int c = 0;
	x ^= x + 1;
	for (int i = 0; i < 30; ++i) if (x & 1 << i) ++c;
	return c;
}

int run() {
	int n, _;
	cin >> _;
	while (_--) {
		cin >> n;
		cout << cal(n) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
