#include <bits/stdc++.h>
using namespace std;

const int DG = 10;
const int UB = 10000;
const int UB_RES = 10000000;
vector<int> cnt(DG), ub(DG);

bool input() {
	for (int i = 0; i < DG; ++i) cin >> ub[i];
	for (int i = 0; i < DG; ++i) cnt[i] = 0;
	return cin.fail() == false;
}

bool check() {
	for (int i = 0; i < DG; ++i) if (cnt[i] > ub[i]) return 0;
	return 1;
}

bool add(int x, int l) {
	bool ok = 1;
	for (int i = 0; i < l; ++i) {
		++cnt[x % DG];
		if (cnt[x % DG] > ub[x % DG]) ok = 0;
		x /= DG;
	}
	return ok;
}

void sub(int x, int l) {
	for (int i = 0; i < l; ++i) {
		--cnt[x % DG];
		x /= DG;
	}
}

bool dfs(int a, int p, int end, int &b) {
	if (p >= end) {
		if (add(b, 4)) {
			if (a * b < UB_RES) {
				if (add(a * b, 7)) {
					return 1;
				}
				sub(a * b, 7);
			}
		}
		sub(b, 4);
		return 0;
	}
	for (int i = 0; i < DG; ++i) {
		if (i * a >= UB) break;
		if (add(i * a, 4)) {
			b = b * 10 + i;
			if (dfs(a, p + 1, end, b)) {
				return 1;
			}
			b /= 10;
		}
		sub(i * a, 4);
	}
	return 0;
}

void work(int &a, int &b) {
	for (int i = 0; i < UB; ++i) {
		if (add(i, 4)) {
			int j = 0;
			if (dfs(i, 0, 4, j)) {
				a = i, b = j;
				return ;
			}
		}
		sub(i, 4);
	}
}

int run() {
	while (input()) {
		int a, b;
		a = -1, b = -1;
		work(a, b);
		cout << a << endl << b << endl;
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
