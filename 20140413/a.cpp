#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int main() {
	LL a, b;
	while (cin >> a >> b) {
		if ((a >= 0) ^ (b >= 0)) {
			cout << (a + b) << endl;
		} else {
			cout << (a - b) << endl;
		}
	}
	return 0;
}
