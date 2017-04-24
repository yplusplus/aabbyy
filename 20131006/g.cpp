#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 55;
char maz[N][N];
int n, m, k;
pair<int, int> row[N];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", maz[i]);
			row[i].second = 0;
			for (int j = 0; j < m; j++) row[i].second += maz[i][j] == '*';
			ans += row[i].second;
		}
		for (int i = 0; i < n; i++) {
			row[i].first = m - 2 * row[i].second;
		}
		sort(row, row + n);
		reverse(row, row + n);
		int i = 0;
		while (k && i < n) {
			if (row[i].first < 0) break; 
			else {
				ans += row[i].first;
				row[i].second = m - row[i].second;
				i++, k--;
			}
		}
		//cout << k << endl;
		if (k & 1) {
			int t = (1 << 25);
			for (int i = 0; i < n; i++) {
				t = min(2 * row[i].second - m, t);
			}
			ans -= t;
		}
		printf("%d\n", ans);
	}
	return 0;
}

