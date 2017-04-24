#include <bits/stdc++.h>
using namespace std;

bool check(int a, int b) {
	typedef long long LL;
	LL M = 0;
	for (int i = 0; i < b; ++i) M *= a, ++M;
	if (M == 1) return 0;
	LL R = sqrt((double) M);
	for (int i = 2; i <= R; ++i) if (M % i == 0) return 0;
	return 1;
}

void test() {
	ofstream fout("out");
	for (int i = 1; i <= 16; ++i) {
		for (int j = 1; j <= 16; ++j) fout << check(i, j);
		fout << endl;
	}
}

int run() {
	int b, n;
	//test();
	while (cin >> b >> n) cout << (check(b, n) ? "YES" : "NO") << endl;
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
