#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

bool check(int x) {
	return x <= 20;
}

int main() {
	int T, Case = 1;
	cin >> T;
	while (T--) {
		int a, b, c;
		cin >> a >> b >> c;
		printf("Case %d: ", Case++);
		if (check(a) && check(b) && check(c)) puts("good");
		else puts("bad");
	}
	return 0;
}
