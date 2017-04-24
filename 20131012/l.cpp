#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 111;
int a[N];
int n, m, x, y, op;
int main() {
	int T, Case = 1;
	ios::sync_with_stdio(0);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) a[i] = i;
		while (m--) {
			cin >> op >> x >> y;
			if (op == 1) {
				swap(a[x], a[y]);
			} else {
				int posx, posy;
				for (int i = 1; i <= n; i++) {
					if (a[i] == x) posx = i;
					if (a[i] == y) posy = i;
				}
				swap(a[posx], a[posy]);
			}
		}
		cout << "Case #" << Case++ << ":";
		for (int i = 1; i <= n; i++) cout << " " << a[i];
		cout << endl;
	}
	return 0;
}

