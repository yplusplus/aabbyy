#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int _, n;
	ios::sync_with_stdio(0);
	cin >> _;
	for (int i = 1; i <= _; i++) {
		cin >> n;
		cout << "Case #" << i << ": " << (n - 1) % 9 + 1 << endl;
	}
	return 0;
}

