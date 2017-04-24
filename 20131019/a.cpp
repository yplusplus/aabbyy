#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n;
	while (cin >> n) {
		if (n == 4) cout << "0 2" << endl;
		else if (n == 5) cout << "0 0" << endl;
		else if (n == 6) cout << "6 9" << endl;
		else {
			if (n & 1) {
				cout << (n * 1ll - 3) / 2 * n << " 0" << endl;
			} else {
				cout << (n - 4ll) / 2 * n + n / 2 << ' ' << (n - 4ll) / 2 * n + n / 2 << endl;
			}
		}
	}
	return 0;
}


