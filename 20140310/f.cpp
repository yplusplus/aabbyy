#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const int M = 33;
char letter[N][M];
bool sharp[N][M];
int num[N][M];

void change(char a, int b, bool c, char &d, int &e, bool &f) {
	if (c) {
		if (a == 'G') {
			d = 'A';
			e = b;
			f = false;
		}
		else {
			d = a + 1;
			e = b;
			f = false;
		}
	} else {
		if (a == 'C' || a == 'D' || a == 'F' || a == 'G' || a == 'A') {
			d = a;
			e = b;
			f = true;
		} else if (a == 'E') {
			d = 'F';
			e = b;
			f = false;
		} else if (a == 'B') {
			d = 'C';
			e = b + 1;
			f = false;
		}
	}
}

void init() {
	memset(sharp, false, sizeof(sharp));
	letter[1][0] = 'E';
	num[1][0] = 5;
	letter[2][0] = 'B';
	num[2][0] = 4;
	letter[3][0] = 'G';
	num[3][0] = 4;
	letter[4][0] = 'D';
	num[4][0] = 4;
	letter[5][0] = 'A';
	num[5][0] = 3;
	letter[6][0] = 'E';
	num[6][0] = 3;
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 30; j++) {
			change(letter[i][j - 1], num[i][j - 1], sharp[i][j - 1], letter[i][j], num[i][j], sharp[i][j]);
		}
	}
}

int fret[10];
int main() {
	char line[111111];
	init();
	bool topline = true;
	bool firstcase = true;
	while (gets(line)) {
		if(strlen(line) == 0) continue;
		if (strcmp(line, "0") == 0) {
			memset(fret, 0, sizeof(fret));
			firstcase = 0;
			topline = true;
			continue;
		}
		if (strlen(line) > 6) {
			//cout << line << endl;
			sscanf(line, "%d%d%d%d%d%d", &fret[1], &fret[2], &fret[3], &fret[4], &fret[5], &fret[6]);
			//for (int i = 1; i <= 6; i++) { cout << fret[i] << " "; } cout << endl;
		} else {
			int x;
			if(!firstcase && topline) printf("\n");
			topline = false;
			sscanf(line, "%d", &x);
			cout << letter[x][fret[x]];
			cout << num[x][fret[x]];
			if (sharp[x][fret[x]]) cout << '#';
			cout << endl;
		}
	}
	return 0;
}
