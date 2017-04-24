#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 10;
const int MOD = 2012;
int ans[N];

int run() {
	ans[0] = ans[1] = 1;
	for (int i = 2; i < N; ++i) {
		ans[i] = ans[i - 1] + ans[i - 2];
		if (ans[i] >= MOD) ans[i] -= MOD;
	}
	ans[0] = 0;
	int n, _;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> n;
		cout << "Case #" << cas << ": " << ans[n] << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
