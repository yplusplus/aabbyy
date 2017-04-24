#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 33;
int mat[N][N], mch[N][N];
int tmp[N][N], n;

void rotate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) tmp[i][j] = mat[j][n - i - 1];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) mat[i][j] = tmp[i][j];
	}
}

int cal() {
	int c = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c += mat[i][j] == mch[i][j];
		}
	}
	return c;
}


int main() {
	ios::sync_with_stdio(0);
	while (cin >> n && n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> mat[i][j];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> mch[i][j];
		}
		int mx = 0;
		for (int i = 0; i < 4; i++) {
			mx = max(cal(), mx);
			rotate();
		}
		cout << mx << endl;
	}
	return 0;
}
