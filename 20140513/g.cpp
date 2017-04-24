#include <bits/stdc++.h>
using namespace std;

const int N = 4040;
bool a[N][N], b[N][N], c[N][N];
int n, m;

int hex2dec(char ch) {
	if (isdigit(ch)) return ch - '0';
	return ch - 'A' + 10;
}

void input(bool a[][N]) {
	static char str[1111];
	int cols = (n + 3) / 4;
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		for (int j = 0; j < cols; j++) {
			int ret = hex2dec(str[j]);
			for (int k = 0; k < 4; k++) {
				a[i][j * 4 + k] = ret >> (3 - k) & 1;
			}
		}
	}
}

void mul(bool a[N], bool b[][N], bool c[N]) {
	for (int j = 0; j < N; j++) c[j] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[j] ^= (a[i] & b[i][j]);
		}
	}
}

bool check() {
	srand(time(0));
	const int LIMIT = 10;
	bool t[N], tt[N], ttt[N], tttt[N];
	for (int i = 0; i < LIMIT; i++) {
		for (int j = 0; j < n; j++) {
			t[j] = rand() & 1;
		}
		mul(t, a, tt);
		mul(tt, b, ttt);
		mul(t, c, tttt);
		for (int j = 0; j < n; j++) {
			if (ttt[j] ^ tttt[j]) return false;
		}
	}
	return true;
}

int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	scanf("%d", &n);
	input(a);
	input(b);
	input(c);
	if (check()) puts("YES");
	else puts("NO");
	return 0;
}
