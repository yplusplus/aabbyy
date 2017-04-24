#include <bits/stdc++.h>
using namespace std;

const int N = 77;
const int n = 8;
const long double eps = 1e-14;
double a[N][N];
long double mat[N][N];

bool gauss(int row, int col) {
	int i, j, r, c;
	for (r = c = 0; r < row && c < col; r++, c++) {
		int pvt = r;
		for (i = r + 1; i < row; i++) {
			if (fabs(mat[i][c]) > fabs(mat[pvt][c])) pvt = i;
		}
		if (fabs(mat[pvt][c]) < eps) { r--; continue; }
		//cout << pvt << endl;
		if (pvt != r) {
			for (j = c; j <= col; j++) {
				swap(mat[pvt][j], mat[r][j]);
			}
		}
		for (i = r + 1; i < row; i++) {
			long double tmp = mat[i][c] / mat[r][c];
			//cout << tmp << endl;
			for (j = c; j <= col; j++) {
				mat[i][j] -= mat[r][j] * tmp;
			}
		}
	}
	//cout << r << " " << c << endl;
	for (i = row - 1; i >= 0; i--) {
		if (fabs(mat[i][i]) < eps) {
			if (fabs(mat[i][col]) > eps) return false;
		} else {
			mat[i][col] /= mat[i][i];
			for (j = 0; j < i; j++) {
				mat[j][col] -= mat[j][i] * mat[i][col];
				mat[j][i] = 0;
			}
		}
	}
	//cout << 123 << endl;
	return true;
}

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int cnt[N][N];
bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}

int get_id(int x, int y) {
	return x * n + y;
}

int main() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%lf", &a[i][j]);
			//cout << a[i][j] << endl;
		}
	}
	memset(mat, 0, sizeof(mat));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 8; k++) {
				if (check(i + dx[k], j + dy[k])) cnt[i][j] += a[i + dx[k]][j + dy[k]];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int u = get_id(i, j);
			long double sum = 0.0;
			mat[u][u] = 1.0;
			for (int k = 0; k < 8; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if (check(nx, ny)) {
					int v = get_id(nx, ny);
					mat[u][v] -= a[i][j] / cnt[nx][ny];
				}
			}
			//cout << u << " " << sum << " " << cnt << endl;
		}
	}
	for (int i = 0; i <= n * n; i++) {
		mat[n * n][i] = 1;
	}
	int row = n * n + 1, col = n * n;
	//cout << row << " " << col << endl;
	/*
	for (int i = 0; i < row; i++) {
		for (int j = 0; j <= col; j++) {
			cout << mat[i][j] << " ";
		}
		puts("");
	}
	*/
	gauss(row, col);
	long double ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.20f", (double) mat[get_id(i, j)][col]);
			ans += mat[get_id(i, j)][col];
			if (j < n - 1) printf(" ");
		}
		puts("");
	}
	return 0;
}
