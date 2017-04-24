#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int a[N], b[N], c[N];
int n;
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) { scanf("%d", &b[i]); }
		for (int i = 1; i <= n; i++) { scanf("%d", &a[i]); }
		int need = 0;
		for (int i = n; i >= 1; i--) {
			if (need + b[i] >= a[i]) {
				c[i] = a[i];
				need += b[i] - a[i];
			} else {
				c[i] = need + b[i];
				need = 0;
			}
		}
		if (need != 0) puts("Myon");
		else {
			for (int i = 1; i <= n; i++) {
				printf("%d%c", c[i], i == n ? '\n' : ' ');
			}
		}
	}
	return 0;
}
