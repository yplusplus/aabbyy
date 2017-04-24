#include <bits/stdc++.h>
using namespace std;

const int n = 4;
int x[n], y[n];
int cnt[4];

bool check() {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (x[i] == x[j] && y[i] == y[j]) return false;
			if (x[i] == x[j] || y[i] == y[j]) {
				cnt[i]++; cnt[j]++;
			}
		}
	}
	for (int i = 0; i < n; i++) 
		if (cnt[i] != 1) return false;
	return true;
}

void output() {
	for (int i = 0; i < n; i++) {
		cout << x[i] << " " << y[i] << endl;
	}
}
void solve() {
	//0
	if (check()) { return; }
	//1
	for (int i = 0; i < n; i++) {
		int a = x[i], b = y[i];
		for (int j = 1; j <= 20; j++) {
			for (int k = 1; k <= 20; k++) {
				x[i] = j, y[i] = k;
				if (check()) return;
			}
		}
		x[i] = a, y[i] = b;
	}
	//2
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			int a = x[i], b = y[i], c = x[j], d = y[j];
			for (int k = 1; k <= 20; k++) {
				for (int l = 1; l <= 20; l++) {
					x[i] = k, y[i] = l;
					for (int kk = 1; kk <= 20; kk++) {
						for (int ll = 1; ll <= 20; ll++) {
							x[j] = kk, y[j] = ll;
							if (check()) return;
						}
					}
					x[j] = c, y[j] = d;
				}
			}
			x[i] = a, y[i] = b;
		}
	}
}

int main() {
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	solve();
	output();
	return 0;
}
