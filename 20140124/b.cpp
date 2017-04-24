#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 111111;
inline int lowbit(int a) { return a & -a; }
struct BIT {
	LL a[N], n;
	void init(int _) { n = _ + 3; for (int i = 0; i < n; i++) a[i] = 0; }
	void add(int x, int d) { for (x += 2; x < n; x += lowbit(x)) a[x] += d; }
	LL get(int x) { LL s = 0; for (x += 2; x > 0; x -= lowbit(x)) s += a[x]; return s; }
} bit;
int b[N], n;

int find(int x) {
	int l = 1, r = n, mk = n, m;
	while (l <= r) {
		int m = l + r >> 1;
		if (bit.get(m) >= x) mk = m, r = m - 1;
		else l = m + 1;
	}
	return mk;
}

int main() {
	int m, x, y;
	while (cin >> n) {
		bit.init(n);
		for (int i = 1; i <= n; i++) cin >> b[i];
		for (int i = 1; i <= n; i++) bit.add(i, b[i]);
		cin >> m;
		char op[3];
		while (m--) {
			cin >> op;
			if (*op == 'p') {
				cin >> x >> y;
				bit.add(x, y - b[x]);
				b[x] = y;
			} else {
				cin >> x;
				cout << find(x) << endl;
			}
		}
	}
	return 0;
}
