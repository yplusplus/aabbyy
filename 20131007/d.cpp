#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000000;
//const int N = 70010;
const int N = 3333;
int a[3][N], len[3];
void add(int x, int y, int z) {
	x %= 3;
	y %= 3;
	z %= 3;
	len[z] = max(len[x], len[y]) + 1;
	for (int i = len[z]; i <= len[z] + 10; i++) a[z][i] = 0;
	for (int i = 0; i <= len[z]; i++) {
		a[z][i] = a[x][i] + a[y][i];
	}
	for (int i = 0; i <= len[z]; i++) {
		if (a[z][i] >= mod) a[z][i + 1]++, a[z][i] -= mod;
	}
	if (a[z][len[z]] == 0) len[z]--;
}

int main()
{
	int n;
	while (~scanf("%d", &n)) {
		if (n == 3) {
			puts("4");
		} else if (n == 4) {
			puts("7");
		} else {
			len[0] = len[1] = 0;
			for (int i = 0; i <= 10; i++) {
				a[0][i] = 0;
				a[1][i] = 0;
			}
			a[0][0] = 4, a[1][0] = 7;
			for (int i = 5; i <= n; i++) {
				add(i - 2, i - 1, i);
			}
			int idx = n % 3;
			printf("%d", a[idx][len[idx]]);
			for (int i = len[idx] - 1; i >= 0; i--) {
				printf("%09d", a[idx][i]);
			}
			puts("");
		}
	}
	return 0;
}

