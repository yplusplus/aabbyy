#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const int N = 1111;
int X[N], Y[N];
DB W[N];

int main() {
	int _, n;
	cout << setiosflags(ios::fixed) << setprecision(1);
	ios::sync_with_stdio(0);
	cin >> _;
	while (_--) {
		cin >> n;
		for (int i = 0; i < n; i++) cin >> X[i] >> Y[i];
		memset(W, 0, sizeof(W));
		sort(X, X + n);
		for (int i = 0; i < n; i++) {
			if (i) W[i] += X[i] - X[i - 1];
			if (i < n - 1) W[i] += X[i + 1] - X[i];
			W[i] /= 2;
		}
		sort(W, W + n);
		sort(Y, Y + n);
		DB ans = 0;
		for (int i = 0; i < n; i++) ans += W[i] * Y[i];
		cout << ans << endl;
	}
	return 0;
}

