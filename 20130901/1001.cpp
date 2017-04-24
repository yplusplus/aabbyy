#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int T, n, Case = 1, ans;
	cin >> T;
	while (T--) {
		cin >> n;
		printf("Case %d: ", Case++);
		if (n == 1) cout << 1 << endl;
		else if (n == 2 || n == 3) cout << 2 << endl;
		else {
			int ans = 2 * n - 4;
			cout << ans << endl;
		}
	}
	return 0;
}

