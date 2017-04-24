#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	int _, x;
	double d, a, b, f;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> x >> d >> a >> b >> f;
		cout << cas << ' ' << d / (a + b) * f << endl;
	}
	return 0;
}
