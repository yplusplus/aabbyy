#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 24;
int mat[N], tmp[N];
const int chg1[3][8] = {{ 2, 3, 8, 14, 17, 16, 11, 5 },
						{ 1, 3, 7, 13, 17, 19, 21, 23 },
						{ 4, 5, 6, 7, 8, 9, 23, 22 } };
const int chg2[3][4] = {{ 6, 7, 13, 12 },
						{ 9, 8, 14, 15 },
						{ 2, 3, 1, 0 } };
const int face[6][4] = {{ 0, 1, 2, 3 },
						{ 4, 5, 10, 11 },
						{ 6, 7, 12, 13 },
						{ 8, 9, 14, 15 },
						{ 16, 17, 18, 19 },
						{ 20, 21, 22, 23 } };

int ans;
bool check(int a) {
	for (int i = 0; i < 4; i++) if (mat[face[a][i]] != mat[face[a][0]]) return 0;
	return 1;
}

bool check() {
	int c = 0;
	for (int i = 0; i < 6; i++) c += check(i);
	ans = max(c, ans);
	return ans;
}

void change(int k) {
	for (int i = 0; i < N; i++) tmp[i] = mat[i];
	if (k & 1) {
		k >>= 1;
		for (int i = 0; i < 8; i++) tmp[chg1[k][i]] = mat[chg1[k][i + 2 & 7]];
		for (int i = 0; i < 4; i++) tmp[chg2[k][i]] = mat[chg2[k][i + 1 & 3]];
	} else {
		k >>= 1;
		for (int i = 0; i < 8; i++) tmp[chg1[k][i]] = mat[chg1[k][i + 6 & 7]];
		for (int i = 0; i < 4; i++) tmp[chg2[k][i]] = mat[chg2[k][i + 3 & 3]];
	}
	for (int i = 0; i < N; i++) mat[i] = tmp[i];
}

void dfs(int k, int pre) {
	int tmp[N];
	check();
	if (k == 0) return ;
	for (int i = 0; i < N; i++) tmp[i] = mat[i];
	for (int i = 0; i < 6; i++) {
		if ((i ^ 1) == pre) continue;
		change(i);
		dfs(k - 1, i);
		for (int j = 0; j < N; j++) mat[j] = tmp[j];
	}
}

int main() {
	int k;
	while (cin >> k) {
		for (int i = 0; i < N; i++) cin >> mat[i];
		ans = 0;
		dfs(k, -1);
		cout << ans << endl;
	}
	return 0;
}
