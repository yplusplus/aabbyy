#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 10;
pair<int, int> cell[N * N];
int row[N], col[N], block[N];
int num[N][N];
int n, m, nn;

int encode(int x, int y) {
	return x / n * n + y / n;
}

int get_forbiden(int x, int y) {
	int mask = 0;
	mask |= row[x];
	mask |= col[y];
	mask |= block[encode(x, y)];
	//if (x - n >= 0) { for (int j = 0; j < nn; j++) { if (j / n != y / n) mask |= num[x - n][j]; } }
	//if (x + n < nn) { for (int j = 0; j < nn; j++) { if (j / n != y / n) mask |= num[x + n][j]; } }
	//if (y - n >= 0) { for (int i = 0; i < nn; i++) { if (i / n != x / n) mask |= num[i][y - n]; } }
	//if (y + n < nn) { for (int i = 0; i < nn; i++) { if (i / n != x / n) mask |= num[i][y + n]; } }
	return mask;
}

bool dfs(int now) {
	if (now == nn * nn) return true;
	int x = cell[now].first, y = cell[now].second;
	if (num[x][y]) return dfs(now + 1);
	int can = 0;
	int forbiden = get_forbiden(x, y);

	if (x == 0 && y == 0) {
		can = 1;
	} else {
		int xmask = 0, ymask = 0;
		if (x - n >= 0) {
			for (int j = 0; j < n; j++) {
				xmask |= num[x - n][j + y / n * n];
			}
		}
		if (y - n >= 0) {
			for (int i = 0; i < n; i++) {
				ymask |= num[i + x / n * n][y - n];
			}
		}
		if (xmask == 0 && ymask == 0) can = ((1 << nn) - 1);
		else if (ymask == 0) can = xmask;
		else if (xmask == 0) can = ymask;
		else can = xmask & ymask;
	}
	can &= ~forbiden;
	for (int i = 0; i < nn; i++) {
		if (can >> i & 1) {
			num[x][y] = 1 << i;
			row[x] |= 1 << i;
			col[y] |= 1 << i;
			block[encode(x, y)] |= 1 << i;
			if (dfs(now + 1)) return true;
			num[x][y] = 0;
			row[x] ^= 1 << i;
			col[y] ^= 1 << i;
			block[encode(x, y)] ^= 1 << i;
		}
	}
	return false;
}

bool solve() {
	if (num[0][0] > 1) return false;
	int tot = 0;
	int a[N];
	//for (int i = 0; i < nn; i++) a[i] = i;
	//random_shuffle(a, a + nn);
	for (int k = 0; k < nn; k++) {
		for (int i = 0; i < nn; i++) {
			for (int j = 0; j < nn; j++) {
				if (encode(i, j) != k) continue;
				cell[tot++] = make_pair(i, j);
				int t = num[i][j];
				if (t) {
					if (row[i] & t) return false;
					if (col[j] & t) return false;
					if (block[encode(i, j)] & t) return false;
					row[i] |= t, col[j] |= t, block[encode(i, j)] |= t;
				}
			}
		}
	}
	return dfs(0);
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n >> m) {
		nn = n * n;
		memset(num, 0, sizeof(num));
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		memset(block, 0, sizeof(block));
		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			num[a][b] = 1 << c;
		}
		cout << (solve() ? "YES" : "NO") << endl;
	}
	return 0;
}

