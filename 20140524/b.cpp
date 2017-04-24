#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<LL> VI;
VI a;

int run() {
	int _, n;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> n;
		a.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		cout << "Case #" << cas << ": ";
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}
		sort(a.begin(), a.end());
		multiset<LL> tree;
		for (int i = 0; i < n; ++i) {
			tree.insert(a[i]);
		}
		int answer = INT_MAX;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				LL d = a[j] - a[i];
				if (d == 0) {
					answer = min(int(n - tree.count(a[i])), answer);
					continue;
				}
				for (int k = 1; k < n; ++k) {
					if (d % k) continue;
					LL dt = d / k, temp;
					vector<int> mark(n << 1 | 1, 0);
					for (int t = -n; t <= n; ++t) {
						temp = a[i] + dt * t;
						if (tree.find(temp) == tree.end()) mark[t + n] = 0;
						else mark[t + n] = 1;
					}
					for (int t = 1, n2 = n << 1; t <= n2; ++t) {
						mark[t] += mark[t - 1];
					}
					for (int t = n, n2 = n << 1; t <= n2; ++t) {
						answer = min(n - (mark[t] - mark[t - n]), answer);
					}
				}
			}
		}
		cout << answer << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
