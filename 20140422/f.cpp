#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL work(int n, int m) {
	LL t = (1LL << m) - 1, s = t;
	n = (int) min((LL) n, t);
	for (int i = 0; i < n; ++i) {
		s += (t - i - 1) << i;
	}
	return s;
}

int run() {
	int n, m;
	while (cin >> n >> m && (n || m)) {
		cout << work(n, m) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
