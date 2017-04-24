#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;
typedef vector<int> VI;
inline int lowbit(int x) { return x & -x; }
const int K = 11;
struct BIT {
	VI a;
	int n;
	void init(int sz) { a.clear(); a.resize(n = sz + 5, 0); }
	void add(int x, int d) { for ( ; x < n; x += lowbit(x)) { a[x] += d; if (a[x] >= MOD) a[x] -= MOD; } }
	int sum(int x = -1) { int s = 0; for (x = x < 0 ? n - 1 : x; x > 0; x -= lowbit(x)) { s += a[x]; if (s >= MOD) s -= MOD; } return s; }
} bit[K];

int run() {
	int n, m;
	while (cin >> n >> m) {
		for (int i = 0; i <= m; ++i) bit[i].init(n);
		bit[0].add(n + 1, 1);
		int x;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			for (int i = m; i >= 1; --i) {
				bit[i].add(x, (bit[i - 1].sum() - bit[i - 1].sum(x) + MOD) % MOD);
			}
		}
		cout << bit[m].sum() << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
