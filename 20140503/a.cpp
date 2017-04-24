#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef vector<DB> VDB;
VDB p, q, s, best, current;
DB a, b;
int n;

DB gao(const DB &g) {
	DB sum = 0;
	for (int i = 0; i < n; ++i) {
		current[i] = max(0.0, p[i] - s[i] * g) / q[i];
		sum += current[i];
	}
	return sum * a + g * b;
}

int run() {
	while (cin >> n >> a >> b) {
		p.resize(n);
		q.resize(n);
		s.resize(n);
		current.resize(n);
		for (int i = 0; i < n; ++i) cin >> p[i] >> q[i] >> s[i];
		DB ans1 = DBL_MAX, ans2;
		for (int i = 0; i < n; ++i) {
			DB temp = gao(p[i] / s[i]);
			if (ans1 > temp) {
				ans1 = temp;
				ans2 = p[i] / s[i];
				best = current;
			}
		}
		DB temp = gao(0);
		if (ans1 > temp) {
			ans1 = temp;
			ans2 = 0;
			best = current;
		}
		cout << ans1 << endl << ans2 << endl;
		for (int i = 0; i < n; ++i) {
			if (i) cout.put(' ');
			cout << best[i];
		}
		cout << endl;
	}
	return 0;
}

int main() {
	freopen("academy.in", "r", stdin);
	freopen("academy.out", "w", stdout);
	cout << setiosflags(ios::fixed) << setprecision(20);
	ios::sync_with_stdio(0);
	return run();
}
