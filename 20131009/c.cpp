#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(10);
	int n;
	double t, s, x;
	while (cin >> n >> t >> s) {
		while (n--) {
			cin >> x;
			cout << (x + t + s) / 2 << endl;
		}
	}
	return 0;
}

