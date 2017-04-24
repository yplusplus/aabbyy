#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);
int main() {
	int n;
	cout << setiosflags(ios::fixed) << setprecision(10);
	while (cin >> n) {
		if (n == 1) cout << 1.0 << endl;
		else cout << 1.0 / sin(PI / n) + 1 << endl;
	}
	return 0;
}

