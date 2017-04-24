#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 55;
struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
} edge[2222];

double mat[N][N];
double x[N];
int n, m;
const double eps = 1e-8;
vector<Edge> vec[N];

int sign(double x) {
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}

bool gauss(int row, int col) {
	int i, j, r, c;
	for (r = c = 0; r < row && c <= col; r++, c++) {
		for (i = r; i < row; i++) {
			if (sign(mat[i][c]) != 0) break;
		}
		if (i == row) { r--; continue; }
		if (i != r) {
			for (j = c; j <= col; j++) swap(mat[i][j], mat[r][j]);
		}
		for (i = r + 1; i < row; i++) {
			if (sign(mat[i][c] != 0)) {
				double tmp = mat[i][c] / mat[r][c];
				for (j = c; j <= col; j++) {
					mat[i][j] -= mat[r][j] * tmp;
				}
			}
		}
	}
	for (i = row - 1; i >= 0; i--) {
		if (sign(mat[i][i]) != 0) x[i] = mat[i][col] / mat[i][i];
		else {
			if (sign(mat[i][col]) == 0) x[i] = 0;
			else return false;
		}
		for (j = 0; j < i; j++) mat[j][col] -= mat[j][i] * x[i];
	}
	return true;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; i++) vec[i].clear();
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--, b--;
			//cout << 1.0 / c << endl;
			if (a != 0 && a != n - 1) {
				mat[a][b] += 1.0 / c;
				mat[a][a] -= 1.0 / c;
			}
			if (b != 0 && b != n - 1) {
				mat[b][a] += 1.0 / c;
				mat[b][b] -= 1.0 / c;
			}
			edge[i] = Edge(a, b, c);
		}
		mat[0][0] = 1.0;
		mat[0][n] = 1.0;
		mat[n - 1][n - 1] = 1.0;
		mat[n - 1][n] = 0;
		gauss(n, n);
		double ans = 0.0;
		double I = 0.0;
		for (int i = 0; i < m; i++) {
			if (edge[i].u == n - 1 || edge[i].v == n - 1) I += fabs((x[edge[i].u] - x[edge[i].v]) / edge[i].w);
		}
		printf("Case #%d: %.2f\n", Case++, (x[0] - x[n - 1]) / I);
	}
	return 0;
}

