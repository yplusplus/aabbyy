#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const double eps = 1e-6;
int a, b, c, d;
double p;
const int N = 222;

double mat[N][N];
double fix(double x) {
	if (x > eps) return x;
	return fabs(x);
}

bool gauss(int row, int col) {
	int i, j, r, c;
	for (r = c = 0; r < row && c < col; r++, c++) {
		int pvt = r;
		for (i = r + 1; i < row; i++) {
			if (fabs(mat[i][c]) > fabs(mat[pvt][c])) pvt = i;
		}
		if (fabs(mat[pvt][c]) < eps) { r--; continue; }
		if (r != pvt) {
			for (j = c; j <= col; j++) swap(mat[pvt][j], mat[r][j]);
		}
		for (i = r + 1; i < row; i++) {
			double tmp = mat[i][c] / mat[r][c];
			for (j = c; j <= col; j++) {
				mat[i][j] -= tmp * mat[r][j];
			}
		}
	}
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
	return true;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> a >> b >> c >> d >> p;
		int row = a + b + d + 1, col = row;
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < row; i++) {
			mat[i][i] = 1.0;
			if (i > a + b) {
				mat[i][col] = 1.0;
			} else {
				if (i - c >= 0) mat[i][i - c] = -p;
				mat[i][i + d] = p - 1;	
			}
		}
		gauss(row, col);
		printf("%.2f\n", fix(mat[a][col]));
	}
	return 0;
}

