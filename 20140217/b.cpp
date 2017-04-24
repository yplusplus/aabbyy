#include <bits/stdc++.h>

using namespace std;

const int N = 55;
char mat[2][N][N];

void column(int n) {
	int ch = 'A';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) mat[0][i][j] = ch;
		if (ch == 'Z') ch = 'a';
		else ch++;
	}
}

void row(int n) {
	int ch = 'A';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) mat[1][j][i] = ch;
		if (ch == 'Z') ch = 'a';
		else ch++;
	}
}


int main() {
	ios::sync_with_stdio(0);
	int n;
	bool pnt = 0;
	while (cin >> n) {
		if (pnt) cout << endl;
		pnt = 1;
		memset(mat, 0, sizeof mat);
		row(n);
		column(n);
		cout << 2 << ' ' << n << ' ' << n << endl;
		for (int i = 0; i < 2; i++) {
			if (i) cout << endl;
			for (int j = 0; j < n; j++) cout << mat[i][j] << endl;
		}
	}
	return 0;
}
