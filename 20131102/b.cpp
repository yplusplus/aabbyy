#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

bool mat[4][4], tmp[4][4];
char buf[11], word[4][11], ans[22];

bool input() {
	for (int i = 0; i < 4; i++) {
		if (!(cin >> buf)) return 0;
		for (int j = 0; j < 4; j++) mat[i][j] = buf[j] == 'X';
	}
	for (int i = 0; i < 4; i++) cin >> word[i];
	return 1;
}

void rotate() {
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) tmp[i][j] = mat[3 - j][i];
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) mat[i][j] = tmp[i][j];
	//for (int i = 0; i < 4; i++) {
		//for (int j = 0; j < 4; j++) cout << mat[i][j];
		//cout << endl;
	//}
}

int main() {
	while (input()) {
		char *p = ans;
		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (mat[i][j]) *p = word[i][j], p++;
				}
			}
			rotate();
		}
		*p = 0;
		cout << ans << endl;
	}
	return 0;
}
