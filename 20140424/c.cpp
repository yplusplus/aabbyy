#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int fix(int a) {
	vector<int> dg;
	while (a > 0) {
		dg.push_back(a % 10);
		a /= 10;
	}
	sort(dg.begin(), dg.end());
	for (int i = 0, size = dg.size(); i < size; ++i) {
		a = a * 10 + dg[i];
	}
	return a;
}

int run() {
	int n;
	while (cin >> n) {
		if (n > 60) {
			n %= 60;
			n += 60;
		}
		int a = 1;
		for (int i = 0; i < n - 1; ++i) {
			//cout << (i + 1) << ' ' << a << endl;
			a <<= 1;
			a = fix(a);
		}
		cout << a << endl;
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
