#include <iostream>
#include <cstdio>
using namespace std;

int n, k;
int main() {
	while (cin >> n >> k) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			int b, g;
			cin >> b >> g;
			sum += b - g - 2;
		}
		sum += k - 2;
		if (sum < 0) puts("Big Bang!");
		else cout << sum << endl;
	}
}
