#include <iostream>
#include <cstdio>
using namespace std;

int get_number(int i, int j) {
	if (i == j) return 99;
	if (i > j) return 0;
	return 100;
}

int main() {
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {

				printf("%d%c", get_number(i, j), j == n - 1 ? '\n' : ' ');
			}
		}
		puts("");
	}
	return 0;
}

