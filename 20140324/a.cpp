#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef double DB;
const int T = 1 << 8;
const DB PI = acos(-1.0);
const DB EPS = 1e-6;

bool check(const VI &a) {
	int sum = accumulate(a.begin(), a.end(), 0);
	for (int i = 0, sz = a.size(); i < sz; ++i) if ((a[i] << 1) >= sum) return 0;
	return 1;
}

inline DB fix(const DB &a) { return min(max(a, -1.0), 1.0); }

bool check(const VI &a, const int n, const DB &m) {
	DB sum = 0;
	for (int i = 0; i < n; ++i) sum += asin(fix(a[i] / (2 * m)));
	return sum < PI;
}

DB work(const VI &a) {
	int maxID = 0, n = a.size();
	for (int i = 1; i < n; ++i) if (a[i] > a[maxID]) maxID = i;
	DB R = a[maxID] / 2.0, sum = 0;
	for (int i = 0; i < n; ++i) {
		if (i == maxID) continue;
		sum += asin(fix(a[i] / (2 * R)));
	}
	if (sum < PI / 2 + EPS) return R;
	DB l = *max_element(a.begin(), a.end()) / 2.0, r = accumulate(a.begin(), a.end(), 0) / 2.0, m;
	for (int i = 0; i < T; ++i) {
		m = (l + r) / 2;
		if (check(a, n, m)) r = m;
		else l = m;
	}
	return (l + r) / 2;
}

int run() {
	int _, n;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> n;
		VI wall(n);
		for (int i = 0; i < n; ++i) cin >> wall[i];
		cout << "Case " << cas << ": ";
		if (check(wall)) cout << work(wall) << endl;
		else cout << "can't form a convex polygon" << endl;
	}
	return 0;
}

int main() {
	freopen("zeriba.in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(4);
	return run();
}
