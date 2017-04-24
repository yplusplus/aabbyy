#include <bits/stdc++.h>
using namespace std;

const int N = 11 * 3;
int a[77], b[77];
int matrix[22][5];

bool stop(int as, int bs, int acnt, int bcnt) {
	if (as > bs && (as - bs) > bcnt) return true;
	if (as < bs && (bs - as) > acnt) return true;
	return false;
}

void solve() {
	int as = 0, bs = 0;
	int acnt = 5, bcnt = 5;
	int i;
	bool found = false;
	for (i = 0; i < 5; i++) {
		as += a[i];
		acnt--;
		if (stop(as, bs, acnt, bcnt)) { found = true; break; }
		bs += b[i];
		bcnt--;
		if (stop(as, bs, acnt, bcnt)) { found = true; break; }
	}
	if (!found) {
		i = 5;
		while (as == bs) {
			as += a[i];
			bs += b[i];
			i++;
		}
	}
	printf("Winner: %s\n", as > bs ? "home" : "away");
	printf("Score: %d:%d\n", as, bs);
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	char result[20];
	while (T--) {
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 3; j++) {
				scanf("%s", result);
				if (result[0] == 'y') matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}
		for (int j = 0, tot = 0; j < 3; j++) for (int i = 0; i < 11; i++) a[tot++] = matrix[i][j];
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 3; j++) {
				scanf("%s", result);
				if (result[0] == 'y') matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}
		for (int j = 0, tot = 0; j < 3; j++) for (int i = 0; i < 11; i++) b[tot++] = matrix[i][j];
		printf("Match %d:\n", Case++);
		solve();
	}
	return 0;
}
