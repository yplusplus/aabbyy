#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 22;
typedef long long LL;
LL a[N];

int main() {
	int c = 1, d = 1;
	memset(a, 0, sizeof(a));
	a[0] = a[1] = 1;
	for (int i = 2; i < N; i++) {
		for (int j = 1; j <= d; j++) a[i] += a[i - j];
		//cout << i << ' ' << a[i] << ' ' << d << endl;
		if (--c == 0) d++, c = d;
	}
	int n, k, x, y;
	while (cin >> n >> k >> x >> y) {
		LL sum = 0;
		for (int i = 1; i <= n; i++) sum += a[i];
		//cout << sum << endl;
		if (sum > k) cout << "NO" << endl;
		else {
			cout << "YES" << endl;
			for (int i = 0; i < n; i++) {
				if (i) cout << ' ';
				cout << (sum -= a[i]) + 1;
			}
			cout << endl;
		}
	}
	return 0;
}


