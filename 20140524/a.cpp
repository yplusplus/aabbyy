#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 17;
int x[N], l[N], r[N], answer[N];

int run() {
	int _, n, m, k;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> n >> m;
		int tt = 0;
		bool ok = 1;
		for (int i = 0; i < m; ++i) {
			l[i] = tt - 1;
			cin >> k;
			for (int j = 0; j < k; ++j) {
				cin >> x[tt];
				if (j && x[tt - 1] > x[tt]) ok = 0;
				++tt;
			}
			r[i] = tt - 1;
			if (i && (r[i - 1] - l[i - 1]) < (r[i] - l[i])) ok = 0;
		}
		assert(tt == n);
		cout << "Case #" << cas << ":";
		if (ok) {
			for (int i = n - 1, j = 0; i >= 0; --i) {
				if (j >= m || (r[j] - l[j]) <= 0) j = 0;
				if (r[j] - l[j] <= 0) {
					ok = 0;
					break;
				}
				if (j && answer[i + 1] > x[r[j]]) j = 0;
				answer[i] = x[r[j]--];
				++j;
			}
			if (ok) {
				for (int i = 0; i < n; ++i) {
					cout << ' ' << answer[i];
				}
				cout << endl;
			} else {
				cout << " No solution" << endl;
			}
		} else {
			cout << " No solution" << endl;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
