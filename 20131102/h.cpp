#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int a[N], b[N];

int main() {
	int n, x;
	string name, outcome;
	ios::sync_with_stdio(false);
	while (cin >> n) {
		int alloc = 0;
		map<string, int> mp;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for (int i = 0; i < n; i++) {
			cin >> name >> outcome;
			if (mp.count(name) == 0) { mp[name] = ++alloc; }
			int id = mp[name];
			if (outcome == "TL" || outcome == "WA" || outcome == "ML") {
				cin >> x;
				if (x < 6) continue;
				if (x == 6) {
					b[id] = 1;
				} else {
					a[id] = 1, b[id] = 1;
				}
			} else if (outcome == "AC") {
				b[id] = 1;
			}
		}
		int c = 0, d = 0;
		for (int i = 1; i <= alloc; i++) {
			c += a[i];
			d += b[i];
		}
		cout << c << " " << d << endl;
	}
	return 0;
}
