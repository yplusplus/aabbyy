#include <bits/stdc++.h>
using namespace std;

bool check(const string &a, const string &b, int n) {
	int half = n + 1 >> 1;
	//cout << half << endl;
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		for (int j = 0; i + j < n; ++j) {
			if (abs(a[j] - b[i + j]) <= 1) ++cnt;
			else cnt = 0;
			//cout << i << ' ' << a[i] << ' ' << i + j << ' ' << b[i + j] << ' ' << abs(a[j] - b[i + j]) << ' ' << cnt << endl;
			if (cnt >= half) return 1;
		}
	}
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		for (int j = 0; i + j < n; ++j) {
			if (abs(b[j] - a[i + j]) <= 1) ++cnt;
			else cnt = 0;
			//cout << i << ' ' << a[i] << ' ' << i + j << ' ' << b[i + j] << ' ' << abs(a[j] - b[i + j]) << ' ' << cnt << endl;
			if (cnt >= half) return 1;
		}
	}
	return 0;
}

int run() {
	int _, n;
	cin >> _;
	string a, b;
	while (_--) {
		cin >> n >> a >> b;
		cout << (check(a, b, n) ? "POSITIVE" : "NEGATIVE") << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
