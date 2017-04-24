#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111;
int face[6][N][N];

void print(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j) cout << ' ';
			cout << face[0][i][j];
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++) {
		for (int i = 1; i <= 4; i++) {
			for (int k = 0; k < n; k++) {
				if (!(i == 1 && k == 0)) cout << ' ';
				cout << face[i][j][k];
			}
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j) cout << ' ';
			cout << face[5][i][j];
		}
		cout << endl;
	}
}

void build(int n) {
	int cur = 1, sum = 6 * n * n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			face[0][i][j] = cur;
			face[5][n - i - 1][j] = sum - cur + 1;
			cur++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			face[1][i][j] = cur;
			face[3][i][n - j - 1] = sum - cur + 1;
			cur++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			face[2][i][j] = cur;
			face[4][i][n - j - 1] = sum - cur + 1;
			cur++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	int n;
	while (cin >> n) {
		build(n);
		print(n);
	}
	return 0;
}




