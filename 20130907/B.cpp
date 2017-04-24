#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

int main() {
	LL a, b, m;
	while (cin >> a >> b >> m) {
		a = max(a, b);
		if (a == 1) {
			cout << m << endl;
			continue;
		}
		int t = 1;
		b = a;
		LL ans = 0;
		while (1) {
			if (t & 1) ans += m / a;
			else ans -= m / a;
			a *= b;
			t++;
			if (a > m) break;
		}
		cout << ans << endl;
	}
	return 0;
}


