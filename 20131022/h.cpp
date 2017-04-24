#include <bits/stdc++.h>
using namespace std;

const int N = 111;
int a[N][N], b[N][N];
int main() {
	int n;
	ios::sync_with_stdio(false);
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
			}
		}
		memset(b, 0, sizeof(b));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				if (j > i) {
					for (int k = i + 1; k <= j; k++) {
						b[k - 1][k] += a[i][j];
					}
				} else {
					for (int k = j + 1; k <= i; k++) {
						b[k][k - 1] += a[i][j];
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i + 1 < n; i++) {
			ans = max(ans, b[i][i + 1]);
		}
		for (int i = n - 1; i - 1 >= 0; i--) {
			ans = max(ans, b[i][i - 1]);
		}
		ans = (ans + 35) / 36;
		cout << ans << endl;
	}
	return 0;


}

