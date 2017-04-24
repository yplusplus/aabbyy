#include <bits/stdc++.h>
using namespace std;

int main() {
	int ab, ac, bd;
	while (cin >> ab >> ac >> bd) {
		int ans1 = ab * ac;
		int ans2 = bd - ac;
		int d = __gcd(ans1, ans2);
		ans1 /= d;
		ans2 /= d;
		cout << ans1 << '/' << ans2 << endl;
	}
	return 0;
}
