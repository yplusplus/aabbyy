#include <bits/stdc++.h>
using namespace std;

int main() {
	int l, k, h;
	while (cin >> l >> k >> h) {
		int q = l / k;
		int r = l % k;
		if (r == 0) {
			printf("%.10f %.10f\n", q * h * 1.0, q * h * 1.0);
		} else {
			printf("%.10f %.10f\n", q * h * 1.0, (q + 1) * h * 1.0);
		}
	}
}

