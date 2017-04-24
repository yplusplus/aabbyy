#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1111;
int n, k;
int a[N];
int main() {
	while (~scanf("%d%d", &n, &k)) {
		int nn = 1 << n;
		for (int i = 0; i < nn; i++) scanf("%d", &a[i]);
		int cnt = 0;
		for (int i = 0; i < nn; i++) {
			if (a[i] < a[k]) cnt++;
		}
		cnt++;
		if (cnt < nn) cout << 0 << " ";
		else cout << n << " ";
		int ans = 0;
		while (cnt > 1) {
			ans++;
			cnt >>= 1;
		}
		cout << ans << endl;
	}

	return 0;
}
