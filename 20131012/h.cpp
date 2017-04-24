#include <iostream>
#include <cstdio>
using namespace std;

int g[10];
const int N = 7;
char c[10];
bool check(int x) {
	int t = 0;
	for (int i = 0; i < 3; i++) {
		t += c[(N - i + x) % N];
	}
	t %= 256;
	return t == g[x];
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		bool found = true;
		for (int i = 0; i < N; i++) {
			scanf("%d", &g[i]);
		}
		scanf("%s", c);
		for (int i = 0; i < N; i++) {
			if (!check(i)) found = false;
		}
		printf("Case #%d:\n", Case++);
		puts(found ? "Yes" : "No");
	}
	return 0;
}

