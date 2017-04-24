#include <bits/stdc++.h>
using namespace std;

const int N = 32;
int y;
int digit[N];
int a[N], b[N];
int tot;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while (cin >> y) {
		tot = 0;
		while (y) {
			digit[tot++] = y & 1;
			y >>= 1;
		}
		a[tot - 1] = digit[tot - 1];
		for (int i = tot - 2; i >= 0; i--) {
			b[i] = a[i + 1];
			a[i] = digit[i] ^ b[i];
		}
		int ans = 0;
		for (int i = tot - 1; i >= 0; i--) {
			ans <<= 1;
			ans |= a[i];
		}
		cout << ans << endl;
	}
}
