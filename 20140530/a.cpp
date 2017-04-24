#include <cstdio>
#include <iostream>
using namespace std;

char buffer[1 << 5];
int run() {
	while (~scanf("%s", buffer)) {
		int n, cnt = 0;
		sscanf(buffer + 2, "%d", &n);
		for (int i = n + 1; i <= (n << 1); ++i) {
			cnt += ((n * n) % (i - n) == 0);
			//cout << i << ' ' << cnt << ' ' << endl;
		}
		printf("%d\n", cnt);
	}
	return 0;
}

int main() {
	//ios::sync_with_stdio(0);
	return run();
}
