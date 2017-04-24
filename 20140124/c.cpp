#include <iostream>
#include <cstdio>
using namespace std;

const int N = 55555;
const int M = 8;
int mi[1 << M];
int w[M];
int a[N][M];
int n, m;
int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = 0; i < m; i++) scanf("%d", &w[i]);
		int ans = -(1 << 30);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 1 << m; j++) {
				int sum = 0;
				for (int k = 0; k < m; k++) {
					if (j >> k & 1) sum += a[i][k] * w[k];
					else sum -= a[i][k] * w[k];
				}
				if (i == 0) {
					mi[j] = sum;
				} else {
					//cout << sum << " " << mi[j] << endl;
					ans = max(ans, sum - mi[j]);
					mi[j] = min(mi[j], sum);
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}

