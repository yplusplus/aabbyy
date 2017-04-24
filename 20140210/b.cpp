#include <bits/stdc++.h>
using namespace std;

const int N = 1111111;
int pos[N];
int main() {
	int a, b;
	while (cin >> a >> b) {
		memset(pos, -1, sizeof pos);
		a %= b;
		int cur = 0;
		pos[0] = 0;
		while (pos[a] == -1) {
			pos[a] = cur++;
			a *= 10;
			a %= b;
		}
		if (a == 0) cout << cur << ' ' << 0 << endl;
		else cout << pos[a] << ' ' << cur - pos[a] << endl;
	}
	return 0;
}
