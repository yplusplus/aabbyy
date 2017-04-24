#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int n;
	while (cin >> n) {
		int ans = n * (n + 1) / 2;
		puts((ans & 1) ? "grimy" : "black");
	}
	return 0;
}
