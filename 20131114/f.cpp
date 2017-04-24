#include <bits/stdc++.h>
using namespace std;

const int N = 5;
int g[N][N];
int a[N];
int b[N];
int main() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &g[i][j]);
		}
	}	
	for (int i = 0; i < N; i++) a[i] = i;
	int ans = 1 << 30;
	do {
		if (a[0] != 0 || a[4] != 4 || a[3] == 2) continue;
		int t = 0;
		for (int i = 1; i < N; i++) {
			t += g[a[i - 1]][a[i]];
		}
		if (t < ans) {
			ans = t;
			memcpy(b, a, sizeof(a));
		}
	} while (next_permutation(a, a + N));
	printf("%d\n", ans);
	printf("%d", b[0] + 1);
	for (int i = 1; i < N; i++) {
		printf(" %d", b[i] + 1);	
	}
	puts("");
	return 0;
}
