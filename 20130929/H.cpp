#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int a, b;
	while (cin >> a >> b && (a || b)) {
		int d = 0;
		for (int i = 2; i <= a; i++) d = (d + b) % i;
		cout << a << ' ' << b << ' ' << d + 1 << endl;
	}
	return 0;
}

