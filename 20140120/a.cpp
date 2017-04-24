#include <iostream>
using namespace std;

const int N = 111;
char ans[N][N];
int n, m, k, l;
void add(char *a, int s, int t) { for (int i = 0; i < m; i++) a[i] = (s + (i / t)) % k + 'A'; }
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

bool check(int x, int y, int dx, int dy) {
	int c = 0, a = x, b = y;
	while (inmat(a, b)) {
		if (a == x && b == y || ans[a][b] == ans[a - dx][b - dy]) c++;
		else c = 1;
		if (c >= l) return 0;
		//cout << a << ' ' << b << ' ' << c << ' ' << k << endl;
		a += dx; b += dy;
	}
	return 1;
}

bool check() {
	for (int i = 0; i < n; i++) if (!check(i, 0, 0, 1) || !check(i, 0, 1, 1) || !check(i, m - 1, 1, -1)) return 0;
	for (int i = 0; i < m; i++) if (!check(0, i, 1, 0) || !check(0, i, 1, 1) || !check(0, i, 1, -1)) return 0;
	return 1;
}

int main() {
	while (cin >> n >> m >> k >> l) {
		int x = max(n, m);
		if (l - 1 <= x) {
			bool ok = 0;
			for (int i = 0; i < n; i++) ans[i][m] = 0;
			for (int d = 0; d < k; d++) {
				//cout << d << ' ' << l - 1 << endl;
				for (int i = 0; i < n; i++) add(ans[i], i * d % k, l - 1);
				//for (int i = 0; i < n; i++) cout << ans[i] << endl;
				if (check()) {
					ok = 1;
					break;
				}
			}
			if (ok) {
				cout << "YES" << endl;
				for (int i = 0; i < n; i++) cout << ans[i] << endl;
			} else cout << "NO" << endl;
		} else cout << "NO" << endl;
	}
	return 0;
}
