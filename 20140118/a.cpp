#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cassert>
using namespace std;

const int N = 1111;
char maz[N][N];
int all;
int n, m;
int row[2 * N], col[2 * N];

int solve(int a[], int n) {
	if (all % n) return -1;
	int target = all / n;
	int res = n * n * n;
	for (int i = 0; i < n; i++) {
		int left = 0;
		int tmp = 0;
		for (int j = i; j < i + n; j++) {
			left += a[j];
			left -= target;
			tmp += abs(left);
		}
		assert(left == 0);
		res = min(res, tmp);
	}
	return res;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		all = 0;
		for (int i = 0; i < n; i++) { scanf("%s", maz[i]); }
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (maz[i][j] == '1') row[i]++, col[j]++, all++;
			}
		}
		for (int i = 0; i < n; i++) row[i + n] = row[i];
		for (int j = 0; j < m; j++) col[j + m] = col[j];
		int ans_row = solve(row, n);
		int ans_col = solve(col, m);
		printf("Case %d: ", Case++);
		if (ans_row != -1 && ans_col != -1) {
			printf("both %d\n", ans_row + ans_col);
		} else if (ans_row == -1 && ans_col == -1) {
			puts("impossible");
		} else if (ans_row == -1) {
			printf("column %d\n", ans_col);
		} else {
			printf("row %d\n", ans_row);
		}
	}
	return 0;
}
